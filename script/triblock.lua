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

	$Id: $
	ChenZaichun@gmail.com
--]]

-------------------------------------------------------------------------------
-- tri block for moving blocks
TriBlock = {}

-------------------------------------------------------------------------------
-- create moving block
-- 
function TriBlock.New ()
	local self = {}
	self._timer = Timer.New(30)
	self._x = math.random(1, BLOCK_WIDTH) * BLOCK_SIZE
	self._y = 0
	self._dy = 4
	
	local i = math.random()
	for i = 1, 3 do
		self[i] = math.random(1, 6)
	end

	self._timer:Start()
	setmetatable(self, {__index = TriBlock})

	return self
end

-------------------------------------------------------------------------------
-- reset moving block
-- 
function TriBlock:Reset ()
	self._x = math.random(0, BLOCK_WIDTH-1) * BLOCK_SIZE
	self._y = 0
	
	for i = 1, 3 do
		self[i] = math.random(1, 3)
	end

	self._timer:Reset()
end

-------------------------------------------------------------------------------
-- set first block y coordinate
-- 
-- @param y y-axis coordinate
-- 
function TriBlock:SetY (y)
	self._y = y
end

-------------------------------------------------------------------------------
-- move triblock
-- 
function TriBlock:MoveDown ()
	if self._timer:IsActive() then 
		self._y = self._y + self._dy
	end
end

function TriBlock:MoveLeft ()
	if (self._x >= BLOCK_SIZE) then
		self._x = self._x - BLOCK_SIZE
	end
end

function TriBlock:MoveRight ()
	if (self._x < (BLOCK_WIDTH-1) * BLOCK_SIZE) then
		self._x = self._x + BLOCK_SIZE
	end
end

-------------------------------------------------------------------------------
-- scroll image
-- 
function TriBlock:ScrollUP ()
	self[1], self[2], self[3] = self[2], self[3], self[1]
end

function TriBlock:ScrollDown ()
	self[1], self[2], self[3] = self[3], self[1], self[2]
end

-------------------------------------------------------------------------------
-- get image index
-- 
function TriBlock:GetIdx (idx)
	assert(idx >= 1 and idx <= 3, "out of boundary")
	return self[idx]
end

function TriBlock:XIdx ()
	return math.floor(self._x / BLOCK_SIZE) + 1
end

function TriBlock:YIdx ()
	return math.floor(self._y / BLOCK_SIZE) + 1
end

-------------------------------------------------------------------------------

function TriBlock:Draw (canvas, gears)
-- 	bmp:Draw(canvas, self._x + BLOCK_OFFSET_X,
-- 			 self._y + BLOCK_OFFSET_Y, 
-- 			 BLIT_STYLE.BLIT_MASK)
-- 	bmp:Draw(canvas, self._x + BLOCK_OFFSET_X,
-- 			 self._y + BLOCK_OFFSET_Y - BLOCK_SIZE,
-- 			 BLIT_STYLE.BLIT_MASK)
-- 	bmp:Draw(canvas, self._x + BLOCK_OFFSET_X,
-- 			 self._y + BLOCK_OFFSET_Y - BLOCK_SIZE * 2,
-- 			 BLIT_STYLE.BLIT_MASK)

	gears:Draw(canvas, self._x + BLOCK_OFFSET_X,
			   self._y + BLOCK_OFFSET_Y, self:GetIdx(1))
	gears:Draw(canvas, self._x + BLOCK_OFFSET_X,
			   self._y-BLOCK_SIZE + BLOCK_OFFSET_Y, 
			   self:GetIdx(2))
	gears:Draw(canvas, self._x + BLOCK_OFFSET_X, 
			   self._y-BLOCK_SIZE*2 + BLOCK_OFFSET_Y, 
			   self:GetIdx(3))
-- 	gears[self:GetIdx(1)]:Draw(canvas, self._x, self._y, BLIT_STYLE.BLIT_MASK)
-- 	gears[self:GetIdx(2)]:Draw(canvas, self._x,
-- 							   self._y-BLOCK_SIZE, BLIT_STYLE.BLIT_MASK)
-- 	gears[self:GetIdx(3)]:Draw(canvas, self._x,
-- 							   self._y-BLOCK_SIZE, BLIT_STYLE.BLIT_MASK)
end


