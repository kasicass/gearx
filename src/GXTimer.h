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

#ifndef _GX_TIMER_H
#define _GX_TIMER_H

#include "GXInc.h"

/// visible name of timer in Lua


/** 
 * for register GXTimer in Lua
 * 
 * @param L pointer to lua_State
 * 
 * @return always return 1
 */
extern "C"
int luaopen_GXTimer(lua_State* L);

#endif
