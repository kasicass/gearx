
/*!
 * $Id$
 *
 * \brief	WCanvas Lua bind
 */

#include "GXCanvas.h"

//////////////////////////////////////////////////////////////////////////
static int GXCanvas_Create(lua_State* L)
{
	LuaBinder binder(L);
	int w = (int)(binder.checknumber(1));
	int h = (int)(binder.checknumber(2));
	WCanvas* canvas = new WCanvas(w, h);

	binder.pushusertype(canvas, GXCANVAS_CLASSNAME);

	return 1;
}

static int GXCanvas_Destory(lua_State* L)
{
	LuaBinder binder(L);
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(1, GXCANVAS_CLASSNAME));

	SAFEDELETE(canvas);

	return 0;
}

static int GXCanvas_ViewPort(lua_State* L)
{
	LuaBinder binder(L);
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(1, GXCANVAS_CLASSNAME));
	int x = (int)(binder.checknumber(2));
	int y = (int)(binder.checknumber(3));

	canvas->ViewPort(x, y);

	return 0;
}

static int GXCanvas_MoveTo(lua_State* L)
{
	LuaBinder binder(L);
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(1, GXCANVAS_CLASSNAME));
	int x = (int)(binder.checknumber(2));
	int y = (int)(binder.checknumber(3));

	canvas->MoveTo(x, y);

	return 0;
}

static int GXCanvas_Move(lua_State* L)
{
	LuaBinder binder(L);
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(1, GXCANVAS_CLASSNAME));
	int x = (int)(binder.checknumber(2));
	int y = (int)(binder.checknumber(3));

	canvas->Move(x, y);

	return 0;
}

static int GXCanvas_GetX(lua_State* L)
{
	LuaBinder binder(L);
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(1, GXCANVAS_CLASSNAME));
	binder.pushnumber((double)(canvas->GetX()));

	return 1;
}

static int GXCanvas_GetY(lua_State* L)
{
	LuaBinder binder(L);
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(1, GXCANVAS_CLASSNAME));
	binder.pushnumber((double)(canvas->GetY()));

	return 1;
}

static int GXCanvas_GetW(lua_State* L)
{
	LuaBinder binder(L);
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(1, GXCANVAS_CLASSNAME));
	binder.pushnumber((double)(canvas->GetW()));

	return 1;
}

static int GXCanvas_GetH(lua_State* L)
{
	LuaBinder binder(L);
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(1, GXCANVAS_CLASSNAME));
	binder.pushnumber((double)(canvas->GetH()));

	return 1;
}

static int GXCanvas_GetViewPort(lua_State* L)
{
	LuaBinder binder(L);
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(1, GXCANVAS_CLASSNAME));
	int x = (int)(binder.checknumber(2));
	int y = (int)(binder.checknumber(3));

	WPoint pt = canvas->GetViewPort(x, y);
	binder.pushnumber((double)(pt.x));
	binder.pushnumber((double)(pt.y));

	return 2;
}

static int GXCanvas_Clear(lua_State* L)
{
	LuaBinder binder(L);
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(1, GXCANVAS_CLASSNAME));
	int color = (int)(binder.checknumber(2));

	canvas->Clear(color);

	return 0;
}

static int GXCanvas_Draw(lua_State* L)
{
	LuaBinder binder(L);
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(1, GXCANVAS_CLASSNAME));
	WObject* obj = (WObject*)(binder.checkusertype(2, GXOBJECT_CLASNAME));
	int style = (int)(binder.checknumber(3));
	
	canvas->Draw(*obj, style);

	return 0;
}

static int GXCanvas_UnChange(lua_State* L)
{
	LuaBinder binder(L);
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(1, GXCANVAS_CLASSNAME));
	canvas->UnChange();

	return 0;
}

static int GXCanvas_Change(lua_State* L)
{
	LuaBinder binder(L);
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(1, GXCANVAS_CLASSNAME));
	canvas->Change();

	return 0;
}

static int GXCanvas_Reset(lua_State* L)
{
	LuaBinder binder(L);
	WCanvas* canvas = (WCanvas*)(binder.checkusertype(1, GXCANVAS_CLASSNAME));
	int time = (int)(binder.checknumber(2));
	canvas->Reset(time);

	return 0;
}

static int GXCanvas_Msg(lua_State* L)
{
	LuaBinder binder(L);
	const char* msg = binder.checkstring(1);

	MessageBox(NULL, msg, msg, MB_OK);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
static const luaL_reg GXCanvasLib[] = {
	{"Create",		GXCanvas_Create},
	{"ViewPort",	GXCanvas_ViewPort},
	{"MoveTo",		GXCanvas_MoveTo},
	{"Move",		GXCanvas_Move},
	{"X",			GXCanvas_GetX},
	{"Y",			GXCanvas_GetY},
	{"W",			GXCanvas_GetW},
	{"H",			GXCanvas_GetH},
	{"GetViewPort",	GXCanvas_GetViewPort},
	{"Clear",		GXCanvas_Clear},
	{"Draw",		GXCanvas_Draw},
	{"UnChange",	GXCanvas_UnChange},
	{"Change",		GXCanvas_Change},
	{"Reset",		GXCanvas_Reset},
	{"Msg",			GXCanvas_Msg},
	{NULL,			NULL},
};

//////////////////////////////////////////////////////////////////////////
int luaopen_GXCanvasLib(lua_State* L)
{
	LuaBinder binder(L);
	binder.init(GXCANVAS_CLASSNAME, 0, GXCanvasLib, GXCanvas_Destory);

	return 1;
}

//////////////////////////////////////////////////////////////////////////
