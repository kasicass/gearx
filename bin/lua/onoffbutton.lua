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
onoffbutton = {}

-------------------------------------------------------------------------------
local onoffbmp = {}

-------------------------------------------------------------------------------
function onoffbutton.init(pkgname, filenameon, filenameoff, frames, vertical)
	onoffbmp._bmpon = WBitmap.Load(pkgname, filenameon)
	onoffbmp._bmpoff = WBitmap.Load(pkgname, filenameoff)

	local w, h, x_delta, y_delta = 0, 0, 0, 0
	if (vertical) then
		w = onoffbmp._bmpon:W()
		h = onoffbmp._bmpon:H() / frames
		y_delta = h
	else
		w = onoffbmp._bmpon:W() / frames
		h = onoffbmp._bmpon:H()
		x_delta = w
	end

	onoffbmp._on = {}
	onoffbmp._off = {}
	for i = 1, frames do
		onoffbmp._on[i] = WBitmap.Create(onoffbmp._bmpon, 
										 (i-1)*x_delta,
										 (i-1)*y_delta,
										 w, h)
		onoffbmp._off[i] = WBitmap.Create(onoffbmp._bmpoff,
										  (i-1)*x_delta,
										  (i-1)*y_delta,
										  w, h)
	end
end

function onoffbutton.new(x1, y1, x2, y2, state)
	local self = {
		_x1 = x1 or 0,
		_y1 = y1 or 0,
		_x2 = x2 or 0,
		_y2 = y2 or 0,
		_state = state,
		_laststate = not state,
	}

	setmetatable(self, {__index = onoffbutton})
	return self
end

function onoffbutton:draw (canvas)
	if (self._laststate ~= self._state) then
		canvas:Change()
		self._laststate = self._state
	else
		canvas:UnChange()
	end

	if (self._state) then
		onoffbmp._on[2]:Draw(canvas, self._x1, self._y1, BLIT_STYLE.BLIT_MASK)
		onoffbmp._off[1]:Draw(canvas, self._x2, self._y2, BLIT_STYLE.BLIT_MASK)
	else
		onoffbmp._on[1]:Draw(canvas, self._x1, self._y1, BLIT_STYLE.BLIT_MASK)
		onoffbmp._off[2]:Draw(canvas, self._x2, self._y2, BLIT_STYLE.BLIT_MASK)
	end
end
function onoffbutton:iscover (x, y)
	local cover
	if (self._state) then
		cover = (onoffbmp._off[1]:IsCover(x - self._x2, y - self._y2) ~= 0)
	else
		cover = (onoffbmp._on[1]:IsCover(x - self._x1, y - self._y1) ~= 0)
	end

	if (cover) then
		self._state = not self._state
	end

	return cover
end

function onoffbutton:setstate(state)
	self._state = state
end

function onoffbutton:SetPos (x1, y1, x2, y2)
	self._x1, self._y1, self._x2, self._y2 = x1, y1, x2, y2
end

function onoffbutton:setstatepos(x, y, state)
	if (state) then
		self._x1, self._y1 = x, y
	else
		self._x2, self._y2 = x, y
	end
end
