
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

	TAB SIZE: 4
--]]

-------------------------------------------------------------------------------


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



