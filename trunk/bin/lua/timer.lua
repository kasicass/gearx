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

Timer = {}
--setmetatable(Timer, {__index = GXTimer})

-------------------------------------------------------------------------------
-- create a new timer
-- \param duration: duration of the timer
-- \return the timer
function Timer.New (duration)
	local self = {}
	self._timer = GXTimer.Create()
	self._duration = duration or 100
	self._active = false

	setmetatable(self, {__index = Timer})
	
	return self
end

-------------------------------------------------------------------------------
-- reset the timer duration
function Timer:SetDuration (duration)
	self._duration = duration
end

-------------------------------------------------------------------------------
-- start the timer
function Timer:Start ()
	self._active = true
	self._timer:Start()
end

-------------------------------------------------------------------------------
-- stop the timer
function Timer:Stop ()
	self._active = false
	self._timer:Stop()
end

-------------------------------------------------------------------------------
-- test for the timer is atcive
function Timer:IsActive ()
	if (not self._active) then return false end
	
	duration = self._timer:GetTime()
	if (duration >= self._duration) then
		self._timer:Reset()
		return true
	end
end


-------------------------------------------------------------------------------
-- reset timer
function Timer:Reset()
	self._timer:Reset()
end

-------------------------------------------------------------------------------
