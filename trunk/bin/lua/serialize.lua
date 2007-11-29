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

	$Id: $
	ChenZaichun@gmail.com
--]]

-------------------------------------------------------------------------------
module("serialize", package.seeall)

-- serialize objects
-- 
-- @return the result string
-- 
function serialize (o)
	local str = ""
	if type(o) == "number" then
		str = str .. o
	elseif type(o) == "string" then
		str = str .. "\"" .. o .. "\""
	elseif type(o) == "boolean" then
		str = str .. tostring(o)
	elseif type(o) == "table" then
		str = str .. "{\n"
		for k, v in pairs(o) do
			str = str .. "\t" .. k .. " = "
			str = str .. serialize(v)
			str = str .. ",\n"
		end
		str = str .. "}\n"
	else
		error("can not serialize " .. type(o))
	end
	
	return str
end

-------------------------------------------------------------------------------
-- 
function serializenoidx (o)
	local str = ""
	if (type(o) == "number") then
		str = str .. o
	elseif (type(o) == "string") then
		str = str .. "\"" .. o .. "\""
	elseif (type(o) == "boolean") then
		str = str .. tostring(o)
	elseif (type(o) == "table") then
		str = str .. "{\n"
		for i, v in ipairs(o) do
			str = str .. "\t" .. serializenoidx(v)
			str = str .. ",\n"
		end

		str = str .. "}\n"
	else
		error("can not serialize " .. type(o))
	end

	return str
end
    

