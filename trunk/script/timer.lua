
--[[
	$Id: $
	
	Timer
	CopyRight (c) GearX Team, 2007
	See LIENCE for more information

	TAB SIZE: 4
--]]

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
