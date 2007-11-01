
--[[
    $Id$
	
	Scene Playing
	CopyRight (c) GearX Team, 2007
	See LIENCE for more information
--]]

ScenePlaying = {}

function ScenePlaying.Init ()
	local self = {}
	self._bg = WBitmap.Load(MAIN_RES_PKG, 
			"data/pic/playing/background.bmp")
	self._bgm = Music.Load(MAIN_RES_PKG, 
			"data/sound/game_playing.ogg",
		   Music.TYPE.STREAM)
	self._bgm:Play(Music.TYPE.STREAM)
	self._change = true
	setmetatable(self, {__index = ScenePlaying,
						__gc = function (ob) return ob:Destroy() end})

	KeyListener.Regist ("ESC", function () pcall(SetGameState, GAME_STATES.MAINMENU) end)

	return self
end

function ScenePlaying:Destroy ()
	printf("ScenePlaying:Destroy")
	self._bgm:UnLoad(Music.TYPE.STREAM)
	self._bgm = nil
	self._bg = nil
end

function ScenePlaying:Draw (canvas)
	if (self._change) then
		canvas:Change()
		self._change = false
	else
		canvas:UnChange()
	end

	self._bg:Draw(canvas, 0, 0, BLIT_STYLE.BLIT_COPY)
end

