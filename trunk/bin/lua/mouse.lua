-- emacs: -*- mode: lua; coding: gb2312 -*- TAB SIZE: 4 -*- 

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

-------------------------------------------------------------------------------
-- Mouse Listener
MouseListener = {
	_listener = {}
}

-------------------------------------------------------------------------------
-- regist mouse message handlder
-- \param msg: message to be handed
-- \param func: callback function, the callback function must have the x, y 
--              parameter handler
function MouseListener.Regist (msg, func)
	if (not MouseListener._listener[msg]) then
		MouseListener._listener[msg] = {}
	end

	table.insert(MouseListener._listener[msg], func)
end

-------------------------------------------------------------------------------
-- check for mouse message
-- \param msg: which message to be check
-- \param x: x coordinate
-- \param y: y coordinate
function MouseListener.Check (msg, x, y)
	if (not MouseListener._listener[msg]) then return end
	for i, t in ipairs(MouseListener._listener[msg]) do
		local noerr, msg = pcall(t, x, y)
		if (not noerr) then
			return error("call for " .. msg .. "check failed: " .. msg)
		end

		if (msg) then return msg end
	end

	return false
end

-------------------------------------------------------------------------------
-- remove handler
-- \param msg: which msg handler to be removed
-- \param func: which hanlder to be removed
function MouseListener.Remove (msg, func)
	for i, t in ipairs(MouseListener._listener[msg]) do
		if (t == func) then
			table.remove(MouseListener._listener[msg], i)
		end
	end
end


-------------------------------------------------------------------------------
-- remove all handler
function MouseListener.RemoveAll ()
-- 	for v, t in pairs(MouseListener._listener) do
-- 		MouseListener._listener[v] = nil
-- 	end

	MouseListener._listener = {}
end
