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
 * @file   GXBitmap.cpp
 * @author ChenZaichun <ChenZaichun@gmail.com>
 * @date   Sun Nov 25 17:19:45 2007
 * 
 * @brief  WBitmap for Lua
 * 
 * 
 */

///////////////////////////////////////////////////////////////////////////////
#include "GXBitmap.h"

///////////////////////////////////////////////////////////////////////////////
/** 
 * load bitmap from wdf package
 * 
 * @param L pointer to lua
 *
 *			parameter from lua:
 *				pkgname wdf package file name
 *				filename file to be loaded
 * 
 * @return 1
 *
 *			return WBitmap object to lua
 */
static int WBitmap_Load(lua_State* L)
{
	LuaBinder binder(L);
	const char* pkgname = binder.checkstring(1);
	const char* filename = binder.checkstring(2);
	WFile f;
	WFile::OpenDataFile(pkgname);
	f.Load(filename);
	WBitmap* bmp = new WBitmap;
	assert(bmp);
	bmp->Load(f);

	binder.pushusertype(bmp, GXBITMAP_CLASSNAME);

	return 1;
}

/** 
 * destroy wbitmap object, called by lua __gc
 * 
 * @param L 
 * 
 * @return 
 */
static int WBitmap_Destory(lua_State* L)
{
	LuaBinder binder(L);
	WBitmap* bmp = (WBitmap*)(binder.checkusertype(1, GXBITMAP_CLASSNAME));
	SAFEDELETE(bmp);

	return 0;
}

/** 
 * create sub bitmap by parent bitmap
 * 
 * @param L 
 * 
 * @return 1
 *
 *			WBitmap object for lua
 */
static int WBitmap_Create(lua_State* L)
{
	LuaBinder binder(L);
	WBitmap* bmpparent = (WBitmap*)(binder.checkusertype(1, GXBITMAP_CLASSNAME));
	int x = (int)(binder.checknumber(2));
	int y = (int)(binder.checknumber(3));
	int w = (int)(binder.checknumber(4));
	int h = (int)(binder.checknumber(5));
	WBitmap* bmp = new WBitmap;
	bmp->Create(*bmpparent, x, y, w, h);
	binder.pushusertype(bmp, GXBITMAP_CLASSNAME);

	return 1;
}

/** 
 * create empty bitmap by color
 * 
 * @param L 
 * 
 * @return 1
 *
 *			WBitmap object
 */
static int WBitmap_CreateEmpty(lua_State* L)
{
	LuaBinder binder(L);
	int x = (int)(binder.checknumber(1));
	int y = (int)(binder.checknumber(2));
	int color = (int)(binder.checknumber(3));
	WBitmap* bmp = new WBitmap;
	bmp->Create(x, y);
	bmp->Clear(color);

	binder.pushusertype(bmp, GXBITMAP_CLASSNAME);

	return 1;
}

/** 
 * 
 * 
 * @param L 
 * 
 * @return 
 */
static int WBitmap_Draw(lua_State* L)
{
	LuaBinder binder(L);
	WBitmap* bmp = (WBitmap*)(binder.checkusertype(1, GXBITMAP_CLASSNAME));
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(2, GXCANVAS_CLASSNAME));
	int x = (int)(binder.checknumber(3));
	int y = (int)(binder.checknumber(4));
	int style = (int)(binder.checknumber(5));

	canvas->ViewPort(x, y);
	canvas->Draw(*bmp, style);

	return 0;
}

/** 
 * 
 * 
 * @param L 
 * 
 * @return 
 */
static int WBitmap_GetW(lua_State* L)
{
	LuaBinder binder(L);
	WBitmap* bmp = (WBitmap*)(binder.checkusertype(1, GXBITMAP_CLASSNAME));

	binder.pushnumber((lua_Number)(bmp->GetW()));

	return 1;
}

/** 
 * 
 * 
 * @param L 
 * 
 * @return 
 */
static int WBitmap_GetH(lua_State* L)
{
	LuaBinder binder(L);
	WBitmap* bmp = (WBitmap*)(binder.checkusertype(1, GXBITMAP_CLASSNAME));

	binder.pushnumber((lua_Number)(bmp->GetH()));

	return 1;
}

/** 
 * 
 * 
 * @param L 
 * 
 * @return 
 */
static int WBitmap_IsCover(lua_State* L)
{
	LuaBinder binder(L);
	WBitmap* bmp = (WBitmap*)(binder.checkusertype(1, GXBITMAP_CLASSNAME));
	int x = (int)(binder.checknumber(2));
	int y = (int)(binder.checknumber(3));

	int ret = bmp->IsCover(WPoint(x, y));
	binder.pushnumber((lua_Number)(ret));

	return 1;
}

/** 
 * 
 * 
 * @param L 
 * 
 * @return 
 */
static int WBitmap_SetData(lua_State * L)
{
	LuaBinder binder(L);
	WBitmap* bmp = (WBitmap*)(binder.checkusertype(1, GXBITMAP_CLASSNAME));
	int data = (int)(binder.checknumber(2));

	bmp->SetUserData(data);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
/// bitmap exported function for lua
static const luaL_reg WBitmapLib[] = {
	{"Load",		WBitmap_Load},
	{"Create",		WBitmap_Create},
	{"Draw",		WBitmap_Draw},
	{"W",			WBitmap_GetW},
	{"H",			WBitmap_GetH},
	{"IsCover",		WBitmap_IsCover},
	{"SetData",		WBitmap_SetData},
	{"CreateEmpty",	WBitmap_CreateEmpty},
	{NULL,			NULL},
};

///////////////////////////////////////////////////////////////////////////////
/** 
 * 
 * 
 * @param L 
 * 
 * @return 1
 *
 */
extern "C"
int luaopen_GXBitmapLib(lua_State* L)
{
	LuaBinder binder(L);
	binder.init(GXBITMAP_CLASSNAME, 0, WBitmapLib, WBitmap_Destory);

	return 1;
}
