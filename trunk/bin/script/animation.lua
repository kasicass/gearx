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
-- animation class
Animation = {}

-------------------------------------------------------------------------------
-- create animation
--
-- @param pkgname	wdf package name
-- @param filename	file of the bitmap
-- @param frame		total frames
-- @param vertical	is bitmap vertically?
-- @param x			x coordinate
-- @param y			y coordinate
-- @param duration	duration of animation
--
-- @return animation obj
function Animation.New(pkgname, filename, frames, vertical, x, y, duration)
	local self= {
		_frames = frames,
		_x = x or 0,
		_y = y or 0,
		_timer = Timer.New(duration),
		_current = 0,
		_lastframe = -1,
	}

	self._bmp = WBitmap.Load(pkgname, filename)

	vertical = vertical or false
	local w, h, x_delta, y_delta = 0, 0, 0, 0
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

	setmetatable(self, {__index = Animation})

	return self
end

-------------------------------------------------------------------------------
-- get animation width
--
-- @return animation width 
function Animation:W()
	return self[1]:W()
end

-------------------------------------------------------------------------------
-- get animation height
-- 
-- @return animation height
function Animation:H()
	return self[1]:H()
end

-------------------------------------------------------------------------------
-- set animation position
-- 
-- @param x		x coordinate
-- @param y		y coordinate
function Animation:SetPos(x, y)
	self._x = x
	self._y = y
end

-------------------------------------------------------------------------------
-- set animation duration
-- 
-- @param duration time count
function Animation:SetDuration(duration)
	self._timer:SetDuration(duration)
end

-------------------------------------------------------------------------------
-- start animation
-- 
function Animation:Start()
	self._timer:Start()
end

-------------------------------------------------------------------------------
-- stop animation
-- 
function Animation:Stop()
	self._timer:Stop()
end

-------------------------------------------------------------------------------
-- draw the animation
-- 
-- @param canvas canvas to be drawn on
function Animation:Draw(canvas)
	if (self._timer:IsActive()) then
		self._current = math.fmod(self._current + 1, self._frames)
	end
	
	if (self._lastframe ~= self._current) then
		canvas:Change()
		self._lastframe = self._current
	else 
		canvas:UnChange()
	end

	self[self._current+1]:Draw(canvas, self._x, self._y, BLIT_STYLE.BLIT_MASK)
end

-------------------------------------------------------------------------------
