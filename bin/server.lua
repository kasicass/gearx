-- emacs: -*- mode: lua; coding: utf-8; -*- 

--[[
    Copyright (C) 2007 GearX Team

    This source code is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This source code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

	$Id: $
	ChenZaichun@gmail.com
--]]

-------------------------------------------------------------------------------
require("gxbase")
require("socket")
require("operations")
require("serverdata")

-------------------------------------------------------------------------------
-- server class
server = {}
-------------------------------------------------------------------------------
local DEFAULT_PORT = 5158		-- default server port

-------------------------------------------------------------------------------
-- server init
-- 
-- @param port which port to listen
-- 
function server.init (port)
	local self = {}
	socket.init()				-- init socket lib

	self._socket = socket.create()
	socket.bind(self._socket, port or DEFAULT_PORT) -- bind server socket
	socket.listen(self._socket)

	self._serverdata = {}
	
	setmetatable(self, {__index = server})
	return self
end

-------------------------------------------------------------------------------
-- server shutdown
-- 
function server:shutdown ()
	self = nil
	socket.shutdown()
end

-------------------------------------------------------------------------------
-- process data
-- 
-- @param list recived data list
-- 
function server:process (list, datalist)
	for i = 1, #list do
		local t = list[i]
		local data = datalist[i]
		local str = t:recvdata()

		-- process data
		local _, _, opstr = string.find(str, "^(%d)")
		local op = tonumber(opstr)
		if (op == operations.MOVELEFT) then
			-- move left
			data:moveleft()
		elseif (op == operations.MOVERIGHT) then
			-- move right
			data:moveright()
		elseif (op == operations.UPSCROLLIMG) then
			-- up scroll image
			data:upscrollimg()
		elseif (op == operations.DOWNSCROLLIMG) then
			-- down scroll image
			data:downscorllimg()
		elseif (op == operations.MOVEDOWN) then
			-- move down
			data:movedown()
		elseif (op == operations.EXIT) then
			-- peer exit
		elseif (op == operations.START) then
			-- start the game
			data:process()
		elseif (op == operations.UPDATE) then
			data:process()
		else
			print("unknown op...")
		end
	end
end

function resettable(tbl)
	local count = #tbl
	while (count > 0) do
		table.remove(tbl, count)
		count = count - 1
	end
end

-------------------------------------------------------------------------------
-- server main
do
	local s = server.init()
	local fdread = fdset.create()
	local fdtmp = fdset.create()
	local selret = 0
	local sockt = 0
	local t_socket_list = {}
	local t_recved_list = {}
	local datalist = {}

	fdread:zero()
	fdread:set(s._socket)		-- add socket to fd_set

	print("socket ", s._socket)
	while (true) do
		fdset.dup(fdtmp, fdread) -- duplicate fd_set
		selret = socket.selectread(fdtmp)
		resettable(t_recved_list)
		resettable(datalist)
		if (selret > 0) then
			for i = 0, selret-1, 1 do
				sockt = fdtmp:getsocket(i)
				if (fdread:isset(sockt)) then
					if (sockt == s._socket) then
						local data = serverdata.create()
						local t_newsockt = t_socket.create()
						socket.accept(s._socket, t_newsockt)
						fdread:set(t_newsockt:getsocket())
						table.insert(t_socket_list, t_newsockt)
						table.insert(s._serverdata, data)
						print("new connection")
					else
						-- handle recv message
						for j = 1, #t_socket_list do
							local st = t_socket_list[j]:getsocket()
							if (sockt == st) then
								-- find out the socket and buffer
								local ret = socket.recv(t_socket_list[j])
								if (ret > 0) then
									table.insert(datalist, s._serverdata[j])
									table.insert(t_recved_list, t_socket_list[j])
								else
									-- connection closed
									fdread:clr(st)
									t_socket_list[j] = nil
									s._serverdata[j] = nil
									table.remove(s._serverdata, j)
									table.remove(t_socket_list, j)
								end

								break
							end
						end
					end
				end
			end
		end

		s:process(t_recved_list, datalist)
		for m = 1, #t_recved_list do
			datalist[m]:update(t_recved_list[m])
		end
	end

	s:shutdown()
end

