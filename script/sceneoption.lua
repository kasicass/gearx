
--[[
    $Id: $
	
	option 
	CopyRight (c) GearX Team, 2007
	See LISENCE for more information
	
	TAB SIZE: 4
--]]

dofile("../script/onoffbutton.lua")

SceneOption = {}

local OPTION_PIC_PATH = "data/pic/options/"

-------------------------------------------------------------------------------
function SceneOption.Init ()
	local self = {}
	self._bg = WBitmap.Load(MAIN_RES_PKG, 
								  OPTION_PIC_PATH .. "background.bmp")
--[[
	self._sound = OnOffButton.New(MAIN_RES_PKG, 
								  OPTION_PIC_PATH .. "check_button_on.bmp",
								  OPTION_PIC_PATH .. "check_button_off.bmp",
								  2, true,
								  380, 205,
								  480, 205, true)
	--]]								  
	self._music = OnOffButton.New(MAIN_RES_PKG, 
								  OPTION_PIC_PATH .. "check_button_on.bmp",
								  OPTION_PIC_PATH .. "check_button_off.bmp",
								  2, true,
								  380, 280,
								  480, 280, true)

	self._close = Button.New(MAIN_RES_PKG,
							 OPTION_PIC_PATH .. "btn_close.bmp",
							 2, true, 584, 137)
	self._change = true

	local function LBtnDown(obj)
		return function (x, y)
				   local ret = obj:IsCover(x, y)
				   if (ret) then
					   local noerr, msg = pcall(SetGameState, GAME_STATES.MAINMENU)
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

	local function OnOffMouseDown (obj)
		return function (x, y)
				   return obj:IsCover(x, y)
			   end
	end

--	MouseListener.Regist("LBUTTONDOWN", OnOffMouseDown(self._sound))
	MouseListener.Regist("LBUTTONDOWN", OnOffMouseDown(self._music))
	MouseListener.Regist("MOUSEMOVE", MouseMoveMsg(self._close))
	MouseListener.Regist("LBUTTONDOWN", LBtnDown(self._close))
	setmetatable(self, {__index = SceneOption})

	return self
end

function SceneOption:Draw (canvas)
	self._close:Draw(canvas)
--	self._sound:Draw(canvas)
	self._music:Draw(canvas)
--
	if (self._change) then
		canvas:Change()
		self._change = false
	else
		canvas:UnChang()
	end
--
--	canvas:Change()

	self._bg:Draw(canvas, 184, 125, BLIT_STYLE.BLIT_MASK)
end

function SceneOption:Destroy ()
	MouseListener.RemoveAll()
end

