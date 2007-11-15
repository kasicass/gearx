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

	$Id$
	ChenZaichun@gmail.com
--]]

-------------------------------------------------------------------------------
--module("button", package.seeall)

-- Button class
Button = {}

----------------------------------------------------------------------------
-- create a button
-- 
-- @param pkgname wdf file name for container the bitmap
-- @param filename filename of the bitmap
-- @param frames total frames of the bitmap
-- @param vertical is the frames vertically?
-- @param x x coordinate
-- @param y y coordinate
-- 
-- @return the created button
-- 
function Button.New(pkgname, filename, frames, vertical, x, y)
	local self = {
		_frames = frames or 2,
		_x = x or 0,
		_y = y or 0,
		_laststate = -1,
		_state = 1,
	}
	
	self._bmp = WBitmap.Load(pkgname, filename)
	
	local w, h
	local x_delta, y_delta = 0, 0
	vertical = vertical or true
	if vertical then
		w = self._bmp:W()
		h = self._bmp:H() / self._frames
		y_delta = h
	else
		w = self._bmp:W() / self._frames
		h = self._bmp:H()
		x_delta = w
	end
	
	for i = 1, self._frames do
		self[i] = WBitmap.Create(self._bmp, (i-1)*x_delta, 
					(i-1)*y_delta, w, h)
	end

	setmetatable(self, {__index = Button})
	
	return self
end

-------------------------------------------------------------------------------
-- set the button postion
-- 
-- @param self button position to be changed
-- @param x x coordinate
-- @param y y coordinate
function Button:SetPos(x, y)
	self._x = x
	self._y = y
end

-------------------------------------------------------------------------------
-- button Draw function
-- 
-- @param self button to be drawn
-- @param canvas canvas which the button will be drawn on
function Button:Draw(canvas)
	if (self._laststate ~= self._state) then
		canvas:Change()
		self._laststate = self._state
	else
		canvas:UnChange()
	end

	self[self._state]:Draw(canvas, self._x, self._y, BLIT_STYLE.BLIT_MASK)
end

-------------------------------------------------------------------------------
-- change the status of the button
-- 
-- @param self button 
-- @param state new state of the button
function Button:StatusChange (state)
	self._state = state
end

-------------------------------------------------------------------------------
-- mouse move message handler of button, the function is to handle
-- 		the mouse hover message
-- 
-- @param self button
-- @param x x coordinate of the mouse
-- @param y y coordinate of the mouse
function Button:IsCover(x, y)
	local cover = (self[self._state]:IsCover(x-self._x, y-self._y) ~= 0)
	if (cover) then
		self._state = 2
	else
		self._state = 1
	end
	
	return cover
end

-------------------------------------------------------------------------------




