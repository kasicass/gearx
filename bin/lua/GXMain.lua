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
-- utilities
package.cpath = "../" .. package.cpath
require("gxbase")
require("score")
require("settings")

-------------------------------------------------------------------------------
MAIN_PATH = "" -- "../data/"
MAIN_RES_PKG = MAIN_PATH .. "data.wdf"
SOUND_PATH = "data/sound/"

-------------------------------------------------------------------------------
BLIT_STYLE = {
	BLIT_NORMAL = 0,
	BLIT_COPY	= 0,
	BLIT_ADDITIVE = 1,
	BLIT_SUBTRACT = 2,
	BLIT_TRANS = 3,
	BLIT_MASK = 4,
	BLIT_BACK = 5,
}

GAME_STATES = {
	INIT		= 1,
	MAINMENU	= 2,
	PLAYING		= 3,
	OPTION		= 4,
	HIGHSCORE	= 5,
	CREDIT      = 6,
}

WND_MSG = {
	WM_KEYDOWN     = 0X0100,
	WM_MOUSEMOVE   = 0X0200,
	WM_LBUTTONDOWN = 0X0201,
}

-------------------------------------------------------------------------------
font = WFont.Create("Verdana", 24)

-------------------------------------------------------------------------------
gamestate = {
--	_state = GAME_STATES.INIT,
	_state = GAME_STATES.MAINMENU,
--	_state = GAME_STATES.HIGHSCORE,
	_laststate = -1
}

function setgamestate (state)
	print("state change")
	gamestate._state = state
	gamestate._scene:destroy()
	gamestate._scene = nil
end

-------------------------------------------------------------------------------
require("scenelogo")
require("scenemainmenu")
require("sceneplaying")
require("sceneoption")
require("scenehighscore")
require("scenecredit")
-- dofile("lua/scenelogo.lua")
-- dofile("lua/scenemainmenu.lua")
-- dofile("lua/sceneplaying.lua")
-- dofile("lua/sceneoption.lua")
-- dofile("lua/scenehighscore.lua")
-- dofile("lua/scenecredit.lua")

gamestate._INITFUNC = {
	scenelogo.init,
	scenemainmenu.init,
	sceneplaying.init,
	sceneoption.init,
	scenehighscore.init,
	scenecredit.init,
}

gamestate._DRAWFUNC = {
	scenelogo.draw,
	scenemainmenu.draw,
	sceneplaying.draw,
	sceneoption.draw,
	scenehighscore.draw,
	scenecredit.draw,
}

-------------------------------------------------------------------------------

local g_canvas					-- canvas
local g_surface					-- surface

-------------------------------------------------------------------------------
-- init function
function GXInit (hwnd)
	g_canvas = WCanvas.Create(800, 600)
	g_surface = WSurface.Create(hwnd, g_canvas)
	g_canvas:Reset(30)
	g_canvas:Clear(0xffffff)
	music.Init();
end

-------------------------------------------------------------------------------
function GXMain ()
	local ret
	if (gamestate._scene == nil) then
		ret, gamestate._scene = pcall(gamestate._INITFUNC[gamestate._state])
 		print("change scene")
 		print("current state is: ", gamestate._state)
	end
	
	ret = pcall(gamestate._DRAWFUNC[gamestate._state], gamestate._scene, g_canvas)

	g_surface:Blit2Screen()
end

-------------------------------------------------------------------------------
function GXMouseMove (x, y)
	mouse.check("MOUSEMOVE", x, y)
end

function GXLButtonDown (x, y)
	mouse.check("LBUTTONDOWN", x, y)
end

-------------------------------------------------------------------------------
function GXKeyDown (key)
	keyboard.check(key)
end

-------------------------------------------------------------------------------
function GXExit ()
	score.savehighscore()
	settings.savesettings()
	gamestate._scene:destroy()
	music.Shutdown()
	gamestate._scene = nil
	font = nil
	g_surface = nil
	g_canvas = nil
end

-------------------------------------------------------------------------------
-- wnd proc
function WndProc (msg, wparam, lparam)
	if (msg == WND_MSG.WM_KEYDOWN) then
		GXKeyDown(wparam)
	elseif (msg == WND_MSG.WM_MOUSEMOVE) then
		GXMouseMove(bit.loword(lparam), bit.hiword(lparam))
	elseif (msg == WND_MSG.WM_LBUTTONDOWN) then
		GXLButtonDown(bit.loword(lparam), bit.hiword(lparam))
	else
		return false
	end

	return true
end

-------------------------------------------------------------------------------

