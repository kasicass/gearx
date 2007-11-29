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

keyboard = {
	_listener = {}
}

-------------------------------------------------------------------------------

keyboard._keycode = {
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
      keyboard._keycode[c] = i
      i = i + 1
      c = string.char(string.byte(c) + 1)
   until c == '9'

   local c, i = string.char(string.byte('A')-1), 64
   repeat
      i = i + 1
      c = string.char(string.byte(c) + 1)
      keyboard._keycode[c] = i
   until c == 'Z'
end

-------------------------------------------------------------------------------
-- regist new keyboard message handler
-- \param keycode: key
-- \param func: callback function
function keyboard.regist (keycode, func)
	keycode = keyboard._keycode[keycode]
	if (not keycode) then
		error("invalidate key ")
	end

	keyboard._listener[keycode] = func
end

-------------------------------------------------------------------------------
-- remove key listener
-- \param keycode: which key to be removed
function keyboard.remove (keycode)
	keyboard._listener[keycode] = nil
end

-------------------------------------------------------------------------------
-- remove all key binding
function keyboard.removeall ()
	keyboard._listener = {}
end

-------------------------------------------------------------------------------
function keyboard.check (key)
	if (keyboard._all) then
		if (keyboard._allfunc) then
			_, ret = pcall(keyboard._allfunc, key)
			if (ret) then
				return
			end
		end
	end

	local func = keyboard._listener[key]
	if (func) then
		local noerr, msg = pcall(func)
		if (not noerr) then
			error("error to call key callback: " .. key .. " " .. msg)
		end
	else
		print("no key bind: " .. key)
	end
end

-------------------------------------------------------------------------------
function keyboard.registall (func)
	keyboard._all = true
	keyboard._allfunc = func
end

-------------------------------------------------------------------------------
function keyboard.removealllistener ()
	keyboard._all = false
	keyboard._allfunc = nil
end

-------------------------------------------------------------------------------
-- test for is a specified key down?
-- 
-- @param key
-- 
function keyboard.keydown (key)
	if (type(x) ~= "number") then
		key = key:upper()
		if x == "CTRL" then
			return keyboard.KeyDown("LCTRL") or keyboard.KeyDown("RCTRL")
		elseif x == "SHIFT" then
			return keyboard.KeyDown("LSHIFT") or keyboard.KeyDown("RSHIFT")
		end

		key = keyboard._keycode[key]
	end
end

-------------------------------------------------------------------------------
