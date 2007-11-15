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

	$Id: $
	ChenZaichun@gmail.com
--]]

-------------------------------------------------------------------------------


SceneCredit = {}

local CREDIT_PIC_PATH = "data/pic/credits/"

-------------------------------------------------------------------------------
function SceneCredit.Init()
	local self = {}
	self._bg = WBitmap.Load(MAIN_RES_PKG,
							CREDIT_PIC_PATH .. "background.bmp")

	self._change = true

	KeyListener.Regist("ESC", function ()
								  pcall(SetGameState, GAME_STATES.MAINMENU)
							  end)

	setmetatable(self, {__index = SceneCredit})

	return self
end

-------------------------------------------------------------------------------
function SceneCredit:Draw(canvas)
	if (self._change) then
		canvas:Change()
		self._change = false
	else
		canvas:UnChange()
	end

	self._bg:Draw(canvas, 0, 0, BLIT_STYLE.BLIT_COPY)
end

-------------------------------------------------------------------------------
function SceneCredit:Destroy ()
	KeyListener.RemoveAll()
end
