
--[[
	$Id$
	
	Animation
	CopyRight (c) GearX Team, 2007
	See LISENCE for more information
	
	TAB SIZE: 4
--]]

dofile("../script/timer.lua")

Animation = {}

function Animation.New(pkgname, filename, frames, vertical, x, y, dration)
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

function Animation:SetPos(x, y)
	self._x = x;
	self._y = y;
end

function Animation:SetDuration(duration)
	self._timer:SetDuration(duration)
end

function Animation:Start()
	self._timer:Start()
end

function Animation:Stop()
	self._timer:Stop()
end

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