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

-- operation of gearx
operations = {
	-- client to server
	MOVELEFT = 1,
	MOVERIGHT = 2,
	UPSCROLLIMG = 3,
	DOWNSCROLLIMG = 4,
	MOVEDOWN = 5,
	EXIT = 6,

	-- both server and client receive this message
	START = 7,

	-- server to client
	UPDATE = 8,
	OVER = 9,
}

-------------------------------------------------------------------------------
-- playing scene state
PLAYING_STATE = {
	INIT = 1,
	PLAYING = 2,
	PAUSE = 3,
	OVER = 4,
	EXIT = 5,					-- exit playing state
}
