
--[[
	$Id: $
	
	GearX scene logo
--]]

SceneLogo = {}

function SceneLogo.Init ()
	local self = {}
	self._logo = {
		_bmp = WBitmap.Load(MAIN_RES_PKG,
						"data/pic/wf_logo.bmp"),
		_x = 250,
		_y = 200,
	}
	
	self._bg = WBitmap.CreateEmpty(self._logo._bmp:W(), self._logo._bmp:H(), 0xffffff)
	self._bgm = Music.Load(MAIN_RES_PKG, "data/sound/game_exit.ogg", Music.TYPE.STREAM)
	self._bgm:Play(Music.TYPE.STREAM)
	
	setmetatable(self, {__index = SceneLogo})
	
	return self
end

function SceneLogo:Destroy ()
	printf("logo gc")
	self._bgm:UnLoad()
	self._bgm = nil
	self._bg = nil
	self._logo._bmp = nil
	self = nil
end

local alpha = 255
function SceneLogo:Draw (canvas)
	if (alpha <= 0) then
		local ret, msg = pcall(SetGameState, GAME_STATES.MAINMENU)
		if (not ret) then
			print(msg)
		end
		
		return 
	end

	canvas:Change()
	self._logo._bmp:SetData(alpha)
	self._logo._bmp:Draw(canvas, self._logo._x, self._logo._y, BLIT_STYLE.BLIT_TRANS)
	self._bg:Draw(canvas, self._logo._x, self._logo._y, BLIT_STYLE.BLIT_COPY)
	alpha = alpha - 1
end



