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

    $Id: $
    ChenZaichun@gmail.com
*/

/**
 * @file   GXFont.cpp
 * @author ChenZaichun <ChenZaichun@gmail.com>
 * @date   Mon Nov 26 15:42:32 2007
 * 
 * @brief  WFont Lua bind
 * 
 */

#include "GXFont.h"

///////////////////////////////////////////////////////////////////////////////
/// storing WFont pointer and HFONT,
/// for release memory
typedef struct GXFontData
{
	WFont*	wfont;
	HFONT	hfont;
} GXFontData, *PGXFontData;

///////////////////////////////////////////////////////////////////////////////
/// list struct for storing font info
typedef struct FontList {
	GXFontData data;
	FontList* next;
} FontList, *PFontList;

FontList * plist = NULL;

///////////////////////////////////////////////////////////////////////////////
/** 
 * 
 * 
 * @param L 
 * 
 * @return 
 */
static int GXFont_Create(lua_State* L)
{
	LuaBinder binder(L);
	const char* fontname = binder.checkstring(1);
	int width = (int)(binder.checknumber(2));

	HFONT hfont = CreateFont(
		width,0,
		0, 0, 
		FW_BOLD, 
		FALSE, FALSE, FALSE, 
		DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_QUALITY, 
//		DEFAULT_PITCH | FF_DONTCARE, 
		fontname);

	WFont* font = new WFont();
	font->Create(hfont);

	FontList * pfont = new FontList;
	pfont->data.wfont = font;
	pfont->data.hfont = hfont;
	pfont->next = NULL;
	if (!plist) {
		plist = pfont;
	} else {
		FontList* p = plist;
		while (p) {
			p = p->next;
		}

		p = pfont;
	}

	binder.pushusertype(font, GXFONT_CLASSNAME);

	return 1;
}

/** 
 * 
 * 
 * @param L 
 * 
 * @return 
 */
static int GXFont_Destroy(lua_State* L)
{
	LuaBinder binder(L);
	WFont* font = (WFont*)(binder.checkusertype(1, GXFONT_CLASSNAME));

	if (plist->data.wfont == font) {
		SAFEDELETE(plist);
	} else {
		FontList * p = plist;
		while (p) {
			if (p->next->data.wfont == font) {
				FontList* q = p->next->next;
				DeleteObject(p->next->data.hfont);
				p->next->data.hfont = NULL;
				SAFEDELETE(p->next);
				p->next = q;
				break;
			}

			p++;
		}

		SAFEDELETE(font);
	}

	return 0;
}

/** 
 * 
 * 
 * @param L 
 * 
 * @return 
 */
static int GXFont_Draw(lua_State* L)
{
	LuaBinder binder(L);
	WFont* font = (WFont*)(binder.checkusertype(1, GXFONT_CLASSNAME));
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(2, GXCANVAS_CLASSNAME));
	const char* str = binder.checkstring(3);
	int color = (int)(binder.checknumber(4));
	int x = (int)(binder.checknumber(5));
	int y = (int)(binder.checknumber(6));

	canvas->ViewPort(x, y);
	font->Draw(*canvas, str, color);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
/// 
static const luaL_reg GXFontLib[] = {
	{"Create",			GXFont_Create},
	{"Draw",			GXFont_Draw},
	{NULL,				NULL},
};

//////////////////////////////////////////////////////////////////////////
/** 
 * 
 * 
 * @param L 
 * 
 * @return 
 */
extern "C"
int luaopen_FontLib(lua_State* L)
{
	LuaBinder binder(L);
	binder.init(GXFONT_CLASSNAME, 0, GXFontLib, GXFont_Destroy);

	return 1;
}

///////////////////////////////////////////////////////////////////////////////
// end of GXFont.cpp

