-- emacs: -*- mode: lua; coding: gb2312 -*- TAB SIZE: 4 -*- 

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
PLAYING_PIC_PATH = "data/pic/playing/"

-------------------------------------------------------------------------------
dofile("../script/score.lua")
dofile("../script/gears.lua")
dofile("../script/spark.lua")
dofile("../script/triblock.lua")
dofile("../script/block.lua")

-------------------------------------------------------------------------------
ScenePlaying = {}

-- playing scene state
PLAYING_STATE = {
	INIT = 1,
	PLAYING = 2,
	PAUSE = 3,
	OVER = 4,
}

-- tasks
local PLAYING_TASKS = {}

-------------------------------------------------------------------------------
-- to start
function ScenePlaying:ToStart (canvas)
	self._tostart = WBitmap.Load(MAIN_RES_PKG,
								 PLAYING_PIC_PATH .. "to_start.bmp")
	KeyListener.Regist("SPACE", function ()
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

	KeyListener.Remove("SPACE")
	self._tostart = nil
end

-- playing
function ScenePlaying:Playing (canvas)

	local function releaseRes()
		print("playing release")
		KeyListener.Remove("UP")
		KeyListener.Remove("DOWN")
		KeyListener.Remove("LEFT")
		KeyListener.Remove("RIGHT")
		KeyListener.Remove("P")
		KeyListener.Remove("SPACE")

		self._gears = nil
		self._blocks = nil
		self._triblock = nil
		self._sparksys = nil
	end
	
	self._gears = Gears.Init()
 	self._blocks = BlockTable.Init()
 	self._triblock = TriBlock.New()
	self._sparksys = SparkSystem.Init()
	self._scatterlist = ScatteredBlocks.Init()
	self._score = 0

	KeyListener.Regist ("ESC", function () 
								   releaseRes()
								   pcall(SetGameState, GAME_STATES.MAINMENU)
							   end)

	KeyListener.Regist("UP", function ()
								 if self._state ~= PLAYING_STATE.PLAYING then
									 return
								 end

								 self._triblock:ScrollUP()
							 end)
	KeyListener.Regist("DOWN", function ()
								 if self._state ~= PLAYING_STATE.PLAYING then
									 return
								 end

								   self._triblock:ScrollDown()
							   end)
	KeyListener.Regist("LEFT", function ()
								 if self._state ~= PLAYING_STATE.PLAYING then
									 return
								 end

								   local x = self._triblock:XIdx() - 1
								   local y = self._triblock:YIdx() + 1
								   if (self._blocks:GetImgIdx(x, y) == 0) then
									   self._triblock:MoveLeft()
								   end
							   end)
	KeyListener.Regist("RIGHT", function ()
								 if self._state ~= PLAYING_STATE.PLAYING then
									 return
								 end

									local x = self._triblock:XIdx() + 1
									local y = self._triblock:YIdx() + 1
									if (self._blocks:GetImgIdx(x, y) == 0) then
										self._triblock:MoveRight()
									end
								end)
	KeyListener.Regist("P", function () 
								if (self._state == PLAYING_STATE.PLAYING) then
									self._state = PLAYING_STATE.PAUSE
								elseif (self._state == PLAYING_STATE.PAUSE) then
									self._state = PLAYING_STATE.PLAYING
								end
							end)
	KeyListener.Regist("SPACE", function ()
									if self._state ~= PLAYING_STATE.PLAYING then
										return
									end
									
									if (self._scatterlist:GetCount() > 0) then
										return
									end
									
									local cx = self._triblock:XIdx()
									local cy = BLOCK_HEIGHT
									while (cy > 3) do
										if (self._blocks:GetImgIdx(cx, cy) == 0) then
											break
										end

										cy = cy - 1
									end

									self._triblock:SetY((cy*BLOCK_SIZE-4))
								end)

	coroutine.yield()

	while (self._state ~= PLAYING_STATE.OVER) do
		local count = self._scatterlist:GetCount()
		if (count > 0) then
			-- scattered list
			local tbl = self._scatterlist
			tbl:Move()
	
			if (math.fmod(tbl[1]._y, BLOCK_SIZE) == 0) then
				self._blocks:ResetTrunkTbl()
				
				local i = 1
				while (i <= count) do
					local cx = math.floor(tbl[i]._x / BLOCK_SIZE) + 1
					local cy = math.floor(tbl[i]._y / BLOCK_SIZE) + 1

					if (cy >= BLOCK_HEIGHT or self._blocks[cx][cy+1] ~= 0) then
						self._blocks:Add(cx, cy, tbl[i]._imgidx)
						self._blocks:FillTrunkTbl(cx, cy)
						table.remove(tbl, i)
						count = count - 1
					else
						i = i + 1
					end
				end

				local trunkcount = self._blocks:TrunkBlocks(self._sparksys)
				if trunkcount > 0 then
					self._score = trunkcount * 10 + self._score
					self._blocks:FillScatteredList(self._scatterlist)
				end
			end
			tbl:Draw(canvas, self._gears)
		else
			-- triblock
			local x, y = self._triblock:XIdx(), self._triblock:YIdx()
			if (y >= BLOCK_HEIGHT or self._blocks:GetImgIdx(x, y+1) ~= 0) then
				self._score = self._blocks:AddTri(self._triblock, self._scatterlist,
											  self._sparksys)*10 + self._score
				if (self._blocks[x][y] ~= 0 and y <= 3) then
					print("over")
					self._state = PLAYING_STATE.OVER
					releaseRes()
					break
				end

				self._triblock:Reset()
--				print("reset")
			else
				self._triblock:MoveDown()
				canvas:Change()
				self._triblock:Draw(canvas, self._gears)
			end
		end

		canvas:Change()
		font:Draw(canvas, "" .. self._score, 0xff, 132, 405)

 		self._sparksys:Move()
 		canvas:Change()
 		self._sparksys:Draw(canvas)

		canvas:Change()
		self._blocks:Draw(canvas, self._gears)
		coroutine.yield()
	end
end

-- pause
function ScenePlaying:Pause (canvas)
	self._anipause = Animation.New(MAIN_RES_PKG,
								   PLAYING_PIC_PATH .. "pause.bmp",
								   4, false)
	self._anipause:SetPos((800-self._anipause:W())/2,
						  (600-self._anipause:H())/2)

	self._anipause:SetDuration(60)
	self._anipause:Start()

	coroutine.yield()

	while (self._state ~= PLAYING_STATE.OVER) do
		self._anipause:Draw(canvas)
		coroutine.yield()
	end

	print("pause release")
	self._anipause = nil
end

-- over
function ScenePlaying:Over (canvas)
	local function relaseRes () 
		KeyListener.Remove("BACKSPACE")
		KeyListener.Remove("ENTER")
		KeyListener.RemoveAllListener()
	end

	local name = ""
	KeyListener.RegistAll(function (key)
--							  print("check key")
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

	KeyListener.Regist("ENTER", function ()
									AddScoreToHighScore(name, self._score)
									relaseRes()
									print("before his")
									pcall(SetGameState, GAME_STATES.HIGHSCORE)
									print("end his")
								end)
	KeyListener.Regist("BACKSPACE", function ()
										local len = string.len(name)
										if (len == 0) then return end
										name = string.sub(name, 1, len-1)
									end)
										

	self._bmpplayername = WBitmap.Load(MAIN_RES_PKG,
									   PLAYING_PIC_PATH .. "enter_player_name.bmp")

	coroutine.yield()
	
	while (true) do
		if (CheckHighScore(self._score)) then
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
function ScenePlaying.Init ()
	local self = {}

	self._bg = WBitmap.Load(MAIN_RES_PKG, 
							PLAYING_PIC_PATH .. "background.bmp")
	self._bgm = Music.Load(MAIN_RES_PKG, 
						   SOUND_PATH .. "game_playing.ogg",
						   Music.TYPE.STREAM)
	self._change = true
	self._state = PLAYING_STATE.INIT

	PLAYING_TASKS._tostart = coroutine.create(function (canvas)
												  self:ToStart(canvas)
											  end)
	PLAYING_TASKS._playing = coroutine.create(function (canvas)
												  self:Playing(canvas)
											  end)
	PLAYING_TASKS._pause = coroutine.create(function (canvas)
												self:Pause(canvas)
											end)
	PLAYING_TASKS._over = coroutine.create(function (canvas)
											   self:Over(canvas)
										   end)

	if (IsPlayMusic()) then
		self._bgm:Play(Music.TYPE.STREAM)
	end

	setmetatable(self, {__index = ScenePlaying})

	return self
end

-------------------------------------------------------------------------------
function ScenePlaying:Destroy ()
	printf("ScenePlaying:Destroy")
	self._bgm:UnLoad(Music.TYPE.STREAM)
	self._bgm = nil
	self._bg = nil
end

-------------------------------------------------------------------------------
function ScenePlaying:Draw (canvas)
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


