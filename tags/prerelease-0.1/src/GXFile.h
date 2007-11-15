
/*!
 * $Id$
 *
 * \brief	����WFile��luabind��lua��ʹ��
 */

#ifndef _GX_FILE_H
#define _GX_FILE_H

#include "GXInc.h"

/*!
 * ע��File�������ɹ�ʹ�õ���:
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
 * Lua����:
 *		local f = File.OpenDataFile("data.wdf")
 *		File.Load(f, "mainmenu.bmp")
 *		local data = File.Data(f)
 *		Bitmap.Load(data)
 *		...				-- automatic release by _gc, so you don't need to call Close
 * 
 * ����Close֮�󣬶��󽫱�����
 */
int luaopen_GXFileLib(lua_State* L);

#endif