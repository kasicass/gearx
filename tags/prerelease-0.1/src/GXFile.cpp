
/*!
* $Id$
*
* \brief	对于WFile的luabind，lua中使用
*/

#include "GXFile.h"

static int GXFile_OpenDataFile(lua_State* L)
{
	LuaBinder binder(L);
	const char* pkgname = binder.checkstring(1);
	WFile::OpenDataFile(pkgname);

	WFile * file = new WFile;
	binder.pushusertype(file, GXFILE_CLASSNAME);

	return 1;
}

static int GXFile_Load(lua_State* L)
{
	LuaBinder binder(L);
	WFile* file = (WFile*)(binder.checkusertype(1, GXFILE_CLASSNAME));
	const char* filename = binder.checkstring(2);
	file->Load(filename);

	return 0;
}

static int GXFile_Data(lua_State* L)
{
//	LuaBinder binder(L);
//	WFile* file = (WFile*)(binder.checkusertype(1, GXFILE_CLASSNAME));
//	binder.pushpointer(file->GetPtr());

	return 0;
}

static int GXFile_Open(lua_State* L)
{
	LuaBinder binder(L);
	WFile* file = (WFile*)(binder.checkusertype(1, GXFILE_CLASSNAME));
	const char* filename = binder.checkstring(2);
	file->Open(filename);

	return 0;
}

static int GXFile_Read(lua_State* L)
{
	LuaBinder binder(L);
	WFile* file = (WFile*)(binder.checkusertype(1, GXFILE_CLASSNAME));
	void * buffer = binder.checkpointer(2);//binder.checkusertype(-2, GX_DATA_CLASSNAME);
	int size = binder.checkint(3);
	int read = 0;

	file->Read(buffer, size, &read);
	binder.pushnumber((double)(read));

	return 1;
}

static int GXFile_Skip(lua_State* L)
{
	LuaBinder binder(L);
	WFile* file = (WFile*)(binder.checkusertype(1, GXFILE_CLASSNAME));
	int size = binder.checkint(2);

	file->Skip(size);

	return 0;
}

static int GXFile_Size(lua_State* L)
{
	LuaBinder binder(L);
	WFile* file = (WFile*)(binder.checkusertype(1, GXFILE_CLASSNAME));
	binder.pushint(file->GetSize());

	return 1;
}

static int GXFile_Tell(lua_State* L)
{
	LuaBinder binder(L);
	WFile* file = (WFile*)(binder.checkusertype(2, GXFILE_CLASSNAME));
	binder.pushint(file->Tell());

	return 1;
}

static int GXFile_Close(lua_State* L)
{
	LuaBinder binder(L);
	WFile* file = (WFile*)(binder.checkusertype(1, GXFILE_CLASSNAME));
	file->Close();

	SAFEDELETE(file);

	return 0;
}

static int GXFile_IsEnd(lua_State* L)
{
	LuaBinder binder(L);
	WFile* file = (WFile*)(binder.checkusertype(1, GXFILE_CLASSNAME));

	bool end = file->IsEnd();
    binder.pushboolean(end);

	return 1;
}

static int GXFile_Destory(lua_State* L)
{
	LuaBinder binder(L);
	WFile* file = (WFile*)(binder.checkusertype(1, GXFILE_CLASSNAME));
	
	SAFEDELETE(file);

	return 0;
}

static const luaL_reg GXFileLib[] = {
	{"OpenDataFile",	GXFile_OpenDataFile},
//	{"Destroy",			GXBitmap_Destory},
	{"Load",			GXFile_Load},
//	{"Data",			GXFile_Data},
	{"Open",			GXFile_Open},
//	{"Read",			GXFile_Read},
	{"Skip",			GXFile_Skip},
	{"Size",			GXFile_Size},
	{"Tell",			GXFile_Tell},
	{"Close",			GXFile_Close},
	{"IsEnd",			GXFile_IsEnd},
	{NULL,				NULL},
};

int luaopen_GXFileLib(lua_State* L)
{
	LuaBinder binder(L);
	binder.init(GXFILE_CLASSNAME, 0, GXFileLib, GXFile_Destory);

	return 1;
}
