
--[[
    $Id: $
	
	Keyboard Message Handler
	CopyRight (c) GearX Tearm, 2007
	See LICENSE for more infomation

	TAB SIZE: 4
--]]

KeyListener = {
	_listener = {}
}

KeyListener._keycode = {
   	UP 	    = 38,
	DOWN 	= 40,
	LEFT 	= 37,
	RIGHT 	= 39,
	MINUS	= 189,
	PLUS 	= 187,
	ENTER 	= 13,
	F1   	= 112,
	F2  	= 113,
	F3 	    = 114,
	F4 	    = 115,
	F5 	    = 116,
	F6   	= 117,
	F7  	= 118,
	F8 	    = 119,
	F9  	= 120,
	F10 	= 121,
	F11 	= 122,
	F12 	= 123,
	ESC 	= 27,
	INS 	= 45,
	BACKSPACE = 8,
	DEL 	= 46,
	PAGEUP	= 33,
	PAGEDOWN= 34,
	HOME 	= 36,
	END  	= 35,
	CTRL    = 17,
	LCTRL 	= 17,
	RCTRL	= 17,
	ALT	    = 18,
	LSHIFT	= 16,
	RSHIFT	= 16,
	SHIFT   = 16,
	TAB	    = 9,
	SPACE	= 32,
}
do
   local c, i = '0', 48
   repeat
      KeyListener._keycode[c] = i
      i = i + 1
      c = string.char(string.byte(c) + 1)
   until c == '9'

   local c, i = string.char(string.byte('A')-1), 64
   repeat
      i = i + 1
      c = string.char(string.byte(c) + 1)
      KeyListener._keycode[c] = i
   until c == 'Z'
end

-------------------------------------------------------------------------------
-- regist new keyboard message handler
-- \param keycode: key
-- \param func: callback function
function KeyListener.Regist (keycode, func)
	keycode = KeyListener._keycode[keycode]
	if (not keycode) then
		error("invalidate key ")
	end

	KeyListener._listener[keycode] = func
end

-------------------------------------------------------------------------------
-- remove key listener
-- \param keycode: which key to be removed
function KeyListener.Remove (keycode)
	KeyListener._listener[keycode] = nil
end

-------------------------------------------------------------------------------
-- remove all key binding
function KeyListener.RemoveAll ()
	for v, t in pairs(KeyListener._listener) do
		KeyListener._listener[v] = nil
	end

	KeyListener._listener = {}
end

-------------------------------------------------------------------------------
function KeyListener.Check (key)
	local func = KeyListener._listener[key]
	if (func) then
		local noerr, msg = pcall(func)
		if (not noerr) then
			error("error to call key callback: " .. key .. " " .. msg)
		end
	else
		printf("no key bind: " .. key)
	end
end

-------------------------------------------------------------------------------
-- test for is a specified key down?
-- \param key
function KeyListener.KeyDown (key)
	if (type(x) ~= "number") then
		key = key:upper()
		if x == "CTRL" then
			return KeyListener.KeyDown("LCTRL") or KeyListener.KeyDown("RCTRL")
		elseif x == "SHIFT" then
			return KeyListener.KeyDown("LSHIFT") or KeyListener.KeyDown("RSHIFT")
		end

		key = KeyListener._keycode[key]
	end
end

-------------------------------------------------------------------------------
