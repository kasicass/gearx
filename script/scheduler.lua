
--[[
    $Id: $
    
    Task Scheduleer
    CopyRight (c) GearX Team, 2007
    See LICENSE for more information
--]]

Scheduler = {}

function Scheduler:AddTask (name, task)
    self._tasks[name] = coroutine.create(task)
end

function Scheduler:Loop ()
    repeat
	for name, co in pairs(self._tasks) do
	    coroutine.resume(co)
	    if (coroutine.status(co) == "dead") then
		self._tasks[name] = nil
	    end
	end
    until not next(self.tasks)
end



