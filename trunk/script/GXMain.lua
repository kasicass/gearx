--[[
	$Id$
	Desc:	GearX Main Script
--]]

dofile("../script/utility.lua")
dofile("../script/button.lua")
dofile("../script/mouse.lua")
dofile("../script/keyboard.lua")
dofile("../script/music.lua")

MAIN_RES_PKG = "data.wdf"
SOUND_PATH = "data/sound/"

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
	HIGHTSCORE	= 5,
	CREDIT      = 6,
}

WND_MSG = {
	WM_KEYDOWN     = 0X0100,
	WM_MOUSEMOVE   = 0X0200,
	WM_LBUTTONDOWN = 0X0201,
}

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

dofile("../script/scenelogo.lua")
dofile("../script/scenemainmenu.lua")
dofile("../script/sceneplaying.lua")
dofile("../script/sceneoption.lua")

GameState._INITFUNC = {
	SceneLogo.Init,
	SceneMainMenu.Init,
	ScenePlaying.Init,
	SceneOption.Init,
}

GameState._DRAWFUNC = {
	SceneLogo.Draw,
	SceneMainMenu.Draw,
	ScenePlaying.Draw,
	SceneOption.Draw,
}

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

-- wnd proc
function WndProc (msg, wparam, lparam)
	if (msg == WND_MSG.WM_KEYDWON) then
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

