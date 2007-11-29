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

-------------------------------------------------------------------------------
-- Mouse Listener
-- 
mouse = {
	_listener = {}
}

-------------------------------------------------------------------------------
-- regist mouse message handlder
-- 
-- @param msg message to be handed
-- @param func callback function, the callback function must have the x, y 
--              parameter handler
-- 
function mouse.regist (msg, func)
	if (not mouse._listener[msg]) then
		mouse._listener[msg] = {}
	end

	table.insert(mouse._listener[msg], func)
end

-------------------------------------------------------------------------------
-- check for mouse message
-- 
-- \param msg: which message to be check
-- \param x: x coordinate
-- \param y: y coordinate
-- 
function mouse.check (msg, x, y)
	if (not mouse._listener[msg]) then return end
	for i, t in ipairs(mouse._listener[msg]) do
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
-- 
-- \param msg: which msg handler to be removed
-- \param func: which hanlder to be removed
-- 
function mouse.remove (msg, func)
	for i, t in ipairs(mouse._listener[msg]) do
		if (t == func) then
			table.remove(mouse._listener[msg], i)
		end
	end
end


-------------------------------------------------------------------------------
-- remove all handler
function mouse.removeall ()
-- 	for v, t in pairs(mouse._listener) do
-- 		mouse._listener[v] = nil
-- 	end

	mouse._listener = {}
end
