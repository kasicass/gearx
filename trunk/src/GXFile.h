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
 * @file   GXFile.h
 * @author ChenZaichun <ChenZaichun@gmail.com>
 * @date   Sun Nov 25 17:28:30 2007
 * 
 * @brief  WFile for lua
 * 
 * 
 */

#ifndef _GX_FILE_H
#define _GX_FILE_H

#include "GXInc.h"

/*!
 * registed functions:
 *
 *		OpenDataFile(const char* packagename)	/// open wdf package
 *		Load(const char *filename)				/// read the whole file to memory
 *		Open(const char *filename)				/// open a file
 *		Read(void *buffer,int s)				/// read file, the file pointer is current postion
 *		Skip(int s)								/// skip 
 *		Data()									/// get the data
 *		Size()
 *		Tell()
 *		Close()									/// close the file for read
 *		IsEnd()	
 *
 * Lua code example:
 *		local f = File.OpenDataFile("data.wdf")
 *		File.Load(f, "mainmenu.bmp")
 *		local data = File.Data(f)
 *		Bitmap.Load(data)
 *		...				-- automatic release by _gc, so you don't need to call Close
 *
 */
extern "C"
int luaopen_GXFileLib(lua_State* L);

#endif
