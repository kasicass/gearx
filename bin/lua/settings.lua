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
-- require files
require("gamesetting")
require("serialize")
-- dofile("lua/cfg.lua")
-- dofile("lua/serialize.lua")

module("settings", package.seeall)

-------------------------------------------------------------------------------
-- return music setting
function isplaymusic ()
	return gamesetting.MUSIC
end

-- return sound setting
function isplaysound ()
	return gamesetting.SOUND
end

function playmusic (play)
	gamesetting.MUSIC = play
end

function playsound (play)
	gamesetting.SOUND = play
end

function fullscreen (fs)
	gamesetting.FULLSCREEN = fs
end

function isfullscreen ()
	return gamesetting.FULLSCREEN
end

-------------------------------------------------------------------------------
-- save settings
function savesettings ()
	local f = assert(io.open("lua/gamesetting.lua", "w"))
	local str = "gamesetting = " .. serialize.serialize(gamesetting)
	f:write(str)
	f:close()
end

-------------------------------------------------------------------------------
