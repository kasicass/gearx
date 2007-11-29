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
require("blockcfg")

-------------------------------------------------------------------------------
spark = {}

-------------------------------------------------------------------------------
-- create spark images
-- 
-- @param x x coordinate
-- @param y y coordinate
function spark.new (x, y, frame)
	local self = {
		_x = x or 1,
		_y = y or 1,
		_frame = frame or 1,
	}

	self._dx = math.random(-10, 10)
	self._dy = math.random(-40, -10)

	if (self._dy > -20) then
		self._dyacc = math.random(2, 3)
	elseif (self._dy > -30) then
		self._dyacc = math.random(3, 4)
	else
		self._dyacc = math.random(4, 5)
	end

	setmetatable(self, {__index = spark})

	return self
end

-------------------------------------------------------------------------------
-- move the sparks
-- 
function spark:move ()
	self._x = self._x + self._dx

	-- x axis
	if (self._x < 0) then
		self._x = 0
		self._dx = -self._dx
	elseif (self._x > BLOCK_TOTAL_WIDTH - BLOCK_SIZE - 1) then
		self._x = BLOCK_TOTAL_WIDTH - BLOCK_SIZE - 1
		self._dx = -self._dx
	end

	self._y = self._y + self._dy

	-- y axis
	self._dy = self._dy + self._dyacc
end

-------------------------------------------------------------------------------
