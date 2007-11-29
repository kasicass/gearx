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

-------------------------------------------------------------------------------
require("onoffbutton")
require("settings")


-------------------------------------------------------------------------------
sceneoption = {}

-------------------------------------------------------------------------------
local OPTION_PIC_PATH = "data/pic/options/"

local MODE_TEXT = {
	"Window",
	"FullScreen",
}

-------------------------------------------------------------------------------
function sceneoption.init ()
	local self = {}
	self._bg = WBitmap.Load(MAIN_RES_PKG, 
								  OPTION_PIC_PATH .. "background.bmp")

	onoffbutton.init(MAIN_RES_PKG, 
					 OPTION_PIC_PATH .. "check_button_on.bmp",
					 OPTION_PIC_PATH .. "check_button_off.bmp",
					 2, true)
	self._sound = onoffbutton.new(380, 280, 480, 280, settings.isplaysound())
	self._music = onoffbutton.new(380, 205, 480, 205, settings.isplaymusic())

	self._close = button.new(MAIN_RES_PKG,
							 OPTION_PIC_PATH .. "btn_close.bmp",
							 2, true, 584, 137)

	self._leftarrow = button.new(MAIN_RES_PKG,
								 OPTION_PIC_PATH .. "btn_left_arrow.bmp",
								 2, true, 380, 380)
	self._rightarrow = button.new(MAIN_RES_PKG,
								  OPTION_PIC_PATH .. "btn_right_arrow.bmp",
								  2, true, 525, 380)
	self._change = true
	self._mode = settings.isfullscreen() and 2 or 1

	local function LBtnDown(obj)
		return function (x, y)
				   local ret = obj:iscover(x, y)
				   if (ret) then
					   local noerr, msg = pcall(setgamestate,
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
				   return obj:iscover(x, y)
			   end
	end

	local function OnOffMouseDown (obj, music)
		return function (x, y)
				   local ret = obj:iscover(x, y)
				   if ret then 
					   self._change = true
					   if (music) then
						   settings.playmusic(not settings.isplaymusic())
					   else
						   settings.playsound(not settings.isplaysound())
					   end
				   end
				   return ret
			   end
	end

	local function ModeBtnDown (obj, mode)
		return function (x, y)
				   local ret = obj:iscover(x, y)
				   if (ret) then
					   self._mode = mode
					   self._change = true
					   if (mode == 1) then
						   settings.fullscreen(false)
					   else
						   settings.fullscreen(true)
					   end
				   end
				   return ret
			   end
	end

	mouse.regist("LBUTTONDOWN", OnOffMouseDown(self._sound, false))
	mouse.regist("LBUTTONDOWN", OnOffMouseDown(self._music, true))
	mouse.regist("MOUSEMOVE", MouseMoveMsg(self._close))
	mouse.regist("LBUTTONDOWN", LBtnDown(self._close))
	mouse.regist("MOUSEMOVE", MouseMoveMsg(self._leftarrow))
	mouse.regist("MOUSEMOVE", MouseMoveMsg(self._rightarrow))
	mouse.regist("LBUTTONDOWN", ModeBtnDown(self._leftarrow, 1))
	mouse.regist("LBUTTONDOWN", ModeBtnDown(self._rightarrow, 2))

	keyboard.regist ("ESC", function () 
								   pcall(setgamestate, GAME_STATES.MAINMENU)
							   end)

	setmetatable(self, {__index = sceneoption})

	return self
end

function sceneoption:draw (canvas)
	self._leftarrow:draw(canvas)
	self._rightarrow:draw(canvas)
	self._close:draw(canvas)
	self._sound:draw(canvas)
	self._music:draw(canvas)

	font:Draw(canvas, MODE_TEXT[self._mode], 0xff, 415, 385)

	if (self._change) then
		canvas:Change()
		self._change = false
	else
		canvas:UnChang()
	end

	self._bg:Draw(canvas, 184, 125, BLIT_STYLE.BLIT_MASK)
end

function sceneoption:destroy ()
	keyboard.removeall()
	mouse.removeall()
end

