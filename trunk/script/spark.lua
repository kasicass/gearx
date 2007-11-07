
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

	TAB SIZE: 4
--]]

-------------------------------------------------------------------------------
Spark = {}

-------------------------------------------------------------------------------
-- create spark images
-- \param x: x coordinate
-- \param y: y coordinate
function Spark.New (x, y)
	local self = {
		_x = x,
		_y = y,
		_frame = 1,
		_dx = math.random(-10, 10),
		_dy = math.random(-10, -40),
		_frame = 1,
	}

	if (self._dy > -20) then
		self._dyacc = math.random(2, 3)
	elseif (self._dy > -30) then
		self._dyacc = math.random(3, 4)
	else
		self._dyacc = math.random(4, 4)
	end

	setmetatable(self, {__index = Spark})

	return self
end

-------------------------------------------------------------------------------
-- move the sparks
function Spark:Move ()
	self._x = self._x + dx;

	-- x axis
	if (self._x < 0) then
		self._x = 0
		self._dx = -self._dx
	elseif (self._x > BLOCK_TOTAL_WIDTH - BLOCK_SIZE - 1) then
		self._x = BLOCK_TOTAL_WIDTH - BLOCK_SIZE - 1
		self._dx = -self._dx
	end

	self._y = self._y + self._dy

	-- y axis
	self._dy = self._dy + self._dyacc
end

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
-- Sparak System
SparkSystem = {}

local SPARK_TOTAL_COUNT = 10 	-- image count

-------------------------------------------------------------------------------
-- Init Spark System
function SparkSystem.Init ()
	local self = {}
	self._bmp = WBitmap.Load(MAIN_RES_PKG,
							 PLAYING_PIC_PATH .. "spark.bmp")
	local w, h = self._bmp:W() / SPARK_TOTAL_COUNT, self._bmp:H()

	for i = 1, SPARK_TOTAL_COUNT do
		self[i] = WBitmap.Create(self._bmp, (i-1)*w, 0, w, h)
	end

	setmetatable(self, {__index = SparkSystem})

	self._sparks = {}
	self._timermotion = Timer.New(30)
	self._timerframe = Timer.New(50)

	return self
end

-------------------------------------------------------------------------------
-- Create Spark
function SparkSystem:CreateSpark(x, y)
	table.insert(self._sparks, Spark.New(x, y))
end

-------------------------------------------------------------------------------
-- Draw Sparks
function SparkSystem:Draw (canvas)
	if (#self._sparks == 0) then
		return
	end

	for i = 1, #self._sparks do
		self[self._sparks[i]._frame]:Draw(canvas, 
										  self._sparks[i]._x + BLOCK_OFFSET_X,
										  self._sparks[i]._y + BLOCK_OFFSET_Y,
										  BLIT_STYLE.BLIT_MASK)
	end
end

-------------------------------------------------------------------------------
-- reset sparks
function SparkSystem:Reset ()
	self._sparks = {}
end

-------------------------------------------------------------------------------
-- moving sparks
function SparkSystem:Move ()
	local count = #self._sparks
	if (count == 0) then return end

	self._timermotion:Start()
	if (self._timermotion:IsActive()) then
		for i = 1, count do
			self._sparks[i]:Move()
		end
	end

	self._timerframe:Start()
	if (self._timerframe:IsActive()) then
		for i = 1, count do
			if self._sparks[i]._frame > SPARK_TOTAL_COUNT - 1 then
				table.remove(self._sparks, i)
			else
				self._sparks[i]._frame = self._sparks[i]._frame + 1
			end
		end
	end
end

-------------------------------------------------------------------------------
