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

	$Id$
	ChenZaichun@gmail.com
--]]

-------------------------------------------------------------------------------
package.cpath = "../" .. package.cpath

PLAYING_PIC_PATH = "data/pic/playing/"

local DEFAULT_SERVER_PORT = 5158

-------------------------------------------------------------------------------
require("score")
require("gears")
require("sparksys")
require("triblock")
require("block")
require("mouse")
require("keyboard")
require("blocktable")
require("socket")
require("sparkimg")
require("operations")

-------------------------------------------------------------------------------
sceneplaying = {}

-- tasks
local PLAYING_TASKS = {}

-------------------------------------------------------------------------------
-- to start
function sceneplaying:tostart (canvas)
	self._tostart = WBitmap.Load(MAIN_RES_PKG,
								 PLAYING_PIC_PATH .. "to_start.bmp")
	keyboard.regist("SPACE", function ()
								 self._state = PLAYING_STATE.PLAYING
								 coroutine.resume(PLAYING_TASKS._tostart,
												  canvas)
							 end)


	coroutine.yield()
	canvas:Change()

	while (self._state == PLAYING_STATE.INIT) do
		self._tostart:Draw(canvas, (800-self._tostart:W())/2,
						   (600-self._tostart:H())/2,
						   BLIT_STYLE.BLIT_MASK)
		canvas = coroutine.yield()
	end

	keyboard.remove("SPACE")
	self._tostart = nil
end

-- playing
function sceneplaying:playing (canvas)

	local function releaseRes()
		print("playing release")
		keyboard.remove("UP")
		keyboard.remove("DOWN")
		keyboard.remove("LEFT")
		keyboard.remove("RIGHT")
		keyboard.remove("P")
		keyboard.remove("SPACE")

		self._gears = nil
		self._blocks = nil
		self._triblock = nil
		self._sparksys = nil
	end
	
	self._gears = gears.init()
 	self._blocks = blocktable.init()
 	self._triblock = triblock.new()
	self._sparksys = sparksys.init()
	self._sparkimg = sparkimg.init()
	self._scatterlist = scatteredblocks.init()
	self._score = 0

	keyboard.regist ("ESC", function () 
								local op = "" .. operations.EXIT
								t_socket.senddata(self._t_socket, op, #op)
								socket.send(self._t_socket)
								releaseRes()
								pcall(setgamestate, GAME_STATES.MAINMENU)
							   end)

	keyboard.regist("UP", function ()
								 if self._state ~= PLAYING_STATE.PLAYING then
									 return
								 end

								 local op = "" .. operations.UPSCROLLIMG
								 t_socket.senddata(self._t_socket, op, #op)
								 socket.send(self._t_socket)
							 end)
	keyboard.regist("DOWN", function ()
								if self._state ~= PLAYING_STATE.PLAYING then
									return
								end

								local op = "" .. operations.DOWNSCROLLIMG
								t_socket.senddata(self._t_socket, op, #op)
								socket.send(self._t_socket)
							end)
	keyboard.regist("LEFT", function ()
								if self._state ~= PLAYING_STATE.PLAYING then
									return
								end

								local op = "" .. operations.MOVELEFT
								t_socket.senddata(self._t_socket, op, #op)
								socket.send(self._t_socket)
							end)
	keyboard.regist("RIGHT", function ()
								 if self._state ~= PLAYING_STATE.PLAYING then
									 return
								 end

								 local op = "" .. operations.MOVERIGHT
								 t_socket.senddata(self._t_socket, op, #op)
								 socket.send(self._t_socket)
							 end)
	keyboard.regist("P", function () 
								if (self._state == PLAYING_STATE.PLAYING) then
									self._state = PLAYING_STATE.PAUSE
								elseif (self._state == PLAYING_STATE.PAUSE) then
									self._state = PLAYING_STATE.PLAYING
								end
							end)
	keyboard.regist("SPACE", function ()
								 if self._state ~= PLAYING_STATE.PLAYING then
									 return
								 end
									
								 if (self._scatterlist:getcount() > 0) then
									 return
								 end

								 local op = "" .. operations.MOVEDOWN
								 t_socket.senddata(self._t_socket, op, #op)
								 socket.send(self._t_socket)									
							 end)

	coroutine.yield()

	while (true) do
		local op = "" .. operations.UPDATE
		t_socket.senddata(self._t_socket, op, #op)
		socket.send(self._t_socket)	
		socket.recv(self._t_socket)
		local retdata = t_socket.recvdata(self._t_socket)
		-- process recv data
		local iend, _s

		-- state
		_, iend, _s = string.find(retdata, "^(%d+)")
		self._state = tonumber(_s)
		if (self._state == PLAYING_STATE.OVER) then
			break
		end
		
		-- score
		retdata = string.sub(retdata, iend+2)
		_, iend, _s = string.find(retdata, "^(%d+)")
		self._score = tonumber(_s)
		
		retdata = string.sub(retdata, iend+2)

		-- triblock
		-- x
		_, iend, _s = string.find(retdata, "^(%d+)")
		self._triblock._x = tonumber(_s)
--		print(self._triblock._x)
		retdata = string.sub(retdata, iend+2)

		-- y
		_, iend, _s = string.find(retdata, "^(%d+)")
		self._triblock._y = tonumber(_s)
		retdata = string.sub(retdata, iend+2)

		-- img[1]
		_, iend, _s = string.find(retdata, "^(%d+)")
		self._triblock:setimgidx(1, tonumber(_s))
		retdata = string.sub(retdata, iend+2)

		-- img[2]
		_, iend, _s = string.find(retdata, "^(%d+)")
		self._triblock:setimgidx(2, tonumber(_s))
		retdata = string.sub(retdata, iend+2)

		-- img[3]
		_, iend, _s = string.find(retdata, "^(%d+)")
		self._triblock:setimgidx(3, tonumber(_s))
		retdata = string.sub(retdata, iend+2)

		for i = 1, BLOCK_WIDTH do
			for j = 1, BLOCK_HEIGHT do
				_, iend, _s = string.find(retdata, "^(%d+)")
				self._blocks[i][j] = tonumber(_s)
		
				retdata = string.sub(retdata, iend+2)
			end
		end

		_, iend, _s = string.find(retdata, "^(%d+)")
		local count = tonumber(_s)
		
		retdata = string.sub(retdata, iend+2)		
		self._scatterlist:reset()
		for i = 1, count do
			local x , y, idx
			_, iend, _s = string.find(retdata, "^(%d+)")
			retdata = string.sub(retdata, iend+2)
			x = tonumber(_s)
			_, iend, _s = string.find(retdata, "^(%d+)")
			retdata = string.sub(retdata, iend+2)
			y = tonumber(_s)
			_, iend, _s = string.find(retdata, "^(%d+)")
			retdata = string.sub(retdata, iend+2)
			idx = tonumber(_s)
			self._scatterlist:add(block.new(x, y, idx))
		end

		_, iend, _s = string.find(retdata, "^(%d+)")
		count = tonumber(_s)
		retdata = string.sub(retdata, iend+2)		
		self._sparksys:reset()

		for i = 1, count do
			local x , y, idx
			_, iend, _s = string.find(retdata, "^(%d+)")
			retdata = string.sub(retdata, iend+2)
			x = tonumber(_s)
			_, iend, _s = string.find(retdata, "^(%d+)")
			retdata = string.sub(retdata, iend+2)
			y = tonumber(_s)
			_, iend, _s = string.find(retdata, "^(%d+)")
			retdata = string.sub(retdata, iend+2)
			idx = tonumber(_s)
			self._sparksys:add(x, y, idx)
		end

		local count = self._scatterlist:getcount()
		if (count > 0) then
			-- scattered list
			local tbl = self._scatterlist
			tbl:draw(canvas, self._gears)
		else
			-- triblock
			self._triblock:draw(canvas, self._gears)
		end

		canvas:Change()
		font:Draw(canvas, "" .. self._score, 0xff, 132, 405)

 		canvas:Change()
		self._sparkimg:draw(canvas, self._sparksys._sparks)

		canvas:Change()
		self._blocks:draw(canvas, self._gears)
		coroutine.yield()
	end
end

-- pause
function sceneplaying:pause (canvas)
	self._anipause = animation.new(MAIN_RES_PKG,
								   PLAYING_PIC_PATH .. "pause.bmp",
								   4, false)
	self._anipause:setpos((800-self._anipause:w())/2,
						  (600-self._anipause:h())/2)

	self._anipause:setduration(60)
	self._anipause:start()

	coroutine.yield()

	while (self._state ~= PLAYING_STATE.OVER) do
		self._anipause:draw(canvas)
		coroutine.yield()
	end

--	print("pause release")
	self._anipause = nil
end

-- over
function sceneplaying:over (canvas)
	local function relaseRes () 
		keyboard.remove("BACKSPACE")
		keyboard.remove("ENTER")
		keyboard.removealllistener()
	end

	local name = ""
	keyboard.registall(function (key)
							  local char

							  if (key+1 >= string.byte('A') and
							   		key+1 <= string.byte('Z')) then
								  char = string.char(key)
								  name = name .. string.upper(char)
								  return true
							  elseif (key+1 >= string.byte('a') and
						  			key+1 <= string.byte('z')) then
								  char = string.char(key)
								  char = string.upper(char)
								  name = name .. string.upper(char)
								  return true
							  elseif (key >= string.byte('0') and
					   				key <= string.byte('9')) then
								  char = string.char(key)
								  name = name .. string.upper(char)
								  return true
							  else
								  return false
							  end
						  end)

	keyboard.regist("ENTER", function ()
								 score.addacoretohighscore(name, self._score)
								 relaseRes()
								 pcall(setgamestate, GAME_STATES.HIGHSCORE)
								end)
	keyboard.regist("BACKSPACE", function ()
									 local len = string.len(name)
									 if (len == 0) then return end
									 name = string.sub(name, 1, len-1)
								 end)
										

	self._bmpplayername = WBitmap.Load(MAIN_RES_PKG,
									   PLAYING_PIC_PATH .. "enter_player_name.bmp")

	coroutine.yield()
	
	while (true) do
		print("before check score")
		if (score.checkhighscore(self._score)) then
			print("check ok")
			canvas:Change()
			font:Draw(canvas, name, 0xff, 370, 300)
			self._bmpplayername:Draw(canvas, 
									 (800-self._bmpplayername:W()) / 2,
									 (600-self._bmpplayername:H()) / 2,
									 BLIT_STYLE.BLIT_MASK)
			coroutine.yield()
		else
			relaseRes()
			break
		end
	end

--	pcall(SetGameState, GAME_STATES.GAMEOVER)
end
-------------------------------------------------------------------------------
-- init scene playing
-- 
function sceneplaying.init ()
	local self = {}

	-- init socket lib
	socket.init()
	self._t_socket = t_socket.create() -- create socket

	self._bg = WBitmap.Load(MAIN_RES_PKG, 
							PLAYING_PIC_PATH .. "background.bmp")
	self._bgm = music.Load(MAIN_RES_PKG, 
						   SOUND_PATH .. "game_playing.ogg",
						   music.TYPE.STREAM)
	self._change = true
	self._state = PLAYING_STATE.INIT

	PLAYING_TASKS._tostart = coroutine.create(function (canvas)
												  self:tostart(canvas)
											  end)
	PLAYING_TASKS._playing = coroutine.create(function (canvas)
												  self:playing(canvas)
											  end)
	PLAYING_TASKS._pause = coroutine.create(function (canvas)
												self:pause(canvas)
											end)
	PLAYING_TASKS._over = coroutine.create(function (canvas)
											   self:over(canvas)
										   end)

	if (settings.isplaymusic()) then
		self._bgm:Play(music.TYPE.STREAM)
	end

	setmetatable(self, {__index = sceneplaying})
	socket.connect(self._t_socket, DEFAULT_SERVER_PORT, "192.168.0.233")

	return self
end

-------------------------------------------------------------------------------
function sceneplaying:destroy ()
	-- release socket lib
	self._t_socket = nil
--	socket.shutdown()

	self._bgm:UnLoad(music.TYPE.STREAM)
	self._bgm = nil
	self._bg = nil
end

-------------------------------------------------------------------------------
function sceneplaying:draw (canvas)
	if (self._state == PLAYING_STATE.INIT) then
		coroutine.resume(PLAYING_TASKS._tostart, canvas)
	elseif (self._state == PLAYING_STATE.PLAYING) then
		coroutine.resume(PLAYING_TASKS._playing, canvas)
	elseif (self._state == PLAYING_STATE.PAUSE) then
		coroutine.resume(PLAYING_TASKS._pause, canvas)
	elseif (self._state == PLAYING_STATE.OVER) then
		coroutine.resume(PLAYING_TASKS._over, canvas)
	end

	if (self._change) then
		canvas:Change()
		self._change = false
	else
		canvas:UnChange()
	end

	self._bg:Draw(canvas, 0, 0, BLIT_STYLE.BLIT_COPY)
end

-------------------------------------------------------------------------------


