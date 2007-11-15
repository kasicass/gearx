
/*!
* $Id$
*
* \brief	WSurface LuaBind
*/

#include "GXSurface.h"

//////////////////////////////////////////////////////////////////////////
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

static int GXSurface_Blit2Screen(lua_State* L)
{
	LuaBinder binder(L);

	WSurface* surface = (WSurface*)(binder.checkusertype(1, GXSURFACE_CLASSNAME));

	surface->Blit2Screen();

	return 0;
}

static int GXSurface_Destroy(lua_State* L)
{
	LuaBinder binder(L);

	WSurface* surface = (WSurface*)(binder.checkusertype(1, GXSURFACE_CLASSNAME));

	SAFEDELETE(surface);
    
	return 0;
}

//////////////////////////////////////////////////////////////////////////
static const luaL_reg GXSurfaceLib[] = {
	{"Create",		GXSurface_Create},
	{"Blit2Screen", GXSurface_Blit2Screen},
	{NULL,			NULL},
};

//////////////////////////////////////////////////////////////////////////
int luaopen_GXSurfaceLib(lua_State* L)
{
	LuaBinder binder(L);
	binder.init(GXSURFACE_CLASSNAME, 0, GXSurfaceLib, GXSurface_Destroy);

	return 1;
}