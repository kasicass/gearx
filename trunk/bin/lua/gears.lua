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
-- gear class 
gears = {}

-------------------------------------------------------------------------------
-- init Gears
function gears.init()
	local self = {}
	-- load main bitmap
	self._img = WBitmap.Load(MAIN_RES_PKG,
							  PLAYING_PIC_PATH .. "gear.bmp")

	-- create sub bitmaps
	local w, h = self._img:W() / GEARS_COUNT, self._img:H()
	self._gear = {}
	for i = 1, GEARS_COUNT do
		self._gear[i] = WBitmap.Create(self._img, (i-1)*w, 
										0, w, h)
	end

	setmetatable(self, {__index = gears})

	return self
end

-------------------------------------------------------------------------------
-- draw gear
function gears:draw (canvas, x, y, idx)
	-- call bitmap draw
	self._gear[idx]:Draw(canvas, x, 
						 y, BLIT_STYLE.BLIT_MASK)
end

-------------------------------------------------------------------------------
-- Get image by index
-- \param idx: index of the image
-- \return the image (WBitmap)
function gears:getimg (idx)
	return self._gear[idx]
end

-------------------------------------------------------------------------------
-- gear actions


-------------------------------------------------------------------------------
-- clear memory
