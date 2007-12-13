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
-- block of scattered
-- 
block = {}

-------------------------------------------------------------------------------
-- new block info
-- 
-- @param x			x-axis index
-- @param y			y-axis index
-- @param imgidx	image index
-- 
-- @return block obj
-- 
function block.new (x, y, imgidx)
	local self = {
		_x = x or 0, 
		_y = y or 0,
		_imgidx = imgidx or 1,
	}

	setmetatable(self, {__index = Block})
	
	return self
end

function block:x ()
	return self._x
end

function block:y ()
	return self._y
end

function block:imgidx ()
	return self._imgidx
end

-------------------------------------------------------------------------------
-- scattered block list
-- 
scatteredblocks = {}

-------------------------------------------------------------------------------
-- init scattered list
-- 
function scatteredblocks.init ()
	local self = {}
	self._dy = 32
	setmetatable(self, {__index = scatteredblocks})

	return self
end

function scatteredblocks:reset ()
	local count = #self
	while (count > 0) do
		table.remove(self, count)
		count = count - 1
	end

	-- self = {}
	-- self._dy = 32
	-- setmetatable(self, {__index = scatteredblocks})
end

-------------------------------------------------------------------------------
-- Add block to list
-- 
-- @param block		block to be added
-- 
function scatteredblocks:add (block)
	table.insert(self, block)
end

-------------------------------------------------------------------------------
-- get scattered blocks count
-- 
-- @return count
-- 
function scatteredblocks:getcount ()
	return #self
end

-------------------------------------------------------------------------------
-- moving the scattered blocks
-- 
function scatteredblocks:move ()
	local count = #self
	if (count == 0) then return end

	for i=1, count do
		self[i]._y = self[i]._y + self._dy
	end
end

-------------------------------------------------------------------------------
-- draw scattered blocks
-- 
function scatteredblocks:draw (canvas, gears)
	local count = #self
	if (count == 0) then return end

	for i = 1, count do
		canvas:Change()
		gears:draw(canvas, self[i]._x + BLOCK_OFFSET_X, 
				   self[i]._y + BLOCK_OFFSET_Y,
				   self[i]._imgidx)
	end
end

-------------------------------------------------------------------------------

