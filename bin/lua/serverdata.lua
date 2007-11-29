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
require("block")
require("blocktable")
require("triblock")
require("sparksys")
require("operations")

-------------------------------------------------------------------------------

serverdata = {}

-------------------------------------------------------------------------------
function serverdata.create ()
	local self = {}
	self._blktbl = blocktable.init()
	self._triblk = triblock.new()
	self._sparksys = sparksys.init()
	self._scatterlist = scatteredblocks.init()
	self._score = 0
	self._state = PLAYING_STATE.PLAYING

	setmetatable(self, {__index = serverdata})

	return self
end

-------------------------------------------------------------------------------
function serverdata:moveleft ()
	local x = self._triblk:xidx() - 1
	local y = self._triblk:yidx() + 1

	if (self._blktbl:getimgidx(x, y) == 0) then
		self._triblk:moveleft()
	end
end

-------------------------------------------------------------------------------
function serverdata:moveright ()
	local x = self._triblk:xidx() + 1
	local y = self._triblk:yidx() + 1
	if (self._blktbl:getimgidx(x, y) == 0) then
		self._triblk:moveright()
	end
end

-------------------------------------------------------------------------------
function serverdata:movedown ()
	if (self._scatterlist:getcount() > 0) then
		return
	end

	local cx = self._triblk:xidx()
	local cy = BLOCK_HEIGHT
	while (cy > 3) do
		if (self._blktbl:getimgidx(cx, cy) == 0) then
			break
		end

		cy = cy - 1
	end

	self._triblk:sety((cy-1)*BLOCK_SIZE-4)
end

-------------------------------------------------------------------------------
function serverdata:upscrollimg ()
	self._triblk:scrollup()
end

-------------------------------------------------------------------------------
function serverdata:downscrollimg ()
	self._triblk:scrolldown()
end

-------------------------------------------------------------------------------
function serverdata:process ()
	local count = self._scatterlist:getcount()
	if (count > 0) then
		-- scattered list
		local tbl = self._scatterlist
		tbl:move()

		if (math.fmod(tbl[1]._y, BLOCK_SIZE) == 0) then
			self._blktbl:resettrunktbl()

			local i = 1
			while (i <= count) do
				local cx = math.floor(tbl[i]._x / BLOCK_SIZE) + 1
				local cy = math.floor(tbl[i]._y / BLOCK_SIZE) + 1
				
				if (cy >= BLOCK_HEIGHT or self._blktbl[cx][cy+1] ~= 0) then
					self._blktbl:add(cx, cy, tbl[i]._imgidx)
					self._blktbl:filltrunktbl(cx, cy)
					table.remove(tbl, i)
					count = count - 1
--					print("remove: ", count)
				else
					i = i + 1
				end
			end

			local trunkcount = self._blktbl:trunkblocks(self._sparksys)
			if trunkcount > 0 then
				self._score = trunkcount * 10 + self._score
				self._blktbl:fillscatteredlist(self._scatterlist)
			end
		end
	else
		-- triblock
		local x, y = self._triblk:xidx(), self._triblk:yidx()
		if (y >= BLOCK_HEIGHT or self._blktbl:getimgidx(x, y+1) ~= 0) then
			self._score = self._blktbl:addtri(self._triblk, 
											  self._scatterlist,
											  self._sparksys)*10 + self._score
			if (self._blktbl[x][y] ~= 0 and y <= 3) then
				self._state = PLAYING_STATE.OVER
				return
			end

			self._triblk:reset()
		else
			self._triblk:movedown()
		end
	end

	self._sparksys:move()
end

-------------------------------------------------------------------------------
function serverdata:update (_t_socket)
	-- send data to client
	-- format:
	--   state,score,triblock_x, triblock_y,imageidx,imageidx,imageidx,
	--   blocktable,
	--   scatteredlist,
	--   sparks\n
	local str = ""
	str = str .. string.format("%d,%d,%d,%d,%d,%d,%d,",
							   self._state,
							   self._score,
							   self._triblk._x,
							   self._triblk._y,
							   self._triblk:getidx(1),
							   self._triblk:getidx(2),
							   self._triblk:getidx(3))

	-- block table
	for i = 1, BLOCK_WIDTH do
		for j = 1, BLOCK_HEIGHT do
			str = str .. self._blktbl[i][j] .. ","
		end
	end

	-- scattered list
	str = str .. self._scatterlist:getcount() .. ","
	-- if (self._scatterlist:getcount() > 0) then
	-- 	print("scattered count: ", self._scatterlist:getcount())
	-- end

	local s1 = ""
	for i = 1, self._scatterlist:getcount() do
		str = str .. string.format("%d,%d,%d,", self._scatterlist[i]._x,
								   self._scatterlist[i]._y,
								   self._scatterlist[i]._imgidx)
	end

	-- sparks
	str = str .. self._sparksys:getcount() .. ","
	-- if (self._sparksys:getcount() > 0) then
	-- 	print("send sparks count: ", self._sparksys:getcount())
	-- end

	for i = 1, self._sparksys:getcount() do
		local _spark = self._sparksys:getspark(i)
		str = str .. string.format("%d,%d,%d\n", 
								   _spark._x,
								   _spark._y,
								   _spark._frame)
	end

	t_socket.senddata(_t_socket, str, #str)
	socket.send(_t_socket)
--	print("send ok")
end




