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

scenelogo = {}

function scenelogo.init ()
	local self = {}
	self._logo = {
		_bmp = WBitmap.Load(MAIN_RES_PKG,
						"data/pic/wf_logo.bmp"),
		_x = 250,
		_y = 200,
	}
	
	self._bg = WBitmap.CreateEmpty(self._logo._bmp:W(), self._logo._bmp:H(), 0xffffff)
	self._bgm = music.Load(MAIN_RES_PKG, "data/sound/game_exit.ogg", music.TYPE.STREAM)
	self._bgm:Play(music.TYPE.STREAM)
	
	setmetatable(self, {__index = scenelogo})
	
	return self
end

function scenelogo:destroy ()
	self._bgm:UnLoad(music.TYPE.STREAM)
	self._bgm = nil
	self._bg = nil
	self._logo._bmp = nil
	self = nil
end

local alpha = 255
function scenelogo:draw (canvas)
	if (alpha <= 0) then
		local ret, msg = pcall(setgamestate, GAME_STATES.MAINMENU)
		if (not ret) then
			print(msg)
		end
		
		return 
	end

	canvas:Change()
	self._logo._bmp:SetData(alpha)
	self._logo._bmp:Draw(canvas, self._logo._x, self._logo._y, BLIT_STYLE.BLIT_TRANS)
	self._bg:Draw(canvas, self._logo._x, self._logo._y, BLIT_STYLE.BLIT_COPY)
	alpha = alpha - 1
end



