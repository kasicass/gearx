-- emacs: -*- lua-mode -*- TAB SIZE: 4 -*- 

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

-------------------------------------------------------------------------------
-- for holding blocks
Block = {}

-------------------------------------------------------------------------------
-- init block container
function Block.Init ()
	local self = {}

	for i = 1, BLOCK_WIDTH do
		self[i] = {}
		for j = 1, BLOCK_HEIGHT do
			self[i][j] = 0
		end
	end

	setmetatable(self, {__index = Block})

-- 	str = serialize(self)
-- 	print(str)

	return self
end

-------------------------------------------------------------------------------
-- add block to container
function Block:Add (x, y, idx)
	self[x][y] = idx
end

-------------------------------------------------------------------------------
-- reset block
function Block:Reset ()
	for i = 1, BLOCK_WIDTH do
		for j = 1, BLOCK_HEIGHT do
			self[i][j] = 0
		end
	end
end

-------------------------------------------------------------------------------
-- add triblock to container
function Block:AddTri (triblock)
--[[	local x = triblock:XIdx()
	local y = triblock:YIdx()

	self[x][y] = triblock:GetIdx(1)
	self[x][y+1] = triblock:GetIdx(2)
	self[x][y+2] = triblock:GetIdx(3) 
--]]
end

-------------------------------------------------------------------------------
-- get block info
function Block:GetImgIdx (x, y)
	printf("x, y: %d, %d", x, y)
-- 	str = serialize(self[x])
-- 	print(str)
-- 	print(rawget(self[x], y))
 	return self[x][y]
--	return rawget(self[x], y)
end

-------------------------------------------------------------------------------
-- remove block from container
function Block:Remove(x, y)
	self[x][y] = 0
end

-------------------------------------------------------------------------------
-- draw blocks
function Block:Draw (canvas, gears)
--[[	for i, t in ipairs(self) do
		for j, v in ipairs(t) do
			if (v > 0) then
				gears:Draw(canvas, i*BLOCK_SIZE, j*BLOCK_SIZE, v)
			end
		end
	end
--]]
end

-------------------------------------------------------------------------------
-- check truncate
function Block:CheckTrunk ()
	
end

-------------------------------------------------------------------------------
--