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

#include "GXFile.h"
#include "GXBitmap.h"
#include "GXCanvas.h"
#include "GXSurface.h"
#include "GXMusic.h"
#include "GXTimer.h"
#include "GXFont.h"

extern
int __stdcall luaopen_bit(lua_State* L);

extern "C"
__declspec(dllexport) int luaopen_gxbase(lua_State* L)
{
	luaopen_GXFileLib(L);
	luaopen_GXBitmapLib(L);
	luaopen_GXCanvasLib(L);
	luaopen_GXSurfaceLib(L);
	luaopen_GXMusicLib(L);
	luaopen_GXTimer(L);
	luaopen_FontLib(L);
	luaopen_bit(L);

	return 0;
}
