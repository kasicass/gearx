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
require("gxbase")

blocktable = {}

-------------------------------------------------------------------------------
-- init block container
function blocktable.init ()
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

	setmetatable(self, {__index = blocktable})

	return self
end

-------------------------------------------------------------------------------
-- add block to container
-- 
-- @param x		x-axis index
-- @param y		y-axis index
-- @param idx	image index
-- 
function blocktable:add (x, y, idx)
	self[x][y] = idx
end

-------------------------------------------------------------------------------
-- reset block
-- 
function blocktable:reset ()
	for i = 1, BLOCK_WIDTH do
		for j = 1, BLOCK_HEIGHT do
			self[i][j] = 0
		end
	end
end

-------------------------------------------------------------------------------
-- reset trunk table
-- 
function blocktable:resettrunktbl()
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
function blocktable:addtri (_triblock, _list, _sparksys)
--	print(_triblock._x, _triblock._y)
	local x = _triblock:xidx()
	local y = _triblock:yidx()

--	print("x, y", x, y)

	self[x][y] = _triblock:getidx(1)
	self[x][y-1] = _triblock:getidx(2)
	self[x][y-2] = _triblock:getidx(3) 

	self:resettrunktbl()

	self:filltrunktbl(x, y)
	self:filltrunktbl(x, y-1)
	self:filltrunktbl(x, y-2)

-- 	local s = "trunk table: " .. serialize(self._trunktbl)
-- 	print(s)

	local count = self:trunkblocks(_sparksys)
	if (count > 0) then
		self:fillscatteredlist(_list)
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
function blocktable:getimgidx (x, y)
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
function blocktable:remove(x, y)
	self[x][y] = 0
end

-------------------------------------------------------------------------------
-- draw blocks
function blocktable:draw (canvas, gears)
	for i, t in ipairs(self) do
		for j, v in ipairs(t) do
			if (v > 0) then
				gears:draw(canvas, (i-1)*BLOCK_SIZE + BLOCK_OFFSET_X,
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
function blocktable:filltrunktbl (x, y)
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

	if (count >= 3) then mode = bit.bor(mode, 1) end
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
	
	if (count >= 3) then mode = bit.bor(mode, 2) end
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

	if (count >= 3) then mode = bit.bor(mode, 4) end
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

	if (count >= 3) then mode = bit.bor(mode, 8) end
	----------------------------------------------------------------------

	----------------------------------------------------------------------
	-- 对四个方向处理，填写trunk table
	-- 横向
	if (bit.band(mode, 1) > 0) then
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
	if (bit.band(mode, 2) > 0) then
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
	if (bit.band(mode, 4) > 0) then
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
	if (bit.band(mode, 8) > 0) then
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
function blocktable:fillscatteredlist (list)
	local restbegin = false

	for cx = 1, BLOCK_WIDTH do
		for cy = BLOCK_HEIGHT, 1, -1 do
			if (restbegin) then
--				print("restbegin")
				if (self[cx][cy] ~= 0) then
					local block = block.new((cx-1)*BLOCK_SIZE,
											(cy-1)*BLOCK_SIZE,
											self[cx][cy])
					list:add(block)
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
function blocktable:trunkblocks (_sparksys)
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
					_sparksys:createspark((cx-1)*BLOCK_SIZE, 
										  (cy-1)*BLOCK_SIZE)
				end
			end
		end
	end

	return count				
end

-------------------------------------------------------------------------------

