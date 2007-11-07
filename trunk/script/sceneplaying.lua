-- emacs: -*- lua-mode -*- TAB SIZE: 4 -*- 

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
dofile("../script/gears.lua")
dofile("../script/triblock.lua")
dofile("../script/block.lua")

-------------------------------------------------------------------------------
ScenePlaying = {}

-------------------------------------------------------------------------------
function ScenePlaying.Init ()
	local self = {}

	self._bg = WBitmap.Load(MAIN_RES_PKG, 
							PLAYING_PIC_PATH .. "background.bmp")
	self._bgm = Music.Load(MAIN_RES_PKG, 
						   SOUND_PATH .. "game_playing.ogg",
						   Music.TYPE.STREAM)
	self._change = true

	if (IsPlayMusic()) then
		self._bgm:Play(Music.TYPE.STREAM)
	end

	self._gears = Gears.Init()
 	self._blocks = Block.Init()
 	self._triblock = TriBlock.New()

	setmetatable(self, {__index = ScenePlaying})

	KeyListener.Regist ("ESC", function () 
								   pcall(SetGameState, GAME_STATES.MAINMENU)
							   end)

	KeyListener.Regist("UP", function ()
								 self._triblock:ScrollUP()
							 end)
	KeyListener.Regist("DOWN", function ()
								   self._triblock:ScrollDown()
							   end)
	KeyListener.Regist("LEFT", function ()
								   self._triblock:MoveLeft()
							   end)
	KeyListener.Regist("RIGHT", function ()
									self._triblock:MoveRight()
								end)

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
	x, y = self._triblock:XIdx(), self._triblock:YIdx()
	print("Index: ", self._blocks:GetImgIdx(x, y))
	-- check 
 --	if (self._blocks:GetInfo(x,y) ~= 0 or (y+1) >= BLOCK_HEIGHT) then
--	if ((y+1) >= BLOCK_HEIGHT) then
-- 		print("reset")
 --		self._blocks:AddTri(self._triblock)
--	if ((y+1) > BLOCK_HEIGHT) then
 --		self._triblock:Reset()
-- 	else
		self._triblock:Move()
-- 	end

	canvas:Change()
--	self._triblock:Draw(canvas, self._gears:GetImg(self._triblock:GetIdx(1)))

--	self._triblock:Draw(canvas, self._gears)
--	self._blocks:Draw(canvas, self._gears)

	if (self._change) then
		canvas:Change()
		self._change = false
	else
		canvas:UnChange()
	end

	self._bg:Draw(canvas, 0, 0, BLIT_STYLE.BLIT_COPY)
end

-------------------------------------------------------------------------------


