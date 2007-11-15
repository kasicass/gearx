
/*!
 * $Id$
 *
 * \brief	对于WBitmap的luabind，Lua中使用
 */

#include "GXBitmap.h"

//////////////////////////////////////////////////////////////////////////
static int WBitmap_Load(lua_State* L)
{
	LuaBinder binder(L);
	const char* pkgname = binder.checkstring(1);
	const char* filename = binder.checkstring(2);
	WFile f;
	WFile::OpenDataFile(pkgname);
	f.Load(filename);
	WBitmap* bmp = new WBitmap;
	bmp->Load(f);

	binder.pushusertype(bmp, GXBITMAP_CLASSNAME);

	return 1;
}

static int WBitmap_Destory(lua_State* L)
{
	LuaBinder binder(L);
	WBitmap* bmp = (WBitmap*)(binder.checkusertype(1, GXBITMAP_CLASSNAME));
	SAFEDELETE(bmp);

	return 0;
}

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

static int WBitmap_GetW(lua_State* L)
{
	LuaBinder binder(L);
	WBitmap* bmp = (WBitmap*)(binder.checkusertype(1, GXBITMAP_CLASSNAME));

	binder.pushnumber((double)(bmp->GetW()));

	return 1;
}

static int WBitmap_GetH(lua_State* L)
{
	LuaBinder binder(L);
	WBitmap* bmp = (WBitmap*)(binder.checkusertype(1, GXBITMAP_CLASSNAME));

	binder.pushnumber((double)(bmp->GetH()));

	return 1;
}

static int WBitmap_IsCover(lua_State* L)
{
	LuaBinder binder(L);
	WBitmap* bmp = (WBitmap*)(binder.checkusertype(1, GXBITMAP_CLASSNAME));
	int x = (int)(binder.checknumber(2));
	int y = (int)(binder.checknumber(3));

	int ret = bmp->IsCover(WPoint(x, y));
	binder.pushnumber(ret);

	return 1;
}

static int WBitmap_SetData(lua_State * L)
{
	LuaBinder binder(L);
	WBitmap* bmp = (WBitmap*)(binder.checkusertype(1, GXBITMAP_CLASSNAME));
	int data = (int)(binder.checknumber(2));

	bmp->SetUserData(data);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
static const luaL_reg WBitmapLib[] = {
	{"Load",		WBitmap_Load},
//	{"Destroy",		WBitmap_Destory},
	{"Create",		WBitmap_Create},
	{"Draw",		WBitmap_Draw},
	{"W",			WBitmap_GetW},
	{"H",			WBitmap_GetH},
	{"IsCover",		WBitmap_IsCover},
	{"SetData",		WBitmap_SetData},
	{"CreateEmpty",	WBitmap_CreateEmpty},
	{NULL,			NULL},
};

int luaopen_GXBitmapLib(lua_State* L)
{
	LuaBinder binder(L);
	binder.init(GXBITMAP_CLASSNAME, 0, WBitmapLib, WBitmap_Destory);

	return 1;
}