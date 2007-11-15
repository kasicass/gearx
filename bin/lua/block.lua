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
-- block of scattered
Block = {}

-------------------------------------------------------------------------------
-- new block info
-- 
-- @param x			x-axis index
-- @param y			y-axis index
-- @param imgidx	image index
-- 
-- @return block obj
function Block.New (x, y, imgidx)
	local self = {
		_x = x or 0, 
		_y = y or 0,
		_imgidx = imgidx or 1,
	}

	setmetatable(self, {__index = Block})
	
	return self
end

-------------------------------------------------------------------------------
-- scattered block list
ScatteredBlocks = {}

-------------------------------------------------------------------------------
-- init scattered list
-- 
function ScatteredBlocks.Init ()
	local self = {}
	self._dy = 32
	setmetatable(self, {__index = ScatteredBlocks})

	return self
end

-------------------------------------------------------------------------------
-- Add block to list
-- 
-- @param block		block to be added
-- 
function ScatteredBlocks:Add (block)
	table.insert(self, block)
--	print("count", #self)
end

-------------------------------------------------------------------------------
-- get scattered blocks count
-- 
-- @return count
-- 
function ScatteredBlocks:GetCount ()
	return #self
end

-------------------------------------------------------------------------------
-- moving the scattered blocks
-- 
function ScatteredBlocks:Move ()
	local count = #self
	if (count == 0) then return end

	for i=1, count do
		self[i]._y = self[i]._y + self._dy
	end
end

-------------------------------------------------------------------------------
-- draw scattered blocks
-- 
function ScatteredBlocks:Draw (canvas, gears)
	local count = #self
	if (count == 0) then return end

	for i = 1, count do
		canvas:Change()
--		print(self[i]._imgidx)
		gears:Draw(canvas, self[i]._x + BLOCK_OFFSET_X, 
				   self[i]._y + BLOCK_OFFSET_Y,
				   self[i]._imgidx)
--		print("draw OK")
	end
end

-------------------------------------------------------------------------------
-- for holding blocks
BlockTable = {}

-------------------------------------------------------------------------------
-- init block container
function BlockTable.Init ()
	local self = {}
	self._trunktbl = {}
	for i = 1, BLOCK_WIDTH do
		self[i] = {}
		self._trunktbl[i] = {}

		for j = 1, BLOCK_HEIGHT do
			self[i][j] = 0
			self._trunktbl[i][j] = false
		end
	end

	setmetatable(self, {__index = BlockTable})

	return self
end

-------------------------------------------------------------------------------
-- add block to container
-- 
-- @param x		x-axis index
-- @param y		y-axis index
-- @param idx	image index
-- 
function BlockTable:Add (x, y, idx)
	self[x][y] = idx
end

-------------------------------------------------------------------------------
-- reset block
-- 
function BlockTable:Reset ()
	for i = 1, BLOCK_WIDTH do
		for j = 1, BLOCK_HEIGHT do
			self[i][j] = 0
		end
	end
end

-------------------------------------------------------------------------------
-- reset trunk table
-- 
function BlockTable:ResetTrunkTbl()
	for i = 1, BLOCK_WIDTH do
		for j = 1, BLOCK_HEIGHT do
			self._trunktbl[i][j] = false
		end
	end
end

-------------------------------------------------------------------------------
-- ADD triblock to container
-- 
-- @param triblock		triblock to be added
-- 
function BlockTable:AddTri (triblock, list, sparksys)
	local x = triblock:XIdx()
	local y = triblock:YIdx()

	self[x][y] = triblock:GetIdx(1)
	self[x][y-1] = triblock:GetIdx(2)
	self[x][y-2] = triblock:GetIdx(3) 

	self:ResetTrunkTbl()

	self:FillTrunkTbl(x, y)
	self:FillTrunkTbl(x, y-1)
	self:FillTrunkTbl(x, y-2)

-- 	local s = "trunk table: " .. serialize(self._trunktbl)
-- 	print(s)

	local count = self:TrunkBlocks(sparksys)
	if (count > 0) then
		self:FillScatteredList(list)
	end

	return count
end

-------------------------------------------------------------------------------
-- get image index
-- 
-- @param x		x-axis index
-- @param y		y-axis index
-- 
-- @return the image index
-- 
function BlockTable:GetImgIdx (x, y)
	if (x < 1 or x > BLOCK_WIDTH) then
		return nil
	end

 	return self[x][y]
end

-------------------------------------------------------------------------------
-- remove block from container
-- 
-- @param x		x-axis index
-- @param y		y-axis index
-- 
function BlockTable:Remove(x, y)
	self[x][y] = 0
end

-------------------------------------------------------------------------------
-- draw blocks
function BlockTable:Draw (canvas, gears)
	for i, t in ipairs(self) do
		for j, v in ipairs(t) do
			if (v > 0) then
				gears:Draw(canvas, (i-1)*BLOCK_SIZE + BLOCK_OFFSET_X,
						   (j-1)*BLOCK_SIZE + BLOCK_OFFSET_Y, 
						   v)
			end
		end
	end
end

-------------------------------------------------------------------------------
-- fill trunk table
-- 
-- @param x	x-axis index
-- @param y y-axis index
-- 
function BlockTable:FillTrunkTbl (x, y)
	local mode = 0
	local idx_x, idx_y = x-1, y
	local imgidx = self[x][y]
	local count = 1

	----------------------------------------------------------------------
	-- 横向判断
	while (idx_x > 0) do
		if (self[idx_x][idx_y] ~= imgidx) then
			break
		end

		count = count + 1
		idx_x = idx_x - 1
	end

	idx_x = x + 1
	while (idx_x <= BLOCK_WIDTH) do
		if (self[idx_x][idx_y] ~= imgidx) then
			break
		end

		count = count + 1
		idx_x = idx_x + 1
	end

	if (count >= 3) then mode = AOr(mode, 1) end
	----------------------------------------------------------------------

	----------------------------------------------------------------------
	-- 左斜
	idx_x, idx_y = x - 1, y - 1
	count = 1
	while (idx_x > 0 and idx_y > 0) do
		if (self[idx_x][idx_y] ~= imgidx) then
			break
		end

		count = count + 1
		idx_x = idx_x - 1
		idx_y = idx_y - 1
	end

	idx_x, idx_y = x + 1, y + 1
	while (idx_x <= BLOCK_WIDTH and idx_y <= BLOCK_HEIGHT) do
		if (self[idx_x][idx_y] ~= imgidx) then
			break
		end

		count = count + 1
		idx_x = idx_x + 1
		idx_y = idx_y + 1
	end
	
	if (count >= 3) then mode = AOr(mode, 2) end
	----------------------------------------------------------------------

	----------------------------------------------------------------------
	-- 竖直
	idx_x, idx_y, count = x, y-1, 1
	while (idx_y > 0) do
		if (self[idx_x][idx_y] ~= imgidx) then
			break
		end

		count = count + 1
		idx_y = idx_y - 1
	end

	idx_y = y + 1
	while (idx_y <= BLOCK_HEIGHT) do
		if (self[idx_x][idx_y] ~= imgidx) then
			break
		end

		count = count + 1
		idx_y = idx_y + 1
	end

	if (count >= 3) then mode = AOr(mode, 4) end
	----------------------------------------------------------------------

	----------------------------------------------------------------------
	-- 右斜
	idx_x, idx_y, count = x+1, y-1, 1
	while (idx_x <= BLOCK_WIDTH and idx_y > 0) do
		if (self[idx_x][idx_y] ~= imgidx) then
			break
		end

		count = count + 1
		idx_x = idx_x + 1
		idx_y = idx_y - 1
	end

	idx_x, idx_y = x-1, y+1
	while (idx_x > 0 and idx_y <= BLOCK_HEIGHT) do
		if (self[idx_x][idx_y] ~= imgidx) then
			break
		end

		count = count + 1
		idx_x = idx_x - 1
		idx_y = idx_y + 1
	end

	if (count >= 3) then mode = AOr(mode, 8) end
	----------------------------------------------------------------------

	----------------------------------------------------------------------
	-- 对四个方向处理，填写trunk table
	-- 横向
	if (AAnd(mode, 1) > 0) then
		idx_x, idx_y = x, y
		self._trunktbl[idx_x][idx_y] = true

		idx_x = idx_x - 1
		while (idx_x >0 ) do
			if (self[idx_x][idx_y] ~= imgidx) then
				break
			end

			self._trunktbl[idx_x][idx_y] = true
			idx_x = idx_x - 1
		end

		idx_x = x + 1
		while (idx_x <= BLOCK_WIDTH) do
			if (self[idx_x][idx_y] ~= imgidx) then
				break
			end

			self._trunktbl[idx_x][idx_y] = true
			idx_x = idx_x + 1
		end
	end

	-- 左斜
	if (AAnd(mode, 2) > 0) then
		idx_x, idx_y = x, y
		self._trunktbl[idx_x][idx_y] = true

		idx_x, idx_y = idx_x - 1, idx_y - 1
		while (idx_x > 0 and idx_y > 0) do
			if (self[idx_x][idx_y] ~= imgidx) then
				break
			end

			self._trunktbl[idx_x][idx_y] = true
			idx_x, idx_y = idx_x - 1, idx_y - 1
		end

		idx_x, idx_y = x+1, y+1
		while (idx_x <= BLOCK_WIDTH and idx_y <= BLOCK_HEIGHT) do
			if (self[idx_x][idx_y] ~= imgidx) then
				break
			end

			self._trunktbl[idx_x][idx_y] = true
			idx_x, idx_y = idx_x + 1, idx_y + 1
		end
	end

	-- 竖直
	if (AAnd(mode, 4) > 0) then
		idx_x, idx_y = x, y
		self._trunktbl[idx_x][idx_y] = true

		idx_y = idx_y - 1
		while (idx_y > 0) do
--			print(idx_y, self[idx_x][idx_y])
			if (self[idx_x][idx_y] ~= imgidx) then
				break
			end

			self._trunktbl[idx_x][idx_y] = true
			idx_y = idx_y - 1
		end

		idx_y = y + 1
		while (idx_y <= BLOCK_HEIGHT) do
			if (self[idx_x][idx_y] ~= imgidx) then
				break
			end

			self._trunktbl[idx_x][idx_y] = true
			idx_y = idx_y + 1
		end
	end

	-- 右斜
	if (AAnd(mode, 8) > 0) then
		idx_x, idx_y = x, y
		self._trunktbl[idx_x][idx_y] = true
		
		idx_x, idx_y = idx_x + 1, idx_y - 1
		while (idx_x <= BLOCK_WIDTH and idx_y > 0) do
			if (self[idx_x][idx_y] ~= imgidx) then
				break
			end

			self._trunktbl[idx_x][idx_y] = true
			idx_x, idx_y = idx_x + 1, idx_y - 1
		end

		idx_x, idx_y = x - 1, y + 1
		while (idx_x > 0 and idx_y <= BLOCK_HEIGHT) do
			if (self[idx_x][idx_y] ~= imgidx) then
				break
			end

			self._trunktbl[idx_x][idx_y] = true
			idx_x, idx_y = idx_x - 1, idx_y + 1
		end
	end
	----------------------------------------------------------------------
end

-------------------------------------------------------------------------------
-- add scattered block to scattered block list
-- 
-- @param list		scattered block list
-- 
function BlockTable:FillScatteredList (list)
	local restbegin = false

	for cx = 1, BLOCK_WIDTH do
		for cy = BLOCK_HEIGHT, 1, -1 do
			if (restbegin) then
--				print("restbegin")
				if (self[cx][cy] ~= 0) then
					local block = Block.New((cx-1)*BLOCK_SIZE,
											(cy-1)*BLOCK_SIZE,
											self[cx][cy])
					list:Add(block)
					self[cx][cy] = 0
				end
			else
				if (self[cx][cy] == 0) then
					restbegin = true
				end
			end
		end
		
		restbegin = false
	end
end

-------------------------------------------------------------------------------
-- trunk blocks
-- 
function BlockTable:TrunkBlocks (sparksys)
	local count = 0

	for cy = 1, BLOCK_HEIGHT do
		for cx = 1, BLOCK_WIDTH do
			if (self._trunktbl[cx][cy]) then
				self[cx][cy] = 0

				count = count + 1
			end
		end
	end

	-- file spark
	for cy = 1, BLOCK_HEIGHT do
		for cx = 1, BLOCK_WIDTH do
			if (self._trunktbl[cx][cy]) then
				for i=1, 3 do
					sparksys:CreateSpark((cx-1)*BLOCK_SIZE, 
										 (cy-1)*BLOCK_SIZE)
				end
			end
		end
	end

	return count				
end

-------------------------------------------------------------------------------
-- check trunk
-- 
-- function BlockTable:CheckTrunk ()
-- 	if (self._trunktbl:GetCount() > 0) then
		
-- 	else
-- 	end
-- end
