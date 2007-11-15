/*  emacs: -*- mode: cc; coding: gb2312 -*- TAB SIZE: 4 -*-  */

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

#ifndef _GX_SURFACE_H
#define _GX_SURFACE_H

#include "GXInc.h"

/** 
 * for register WSurface in Lua
 * 
 * @param L pointer to lua state
 * 
 * @return always return 1
 */
int luaopen_GXSurfaceLib(lua_State* L);

#endif
