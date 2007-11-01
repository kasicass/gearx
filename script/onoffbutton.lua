
--[[
    $Id$
	
	On/off button
	CopyRight (c) GearX Team, 2007
	See LISENCE for more information

	TAB SIZE: 4
--]]

OnOffButton = {}

-------------------------------------------------------------------------------
function OnOffButton.New(pkgname, filenameon, filenameoff, frames,
						 vertical, x1, y1, x2, y2, state)
	local self = {
		_x1 = x1 or 0,
		_y1 = y1 or 0,
		_x2 = x2 or 0,
		_y2 = y2 or 0,
		_frames = frames or 2,
		_state = state or true,
	}
	self._laststate = not self._state

	self._bmpon = WBitmap.Load(pkgname, filenameon)
	self._bmpoff = WBitmap.Load(pkgname, filenameoff)

	local w, h, x_delta, y_delta = 0, 0, 0, 0
	if (vertical) then
		w = self._bmpon:W()
		h = self._bmpon:H() / self._frames
		y_delta = h
	else
		w = self._bmpon:W() / self._frames
		h = self._bmpon:H()
		x_delta = w
	end

	self._on = {}
	self._off = {}

	for i = 1, self._frames do
		self._on[i] = WBitmap.Create(self._bmpon, 
									 (i-1)*x_delta, (i-1)*y_delta,
									 w, h)
		self._off[i] = WBitmap.Create(self._bmpoff,
									  (i-1)*x_delta, (i-1)*y_delta,
									  w, h)
	end

	setmetatable(self, {__index = OnOffButton})

	return self
end

function OnOffButton:SetPos (x1, y1, x2, y2)
	self._x1, self._y1, self._x2, self._y2 = x1, y1, x2, y2
end

function OnOffButton:SetStatePos (x, y, state)
	if (state) then
		self._x1, self._y1 = x, y
	else
		self._x2, self._y2 = x, y
	end
end

function OnOffButton:SetState (state)
	self._state = state
end

function OnOffButton:IsCover (x, y)
	local cover
	if (self._state) then
		cover = (self._off[1]:IsCover(x - self._x2, y - self._y2) ~= 0)
	else
		cover = (self._on[1]:IsCover(x - self._x1, y - self._y1) ~= 0)
	end

	if (cover) then
		print("yes")
		self._state = not self._state
	end

	return cover
end

function OnOffButton:Draw (canvas)
	if (self._laststate ~= self._state) then
		canvas:Change()
		self._laststate = self._state
	else
		canvas:UnChang()
	end

	if (self._state) then
		self._on[2]:Draw(canvas, self._x1, self._y1, BLIT_STYLE.BLIT_MASK)
		self._off[1]:Draw(canvas, self._x2, self._y2, BLIT_STYLE.BLIT_MASK)
	else
		self._on[1]:Draw(canvas, self._x1, self._y1, BLIT_STYLE.BLIT_MASK)
		self._off[2]:Draw(canvas, self._x2, self._y2, BLIT_STYLE.BLIT_MASK)
	end
end
