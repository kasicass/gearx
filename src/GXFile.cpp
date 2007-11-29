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

    $Id$
    ChenZaichun@gmail.com
*/

/**
 * @file   GXFile.h
 * @author ChenZaichun <ChenZaichun@gmail.com>
 * @date   Sun Nov 25 17:28:30 2007
 * 
 * @brief  WFile for lua
 * 
 * 
 */

///////////////////////////////////////////////////////////////////////////////
#include "GXFile.h"

///////////////////////////////////////////////////////////////////////////////
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
	void * buffer = binder.checkpointer(2);
	int size = binder.checkint(3);
	int read = 0;

	file->Read(buffer, size, &read);
	binder.pushnumber((lua_Number)(read));

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

///////////////////////////////////////////////////////////////////////////////
static const luaL_reg GXFileLib[] = {
	{"OpenDataFile",	GXFile_OpenDataFile},
	{"Load",			GXFile_Load},
	{"Open",			GXFile_Open},
//	{"Read",			GXFile_Read},
	{"Skip",			GXFile_Skip},
	{"Size",			GXFile_Size},
	{"Tell",			GXFile_Tell},
	{"Close",			GXFile_Close},
	{"IsEnd",			GXFile_IsEnd},
	{NULL,				NULL},
};

///////////////////////////////////////////////////////////////////////////////
extern "C"
int luaopen_GXFileLib(lua_State* L)
{
	LuaBinder binder(L);
	binder.init(GXFILE_CLASSNAME, 0, GXFileLib, GXFile_Destory);

	return 1;
}
