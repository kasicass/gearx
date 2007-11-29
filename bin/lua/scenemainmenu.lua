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
-- requires
require("button")
require("music")
require("animation")
require("settings")
require("mouse")
require("keyboard")

-------------------------------------------------------------------------------
scenemainmenu = {}

local MAINMENU_SCENE_PIC_PATH = "data/pic/mainmenu/"

-------------------------------------------------------------------------------
-- 
function scenemainmenu.init ()
	local self = {}

	-- background picture
	self._bg = WBitmap.Load(MAIN_RES_PKG,
			MAINMENU_SCENE_PIC_PATH .. "main_menu_bg.bmp")

	-- button start
	self._btn_start = button.new(MAIN_RES_PKG, 
					MAINMENU_SCENE_PIC_PATH .. "btn_start.bmp", 
					 2, true, 295, 460)
	self._btn_option = button.new(MAIN_RES_PKG,
					MAINMENU_SCENE_PIC_PATH .. "btn_options.bmp",
					  2, true, 530, 530)
	self._btn_highscore = button.new(MAIN_RES_PKG,
					 MAINMENU_SCENE_PIC_PATH .. "btn_highscore.bmp",
					 2, true, 580, 480)
	self._btn_credit = button.new(MAIN_RES_PKG,
				  MAINMENU_SCENE_PIC_PATH .. "btn_credits.bmp",
				  2, true, 660, 430)
	self._btn_exit = button.new(MAIN_RES_PKG,
					MAINMENU_SCENE_PIC_PATH .. "btn_exit.bmp",
					2, true, 660, 530)

	self._bgm = music.Load(MAIN_RES_PKG, SOUND_PATH .. "main_menu.ogg", 
							music.TYPE.STREAM)
	self._btn_hover = music.Load(MAIN_RES_PKG, 
				SOUND_PATH .. "mouse_on_button.wav",
				music.TYPE.SAMPLE)
	if (settings.isplaymusic()) then
		self._bgm:Play(music.TYPE.STREAM)
	end

--	local lastbtn = -1
	local function BtnMouseMoveMsg (obj)
		return function (x, y) 
				   local ret = button.iscover(obj, x, y)
				   if (ret) then
--					   if (lastbtn ~= obj) then
					   if (settings.isplaysound()) then
						   self._btn_hover:Play(music.TYPE.SAMPLE)
--						   lastbtn = obj
					   end
--					   end
				   end
				   return ret
			   end
	end

	local function BtnMouseDown (obj, state)
		return function (x, y)
				   local ret = obj:iscover(x, y) 
				   if ret then
					   local noerr, msg = pcall(setgamestate, state)
					   if (not noerr) then
						   print(msg)
					   end
				   end

				   return ret
			   end
	end

	mouse.regist("MOUSEMOVE", BtnMouseMoveMsg(self._btn_start))
	mouse.regist("MOUSEMOVE", BtnMouseMoveMsg(self._btn_exit))
	mouse.regist("MOUSEMOVE", BtnMouseMoveMsg(self._btn_option))
	mouse.regist("MOUSEMOVE", BtnMouseMoveMsg(self._btn_credit))
	mouse.regist("MOUSEMOVE", BtnMouseMoveMsg(self._btn_highscore))

	mouse.regist("LBUTTONDOWN", 
						 BtnMouseDown(self._btn_start, GAME_STATES.PLAYING))
	mouse.regist("LBUTTONDOWN", 
						 BtnMouseDown(self._btn_option, GAME_STATES.OPTION))
	mouse.regist("LBUTTONDOWN",
						 BtnMouseDown(self._btn_highscore, GAME_STATES.HIGHSCORE))
	mouse.regist("LBUTTONDOWN",
						 BtnMouseDown(self._btn_credit, GAME_STATES.CREDIT))

	mouse.regist("LBUTTONDOWN",
						 function (x, y) 
							 local ret = self._btn_exit:iscover(x, y)
							 if (ret) then
								 Quit()
							 end
							 return ret
						 end)

	keyboard.regist("ESC", function () Quit() end)

	self._ani = animation.new(MAIN_RES_PKG, 
							  "data/pic/mainmenu/mainmenu_cucuma.bmp",
							  4, false, 0, 400, 300)

	self._ani:setduration(60)
	self._ani:start()

	self._change = true
	setmetatable(self, {__index = scenemainmenu})

	return self
end

function scenemainmenu:destroy ()
	mouse.removeall()
	keyboard.removeall()
--	print("scenemainmenu:Destory")
	self._bgm:UnLoad(music.TYPE.STREAM)
	self._btn_hover:UnLoad(music.TYPE.SAMPLE)
	for v, t in pairs(self) do
		self[v] = nil
	end
end

function scenemainmenu:draw (canvas)
	self._btn_option:draw(canvas)
	self._btn_credit:draw(canvas)
	self._btn_highscore:draw(canvas)
	self._btn_exit:draw(canvas)
	self._btn_start:draw(canvas) 
	self._ani:draw(canvas)
	if (self._change) then
		canvas:Change()
		self._change = false
	else
		canvas:UnChange()
	end
	
	-- call bitmap draw
	self._bg:Draw(canvas, 0, 0, BLIT_STYLE.BLIT_COPY)
end
