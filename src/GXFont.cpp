
/*!
 * \file	GXFont.cpp
 * \brief	WFont lua bind
 *
 * $Id: $
 *
 * CopyRight (c) GearX Team, 2007
 * See LISENCE for more information
 */

#include "GXFont.h"

// for storing font information
typedef struct GXFontData
{
	WFont*	wfont;
	HFONT	hfont;
} GXFontData, *PGXFontData;

typedef struct FontList {
	GXFontData data;
	FontList* next;
} FontList, *PFontList;

FontList * plist = NULL;

//////////////////////////////////////////////////////////////////////////
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

/*
static int GXFont_SetAlpha(lua_State* L)
{
	LuaBinder binder(L);
	WFont* font = (WFont*)(binder.checkusertype(1, GXFONT_CLASSNAME));
	int alpha = (int)(binder.checknumber(2));

	font->SetUserData(alpha);
	return 0;
}
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
static const luaL_reg GXFontLib[] = {
	{"Create",			GXFont_Create},
//	{"SetAlpha",		GXFont_SetAlpha},
	{"Draw",			GXFont_Draw},
	{NULL,				NULL},
};

//////////////////////////////////////////////////////////////////////////
int luaopen_FontLib(lua_State* L)
{
	LuaBinder binder(L);
	binder.init(GXFONT_CLASSNAME, 0, GXFontLib, GXFont_Destroy);

	return 1;
}

