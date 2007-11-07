
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

	TAB SIZE: 4
--]]

-------------------------------------------------------------------------------


SceneHighScore = {}

local HIGHSCORE_PIC_PATH = "data/pic/highscore/"

-------------------------------------------------------------------------------
function SceneHighScore.Init ()
	local self = {}

	self._bg = WBitmap.Load(MAIN_RES_PKG,
							HIGHSCORE_PIC_PATH .. "background.bmp")

	KeyListener.Regist("ESC", function ()
								  pcall(SetGameState, GAME_STATES.MAINMENU)
							  end)

	self._change = true
	setmetatable(self, {__index = SceneHighScore})

	return self
end

-------------------------------------------------------------------------------
function SceneHighScore:Destroy()
	KeyListener.RemoveAll()
end

-------------------------------------------------------------------------------
function SceneHighScore:Draw (canvas)
	if (self._change) then
		canvas:Change()
		self._change = false
	else
		canvas:UnChange()
	end

	self._bg:Draw(canvas, 0, 0, BLIT_STYLE.BLIT_COPY)
end
