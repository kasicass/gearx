-- emacs: -*- mode: lua; coding: gb2312 -*- TAB SIZE: 4 -*- 

-------------------------------------------------------------------------------


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
SceneMainMenu = {}

local MAINMENU_SCENE_PIC_PATH = "data/pic/mainmenu/"

-------------------------------------------------------------------------------
-- 
function SceneMainMenu.Init ()
	local self = {}

	-- background picture
	self._bg = WBitmap.Load(MAIN_RES_PKG,
			MAINMENU_SCENE_PIC_PATH .. "main_menu_bg.bmp")

	-- button start
	self._btn_start = Button.New(MAIN_RES_PKG, 
					MAINMENU_SCENE_PIC_PATH .. "btn_start.bmp", 
					 2, true, 295, 460)
	self._btn_option = Button.New(MAIN_RES_PKG,
					MAINMENU_SCENE_PIC_PATH .. "btn_options.bmp",
					  2, true, 530, 530)
	self._btn_highscore = Button.New(MAIN_RES_PKG,
					 MAINMENU_SCENE_PIC_PATH .. "btn_highscore.bmp",
					 2, true, 580, 480)
	self._btn_credit = Button.New(MAIN_RES_PKG,
				  MAINMENU_SCENE_PIC_PATH .. "btn_credits.bmp",
				  2, true, 660, 430)
	self._btn_exit = Button.New(MAIN_RES_PKG,
					MAINMENU_SCENE_PIC_PATH .. "btn_exit.bmp",
					2, true, 660, 530)

	self._bgm = Music.Load(MAIN_RES_PKG, SOUND_PATH .. "main_menu.ogg", 
							Music.TYPE.STREAM)
	self._btn_hover = Music.Load(MAIN_RES_PKG, 
				SOUND_PATH .. "mouse_on_button.wav",
				Music.TYPE.SAMPLE)
	if (IsPlayMusic()) then
		self._bgm:Play(Music.TYPE.STREAM)
	end

	KeyListener.Regist ("UP", function () print("UP") end)

--	local lastbtn = -1
	local function BtnMouseMoveMsg (obj)
		return function (x, y) 
				   local ret = Button.IsCover(obj, x, y)
				   if (ret) then
--					   if (lastbtn ~= obj) then
					   if (IsPlaySound()) then
						   self._btn_hover:Play(Music.TYPE.SAMPLE)
--						   lastbtn = obj
					   end
--					   end
				   end
				   return ret
			   end
	end

	local function BtnMouseDown (obj, state)
		return function (x, y)
				   local ret = obj:IsCover(x, y) 
				   if ret then
					   local noerr, msg = pcall(SetGameState, state)
					   if (not noerr) then
						   print(msg)
					   end
				   end

				   return ret
			   end
	end

	MouseListener.Regist("MOUSEMOVE", BtnMouseMoveMsg(self._btn_start))
	MouseListener.Regist("MOUSEMOVE", BtnMouseMoveMsg(self._btn_exit))
	MouseListener.Regist("MOUSEMOVE", BtnMouseMoveMsg(self._btn_option))
	MouseListener.Regist("MOUSEMOVE", BtnMouseMoveMsg(self._btn_credit))
	MouseListener.Regist("MOUSEMOVE", BtnMouseMoveMsg(self._btn_highscore))

	MouseListener.Regist("LBUTTONDOWN", 
						 BtnMouseDown(self._btn_start, GAME_STATES.PLAYING))
	MouseListener.Regist("LBUTTONDOWN", 
						 BtnMouseDown(self._btn_option, GAME_STATES.OPTION))
	MouseListener.Regist("LBUTTONDOWN",
						 BtnMouseDown(self._btn_highscore, GAME_STATES.HIGHSCORE))
	MouseListener.Regist("LBUTTONDOWN",
						 BtnMouseDown(self._btn_credit, GAME_STATES.CREDIT))

	MouseListener.Regist("LBUTTONDOWN",
						 function (x, y) 
							 local ret = self._btn_exit:IsCover(x, y)
							 if (ret) then
								 Quit()
							 end
							 return ret
						 end)

	KeyListener.Regist("ESC", function () Quit() end)

	self._ani = Animation.New(MAIN_RES_PKG, 
							  "data/pic/mainmenu/mainmenu_cucuma.bmp",
							  4, false, 0, 400, 300)
	self._ani:SetDuration(60)
	self._ani:Start()

	self._change = true
	setmetatable(self, {__index = SceneMainMenu})
	
	return self
end

function SceneMainMenu:Destroy ()
	MouseListener.RemoveAll()
	KeyListener.RemoveAll()
	printf("SceneMainMenu:Destory")
	self._bgm:UnLoad(Music.TYPE.STREAM)
	self._btn_hover:UnLoad(Music.TYPE.SAMPLE)
	for v, t in pairs(self) do
		self[v] = nil
	end
end

function SceneMainMenu:Draw (canvas)
	self._btn_option:Draw(canvas)
	self._btn_credit:Draw(canvas)
	self._btn_highscore:Draw(canvas)
	self._btn_exit:Draw(canvas)
	self._btn_start:Draw(canvas) 
	self._ani:Draw(canvas)
	if (self._change) then
		canvas:Change()
		self._change = false
	else
		canvas:UnChange()
	end
	
	self._bg:Draw(canvas, 0, 0, BLIT_STYLE.BLIT_COPY)
end