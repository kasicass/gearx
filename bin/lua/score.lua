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

	$Id: $
	ChenZaichun@gmail.com
--]]

-------------------------------------------------------------------------------
-- file contain score infmation
dofile("lua/highscore.lua")

-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
-- check score
-- 
-- @param score 
function CheckHighScore (score)
	if (#HIGH_SCORE < 10) then
		return true
	elseif (#HIGH_SCORE == 10) then
		if (HIGH_SCORE[10][2] < score) then
			return true
		end
	end

	return false
end

-------------------------------------------------------------------------------
-- sort highsore
-- 
function SortHighScore ()
	local i = #HIGH_SCORE
	while (i > 1) do
		if (HIGH_SCORE[i][2] > HIGH_SCORE[i-1][2]) then
			HIGH_SCORE[i][2], HIGH_SCORE[i-1][2] = 
				HIGH_SCORE[i-1][2], HIGH_SCORE[i][2]
			HIGH_SCORE[i][1], HIGH_SCORE[i-1][1] =
				HIGH_SCORE[i-1][1], HIGH_SCORE[i][1]
		elseif (HIGH_SCORE[i][1] > HIGH_SCORE[i-1][1]) then
			HIGH_SCORE[i][2], HIGH_SCORE[i-1][2] = 
				HIGH_SCORE[i-1][2], HIGH_SCORE[i][2]
			HIGH_SCORE[i][1], HIGH_SCORE[i-1][1] =
				HIGH_SCORE[i-1][1], HIGH_SCORE[i][1]
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
function AddScoreToHighScore (name, score)
	local count = #HIGH_SCORE
	if (count < 10) then
		table.insert(HIGH_SCORE, {name, score})
	elseif (count == 10) then
		table.remove(HIGH_SCORE, 10)
		table.insert(HIGH_SCORE)
	end

	SortHighScore()
end

-------------------------------------------------------------------------------
-- save high score
-- 
function SaveHighScore ()
	local f = assert(io.open("lua/highscore.lua", "w"))
	local str = "HIGH_SCORE = " .. serializenoidx(HIGH_SCORE)
	f:write(str)
	f:close()
end
