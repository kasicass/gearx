//  emacs: -*- mode: c++; coding: utf-8; -*-

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
 * @file   GXLua.hpp
 * @author ChenZaichun <ChenZaichun@gmail.com>
 * @date   Mon Nov 26 15:59:38 2007
 * 
 * @brief  Lua header files for C++
 *
 *		   <<extern "C">> not supplied automatically because
 *		   Lua also compiles as C++
 * 
 */


#ifndef _GX_LUA_HPP
#define _GX_LUA_HPP

#ifdef __cplusplus
extern "C" {
#endif
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined DEBUG || defined _DEBUG
#pragma comment(lib, "lua51D.lib")
#else
#pragma comment(lib, "lua51.lib")
#endif


//void error(lua_State* L, const char* fmt, ...)
//{
//	va_list argp;
//	va_start(argp, fmt);
//	vfprintf(stderr, fmt, argp);
//	va_end(argp);
//	lua_close(L);
//	exit(EXIT_FAILURE);
//}

#endif
