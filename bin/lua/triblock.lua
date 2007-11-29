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
-- requires
require("timer")
require("blockcfg")

-- tri block for moving blocks
triblock = {}

-------------------------------------------------------------------------------
-- create moving block
-- 
function triblock.new ()
	local self = {}
	self._timer = timer.new(30)
	self._x = math.random(1, BLOCK_WIDTH) * BLOCK_SIZE
	self._y = 0
	self._dy = 4
	
	local i = math.random()
	for i = 1, 3 do
		self[i] = math.random(1, 6)
	end

	self._timer:start()
	setmetatable(self, {__index = triblock})

	return self
end

-------------------------------------------------------------------------------
-- reset moving block
-- 
function triblock:reset ()
	self._x = math.random(0, BLOCK_WIDTH-1) * BLOCK_SIZE
	self._y = 0
	
	for i = 1, 3 do
		self[i] = math.random(1, 3)
	end

	self._timer:reset()
end

-------------------------------------------------------------------------------
-- set first block y coordinate
-- 
-- @param y y-axis coordinate
-- 
function triblock:sety (y)
	self._y = y
end

-------------------------------------------------------------------------------
-- move triblock
-- 
function triblock:movedown ()
	if self._timer:isactive() then 
		self._y = self._y + self._dy
	end
end

function triblock:moveleft ()
	if (self._x >= BLOCK_SIZE) then
		self._x = self._x - BLOCK_SIZE
	end
end

function triblock:moveright ()
	if (self._x < (BLOCK_WIDTH-1) * BLOCK_SIZE) then
		self._x = self._x + BLOCK_SIZE
	end
end

-------------------------------------------------------------------------------
-- scroll image
-- 
function triblock:scrollup ()
	self[1], self[2], self[3] = self[2], self[3], self[1]
end

function triblock:scrolldown ()
	self[1], self[2], self[3] = self[3], self[1], self[2]
end

-------------------------------------------------------------------------------
-- get image index
-- 
function triblock:getidx (idx)
	assert(idx >= 1 and idx <= 3, "out of boundary")
	return self[idx]
end

function triblock:xidx ()
	return math.floor(self._x / BLOCK_SIZE) + 1
end

function triblock:yidx ()
	return math.floor(self._y / BLOCK_SIZE) + 1
end

-------------------------------------------------------------------------------

function triblock:draw (canvas, gears)
	-- call gears draw
	canvas:Change()
	gears:draw(canvas, self._x + BLOCK_OFFSET_X,
			   self._y + BLOCK_OFFSET_Y, self:getidx(1))
	gears:draw(canvas, self._x + BLOCK_OFFSET_X,
			   self._y-BLOCK_SIZE + BLOCK_OFFSET_Y, 
			   self:getidx(2))
	gears:draw(canvas, self._x + BLOCK_OFFSET_X, 
			   self._y-BLOCK_SIZE*2 + BLOCK_OFFSET_Y, 
			   self:getidx(3))
end


-------------------------------------------------------------------------------
function triblock:setimgidx (idx, imgidx)
	self[idx] = imgidx
end

