--[[
	$Id$
	
	Music
	CopyRight (c) GearX Team, 2007
	See LICENSE for more information

	TAB SIZE: 4
--]]


Music = { TYPE = { STREAM = 1, SAMPLE = 2} }
setmetatable(Music, {__index = GXMusic})
