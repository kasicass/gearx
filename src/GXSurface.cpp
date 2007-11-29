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
 * @file   GXSurface.cpp
 * @author ChenZaichun <ChenZaichun@gmail.com>
 * @date   Mon Nov 26 16:25:06 2007
 * 
 * @brief  WSurface Lua bind
 * 
 * 
 */

///////////////////////////////////////////////////////////////////////////////

#include "GXSurface.h"

///////////////////////////////////////////////////////////////////////////////
/** 
 * 
 * 
 * @param L 
 * 
 * @return 
 */
static int GXSurface_Create(lua_State* L)
{
	LuaBinder binder(L);
	HWND hwnd = (HWND)(int)((binder.checknumber(1)));
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(2, GXCANVAS_CLASSNAME));

	WSurface* surface = new WSurface;
	surface->Create(hwnd, *canvas);

	binder.pushusertype(surface, GXSURFACE_CLASSNAME);

	return 1;
}

/** 
 * 
 * 
 * @param L 
 * 
 * @return 
 */
static int GXSurface_Blit2Screen(lua_State* L)
{
	LuaBinder binder(L);

	WSurface* surface = (WSurface*)(binder.checkusertype(1, GXSURFACE_CLASSNAME));

	surface->Blit2Screen();

	return 0;
}

/** 
 * 
 * 
 * @param L 
 * 
 * @return 
 */
static int GXSurface_Destroy(lua_State* L)
{
	LuaBinder binder(L);

	WSurface* surface = (WSurface*)(binder.checkusertype(1, GXSURFACE_CLASSNAME));

	SAFEDELETE(surface);
    
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// 
static const luaL_reg GXSurfaceLib[] = {
	{"Create",		GXSurface_Create},
	{"Blit2Screen", GXSurface_Blit2Screen},
	{NULL,			NULL},
};

///////////////////////////////////////////////////////////////////////////////
/** 
 * 
 * 
 * @param L 
 * 
 * @return 
 */
extern "C"
int luaopen_GXSurfaceLib(lua_State* L)
{
	LuaBinder binder(L);
	binder.init(GXSURFACE_CLASSNAME, 0, GXSurfaceLib, GXSurface_Destroy);

	return 1;
}

///////////////////////////////////////////////////////////////////////////////
// end of GXSurface.cpp

