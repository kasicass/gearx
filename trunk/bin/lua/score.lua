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
-- file contain score infmation
-- 
require("highscore")
require("serialize")

module("score", package.seeall)

-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
-- check score
-- 
-- @param score 
-- 
function checkhighscore (score)
	if (#highscore < 10) then
		return true
	elseif (#highscore == 10) then
		if (highscore[10][2] < score) then
			return true
		end
	end

	return false
end

-------------------------------------------------------------------------------
-- sort highsore
-- 
function sorthighscore ()
	local i = #highscore
	while (i > 1) do
		if (highscore[i][2] > highscore[i-1][2]) then
			highscore[i][2], highscore[i-1][2] = 
				highscore[i-1][2], highscore[i][2]
			highscore[i][1], highscore[i-1][1] =
				highscore[i-1][1], highscore[i][1]
		elseif (highscore[i][1] > highscore[i-1][1]) then
			highscore[i][2], highscore[i-1][2] = 
				highscore[i-1][2], highscore[i][2]
			highscore[i][1], highscore[i-1][1] =
				highscore[i-1][1], highscore[i][1]
		else
			break
		end

		i = i - 1
	end
end

-------------------------------------------------------------------------------
-- add score to highscore table
-- 
-- @param name
-- @param score
-- 
function addscoretohighscore (name, score)
	local count = #highscore
	if (count < 10) then
		table.insert(highscore, {name, score})
	elseif (count == 10) then
		table.remove(highscore, 10)
		table.insert(highscore, score)
	end

	sorthighscore()
end

-------------------------------------------------------------------------------
-- save high score
-- 
function savehighscore ()
	local f = assert(io.open("lua/highscore.lua", "w"))
	local str = "highscore = " .. serialize.serializenoidx(highscore)
	f:write(str)
	f:close()
end
