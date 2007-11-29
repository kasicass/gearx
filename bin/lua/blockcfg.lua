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

module("blockcfg", package.seeall)

-- globals
_G.BLOCK_SIZE = 32 				-- each gear width
_G.BLOCK_WIDTH = 8					-- block x-axis count
_G.BLOCK_HEIGHT = 16				-- block y-axis count
_G.GEARS_COUNT = 6					-- total image of gears
_G.BLOCK_TOTAL_WIDTH = BLOCK_WIDTH * BLOCK_SIZE -- block size
_G.BLOCK_TOTAL_HEIGHT = BLOCK_HEIGHT * BLOCK_SIZE -- block height
_G.BLOCK_OFFSET_X = 280	     	-- start of the drawing area 
_G.BLOCK_OFFSET_Y = 0				--
