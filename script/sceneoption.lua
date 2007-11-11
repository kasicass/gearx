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

-------------------------------------------------------------------------------
dofile("../script/onoffbutton.lua")

-------------------------------------------------------------------------------
SceneOption = {}

-------------------------------------------------------------------------------
local OPTION_PIC_PATH = "data/pic/options/"

local MODE_TEXT = {
	"Window",
	"FullScreen",
}

-------------------------------------------------------------------------------
function SceneOption.Init ()
	local self = {}
	self._bg = WBitmap.Load(MAIN_RES_PKG, 
								  OPTION_PIC_PATH .. "background.bmp")

	OnOffButton.Init(MAIN_RES_PKG, 
					 OPTION_PIC_PATH .. "check_button_on.bmp",
					 OPTION_PIC_PATH .. "check_button_off.bmp",
					 2, true)
	self._sound = OnOffButton.New(380, 280, 480, 280, IsPlaySound())
	self._music = OnOffButton.New(380, 205, 480, 205, IsPlayMusic())

--[[
	self._sound = OnOffButton.New(MAIN_RES_PKG, 
								  OPTION_PIC_PATH .. "check_button_on.bmp",
								  OPTION_PIC_PATH .. "check_button_off.bmp",
								  2, true, 
								  380, 205,
								  480, 205, IsPlaySound())
								  
	self._music = OnOffButton.New(MAIN_RES_PKG, 
								  OPTION_PIC_PATH .. "check_button_on.bmp",
								  OPTION_PIC_PATH .. "check_button_off.bmp",
								  2, true,
								  380, 280,
								  480, 280, IsPlayMusic())
--]]
	self._close = Button.New(MAIN_RES_PKG,
							 OPTION_PIC_PATH .. "btn_close.bmp",
							 2, true, 584, 137)

	self._leftarrow = Button.New(MAIN_RES_PKG,
								 OPTION_PIC_PATH .. "btn_left_arrow.bmp",
								 2, true, 380, 380)
	self._rightarrow = Button.New(MAIN_RES_PKG,
								  OPTION_PIC_PATH .. "btn_right_arrow.bmp",
								  2, true, 525, 380)
	self._change = true
	self._mode = IsFullScreen() and 2 or 1

	local function LBtnDown(obj)
		return function (x, y)
				   local ret = obj:IsCover(x, y)
				   if (ret) then
					   local noerr, msg = pcall(SetGameState,
												GAME_STATES.MAINMENU)
					   if (not noerr) then
						   print(msg)
					   end
				   end

				   return ret
			   end
	end

	local function MouseMoveMsg (obj)
		return function (x, y)
				   return obj:IsCover(x, y)
			   end
	end

	local function OnOffMouseDown (obj, music)
		return function (x, y)
				   local ret = obj:IsCover(x, y)
				   if ret then 
					   self._change = true
					   if (music) then
						   GAME_SETTING.MUSIC = not IsPlayMusic()
					   else
						   GAME_SETTING.SOUND = not IsPlaySound()
					   end
				   end
				   return ret
			   end
	end

	local function ModeBtnDown (obj, mode)
		return function (x, y)
				   local ret = obj:IsCover(x, y)
				   if (ret) then
					   self._mode = mode
					   self._change = true
					   if (mode == 1) then
						   FullScreen(false)
					   else
						   FullScreen(true)
					   end
				   end
				   return ret
			   end
	end

	MouseListener.Regist("LBUTTONDOWN", OnOffMouseDown(self._sound, false))
	MouseListener.Regist("LBUTTONDOWN", OnOffMouseDown(self._music, true))
	MouseListener.Regist("MOUSEMOVE", MouseMoveMsg(self._close))
	MouseListener.Regist("LBUTTONDOWN", LBtnDown(self._close))
	MouseListener.Regist("MOUSEMOVE", MouseMoveMsg(self._leftarrow))
	MouseListener.Regist("MOUSEMOVE", MouseMoveMsg(self._rightarrow))
	MouseListener.Regist("LBUTTONDOWN", ModeBtnDown(self._leftarrow, 1))
	MouseListener.Regist("LBUTTONDOWN", ModeBtnDown(self._rightarrow, 2))

	KeyListener.Regist ("ESC", function () 
								   pcall(SetGameState, GAME_STATES.MAINMENU)
							   end)

	setmetatable(self, {__index = SceneOption})

	return self
end

function SceneOption:Draw (canvas)
	self._leftarrow:Draw(canvas)
	self._rightarrow:Draw(canvas)
	self._close:Draw(canvas)
	self._sound:Draw(canvas)
	self._music:Draw(canvas)

	font:Draw(canvas, MODE_TEXT[self._mode], 0xff, 415, 385)

	if (self._change) then
		canvas:Change()
		self._change = false
	else
		canvas:UnChang()
	end

	self._bg:Draw(canvas, 184, 125, BLIT_STYLE.BLIT_MASK)
end

function SceneOption:Destroy ()
	KeyListener.RemoveAll()
	MouseListener.RemoveAll()
end

