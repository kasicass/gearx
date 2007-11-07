
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
-- require files
dofile("../script/cfg.lua")
dofile("../script/serialize.lua")

-------------------------------------------------------------------------------
-- return music setting
function IsPlayMusic ()
	return GAME_SETTING.MUSIC
end

-- return sound setting
function IsPlaySound ()
	return GAME_SETTING.SOUND
end

function PlayMusic (play)
	GAME_SETTING.MUSIC = play
end

function PlaySound (play)
	GAME_SETTING.SOUND = play
end

function FullScreen (fs)
	GAME_SETTING.FULLSCREEN = fs
end

function IsFullScreen ()
	return GAME_SETTING.FULLSCREEN
end

-------------------------------------------------------------------------------
-- save settings
function SaveSettings ()
	local f = assert(io.open("../script/cfg.lua", "w"))
	local str = "GAME_SETTING = " .. serialize(GAME_SETTING)
	f:write(str)
	f:close()
end

-------------------------------------------------------------------------------
