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
require("spark")

-------------------------------------------------------------------------------
sparkimg = {}

local SPARK_TOTAL_COUNT = 10 	-- image count

function sparkimg.init ()
	local self = {}

	self._bmp = WBitmap.Load(MAIN_RES_PKG,
							 PLAYING_PIC_PATH .. "spark.bmp")
	local w, h = self._bmp:W() / SPARK_TOTAL_COUNT, self._bmp:H()

	for i = 1, SPARK_TOTAL_COUNT do
		self[i] = WBitmap.Create(self._bmp, (i-1)*w, 0, w, h)
	end

	setmetatable(self, {__index = sparkimg})

	return self
end

-------------------------------------------------------------------------------
-- Draw Sparks
-- 
function sparkimg:draw (canvas, sparks)
	if (#sparks == 0) then
		return
	end

	for i = 1, #sparks do
		-- call spark draw
		self[sparks[i]._frame]:Draw(canvas, 
					 sparks[i]._x + BLOCK_OFFSET_X,
					 sparks[i]._y + BLOCK_OFFSET_Y,
					  BLIT_STYLE.BLIT_MASK)
	end
end

-------------------------------------------------------------------------------

