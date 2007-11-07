
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

	TAB SIZE: 4
--]]

-------------------------------------------------------------------------------
-- utilities
dofile("../script/utility.lua")
dofile("../script/settings.lua")
dofile("../script/button.lua")
dofile("../script/mouse.lua")
dofile("../script/keyboard.lua")
dofile("../script/music.lua")

-------------------------------------------------------------------------------
MAIN_RES_PKG = "data.wdf"
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
GameState = {
--	_state = GAME_STATES.INIT,
	_state = GAME_STATES.MAINMENU,
	_laststate = -1
}

function SetGameState (state)
	printf("state change")
	GameState._state = state
	GameState._scene:Destroy()
	GameState._scene = nil
end

-------------------------------------------------------------------------------
dofile("../script/scenelogo.lua")
dofile("../script/scenemainmenu.lua")
dofile("../script/sceneplaying.lua")
dofile("../script/sceneoption.lua")
dofile("../script/scenehighscore.lua")
dofile("../script/scenecredit.lua")

GameState._INITFUNC = {
	SceneLogo.Init,
	SceneMainMenu.Init,
	ScenePlaying.Init,
	SceneOption.Init,
	SceneHighScore.Init,
	SceneCredit.Init,
}

GameState._DRAWFUNC = {
	SceneLogo.Draw,
	SceneMainMenu.Draw,
	ScenePlaying.Draw,
	SceneOption.Draw,
	SceneHighScore.Draw,
	SceneCredit.Draw,
}

-------------------------------------------------------------------------------

local canvas					-- canvas
local surface					-- surface

-- init function
function GXInit (hwnd)
	canvas = WCanvas.Create(800, 600)
	surface = WSurface.Create(hwnd, canvas)
	canvas:Reset(30)
	canvas:Clear(0xffffff)
	Music.Init();
end

function GXMain ()
	local ret
	if (GameState._scene == nil) then
		ret, GameState._scene = pcall(GameState._INITFUNC[GameState._state])
		printf("change scene")
		printf("current state is %d", GameState._state)
	end
	
	ret = pcall(GameState._DRAWFUNC[GameState._state], GameState._scene, canvas)

	surface:Blit2Screen()
end

function GXMouseMove (x, y)
	MouseListener.Check("MOUSEMOVE", x, y)
end

function GXLButtonDown (x, y)
	MouseListener.Check("LBUTTONDOWN", x, y)
end

function GXKeyDown (key)
	KeyListener.Check(key)
end

function GXExit ()
	SaveSettings()
	GameState._scene:Destroy()
	GameState._scene = nil
	font = nil
end

-- wnd proc
function WndProc (msg, wparam, lparam)
	if (msg == WND_MSG.WM_KEYDOWN) then
		GXKeyDown(wparam)
	elseif (msg == WND_MSG.WM_MOUSEMOVE) then
		GXMouseMove(LOWORD(lparam), HIWORD(lparam))
	elseif (msg == WND_MSG.WM_LBUTTONDOWN) then
		GXLButtonDown(LOWORD(lparam), HIWORD(lparam))
	else
		return false
	end

	return true
end

