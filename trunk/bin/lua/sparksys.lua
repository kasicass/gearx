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
require("blockcfg")
require("timer")
require("spark")

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
-- Sparak System
-- 
sparksys = {}

local SPARK_TOTAL_COUNT = 10

-------------------------------------------------------------------------------
-- Init Spark System
-- 
function sparksys.init ()
	local self = {}

	setmetatable(self, {__index = sparksys})

	self._sparks = {}
	self._timermotion = timer.new(30)
	self._timerframe = timer.new(30)
	self._timermotion:start()
	self._timerframe:start()

	return self
end

-------------------------------------------------------------------------------
-- Create Spark
-- 
function sparksys:createspark(x, y)
	local spark = spark.new(x, y)
	table.insert(self._sparks, spark)
--	print("count: ", #self._sparks)
end


-------------------------------------------------------------------------------
-- reset sparks
-- 
function sparksys:reset ()
	self._sparks = {}
end

function sparksys:add (x, y, frame)
	table.insert(self._sparks, spark.new(x, y, frame))
end

-------------------------------------------------------------------------------
-- moving sparks
-- 
function sparksys:move ()
	local count = #self._sparks
	if (count == 0) then return end

	if (self._timermotion:isactive()) then
		for i = 1, count do
			self._sparks[i]:move()
		end
	end

	if (self._timerframe:isactive()) then
		local i = 1
		while (i <= count) do
			if (self._sparks[i]._frame >= SPARK_TOTAL_COUNT) then
				table.remove(self._sparks, i)
				count = count - 1
			else
				self._sparks[i]._frame = self._sparks[i]._frame + 1
				i = i + 1
			end
		end
	end
end

-------------------------------------------------------------------------------

function sparksys:getcount ()
	return #self._sparks
end

function sparksys:getspark(idx)
	return self._sparks[idx]
end

-------------------------------------------------------------------------------
