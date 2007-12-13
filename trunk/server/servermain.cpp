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

///////////////////////////////////////////////////////////////////////////////
#include "GXLua.hpp"

#define MAIN_SCRIPT "server.lua"

int main()
{
	lua_State* L;
	L = lua_open();
	if (L == NULL) {
		printf("cannot create lua state\n");
		return 1;
	}
	luaL_openlibs(L);

	if (luaL_loadfile(L, MAIN_SCRIPT)) {
		printf("%s", lua_tostring(L, -1));
		return 1;
	}
	if (lua_pcall(L, 0, 0, 0)) {
		printf("%s", lua_tostring(L, -1));
		return 1;
	}

	lua_close(L);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// end of servermain.cpp
