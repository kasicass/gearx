
/*!
 * $Id$
 *
 * \brief	对于WBitmap的luabind，Lua中使用
 */

#ifndef _GX_BITMAP_H
#define _GX_BITMAP_H

#include "GXInc.h"

/*!
 * for register GXBitmap functions
 * 
 * we expose this functions:
 *		void Load(void* bmpdata);
 *		void Create(GXBitmap* parent, int x, int y, int w, int h);
 *		void Draw(WCanvas& canvas, int x, int y, int style);
 *
 * we can use this functions in Lua:
 *		Bitmap.Load()							-- load from resource to create a bitmap
 *		Bitmap.Create(parent, x, y, w, h)		-- create from a parent bitmap
 *		Bitmap.Draw(bmp, canvas, x, y, style)	-- draw the bitmap
 *		Bitmap.Destroy(bmp)						-- destory the bitmap object
 */
int luaopen_GXBitmapLib(lua_State* L);

#endif