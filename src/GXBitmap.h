/*  emacs: -*- mode: c; coding: utf-8; -*-  */

/*
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
*/

/**
 * @file   GXBitmap.h
 * @author ChenZaichun <ChenZaichun@gmail.com>
 * @date   Sun Nov 25 17:27:38 2007
 * 
 * @brief  WBitmap for Lua
 * 
 * 
 */

#ifndef _GX_BITMAP_H
#define _GX_BITMAP_H

#include "GXInc.h"

/*!
 * for register GXBitmap functions
 * 
 * we expose this functions:
 *		void Load(void* bmpdata);
 *		void Create(GXBitmap* parent, int x, int y, int w, int h);
 *		void Draw(WCanvas& canvas, int x, int y, int style);
 *
 * we can use this functions in Lua:
 *		Bitmap.Load()							-- load from resource to create a bitmap
 *		Bitmap.Create(parent, x, y, w, h)		-- create from a parent bitmap
 *		Bitmap.Draw(bmp, canvas, x, y, style)	-- draw the bitmap
 *		Bitmap.Destroy(bmp)						-- destory the bitmap object
 */
extern "C"
int luaopen_GXBitmapLib(lua_State* L);

#endif
