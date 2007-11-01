
/*!
 * $Id$
 *
 * \brief	对于WFile的luabind，lua中使用
 */

#ifndef _GX_FILE_H
#define _GX_FILE_H

#include "GXInc.h"

/*!
 * 注册File函数，可供使用的有:
 *
 *		OpenDataFile(const char* packagename)	/// open wdf package
 *		Load(const char *filename)				/// read the whole file to memory
 *		Open(const char *filename)				/// open a file
 *		Read(void *buffer,int s)				/// read file, the file pointer is current postion
 *		Skip(int s)								/// skip 
 *		Data()									/// get the data
 *		Size()
 *		Tell()
 *		Close()									/// close the file for read
 *		IsEnd()	
 *
 * Lua代码:
 *		local f = File.OpenDataFile("data.wdf")
 *		File.Load(f, "mainmenu.bmp")
 *		local data = File.Data(f)
 *		Bitmap.Load(data)
 *		...				-- automatic release by _gc, so you don't need to call Close
 * 
 * 调用Close之后，对象将被销毁
 */
int luaopen_GXFileLib(lua_State* L);

#endif