/*  emacs: -*- mode: cc; coding: gb2312 -*- TAB SIZE: 4 -*-  */

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
 * @file   GXMusic.cpp
 * @author ChenZaichun
 * @date   Mon Nov 12 16:35:13 2007
 * 
 * @brief  fmod lua bind
 * 
 * 		   封装了读取wdf包内声音文件，并暴露接口使之能够在Lua中使用
 */


#include "GXMusic.h"
#include "fmod.h"

//////////////////////////////////////////////////////////////////////////
// prototypes
void* F_CALLBACKAPI MusicOpen(const char *name);
void  F_CALLBACKAPI MusicClose(void *handle);
int	  F_CALLBACKAPI MusicRead(void *buffer, int size, void *handle);
int   F_CALLBACKAPI MusicSeek(void *handle, int pos, signed char mode);
int   F_CALLBACKAPI MusicTell(void *handle);

//////////////////////////////////////////////////////////////////////////
/** 
 * wrapper of fopen for reading wdf package 
 * 
 * @param name file name
 * 
 * @return file handle
 */
void* F_CALLBACKAPI MusicOpen(const char *name)
{
	int id = WString2ID(name);
	WFile * file = new WFile;
	file->Open(name);
	return (void*)(file);
}

/** 
 * 
 * 
 * @param handle 
 * 
 * @return 
 */
void  F_CALLBACKAPI MusicClose(void *handle)
{
	WFile* file = (WFile*)handle;
	SAFEDELETE(file);
}

int	  F_CALLBACKAPI MusicRead(void *buffer, int size, void *handle)
{
	int read = 0;
	((WFile*)handle)->Read(buffer, size, &read);

	return read;
}

int   F_CALLBACKAPI MusicSeek(void *handle, int pos, signed char mode)
{
	int cur = MusicTell(handle);
	WFile* f = ((WFile*)handle);

	switch (mode) {
	case SEEK_SET:
		f->Skip(pos-cur);
		break;

	case SEEK_END:
		f->Skip(f->GetSize()-pos-cur);
		break;

	case SEEK_CUR:
		f->Skip(pos);
		break;
	}

	return 0;
}

int   F_CALLBACKAPI MusicTell(void *handle)
{
	return ((WFile*)handle)->Tell();
}

//////////////////////////////////////////////////////////////////////////
static int GXMusic_Init(lua_State* L)
{
	if (FSOUND_GetVersion() < FMOD_VERSION)	{ 
//		FSOUND_Close(); 
		return false; 
	}

//	FSOUND_SetOutput(FSOUND_OUTPUT_DSOUND);
//	FSOUND_SetDriver(FSOUND_OUTPUT_DSOUND);

	FSOUND_File_SetCallbacks(MusicOpen, MusicClose, MusicRead, MusicSeek, MusicTell);

	if (!FSOUND_SetMemorySystem(malloc(4*1024*1024), 4*1024*1024, NULL, NULL, NULL)) {
		return false;
	}

	FSOUND_SetMixer(FSOUND_MIXER_QUALITY_AUTODETECT);
	if (!FSOUND_Init (44100, 32, FSOUND_INIT_USEDEFAULTMIDISYNTH)) {
		FSOUND_Close();
		return false;
	}

	return true;
}

static int GXMusic_Shutdown(lua_State* L)
{
	FSOUND_Close();

	return 0;
}

static int GXMusic_Load(lua_State* L)
{
	LuaBinder binder(L);
	const char* pkgname = binder.checkstring(1);
	const char* filename = binder.checkstring(2);
	int type = (int)(binder.checknumber(3));

	WFile::OpenDataFile(pkgname);

	void * ret = NULL;
	switch (type) {
		case 1:
			ret = (void*)(FSOUND_Stream_Open(filename, 0, 0, 0));
			FSOUND_Stream_SetMode((FSOUND_STREAM*)ret, FSOUND_LOOP_NORMAL);
			break;

		case 2:
			ret = (void*)(FSOUND_Sample_Load(0, filename, 0, 0, 0));
			FSOUND_Sample_SetMode((FSOUND_SAMPLE*)ret, FSOUND_LOOP_OFF);
			break;
	}
	
	binder.pushusertype(ret, GXMUSIC_CLASSNAME);
	return 1;
}

static int GXMusic_UnLoad(lua_State* L)
{
	LuaBinder binder(L);
	void * ret = binder.checkusertype(1, GXMUSIC_CLASSNAME);
	int type = (int)(binder.checknumber(2));
	switch (type) {
		case 1:
			FSOUND_Stream_Close((FSOUND_STREAM*)ret);
			break;
		case 2:
			FSOUND_Sample_Free((FSOUND_SAMPLE*)ret);
			break;
	}

	return 0;
}

static int GXMusic_Play(lua_State* L)
{
	LuaBinder binder(L);
	void * ret = binder.checkusertype(1, GXMUSIC_CLASSNAME);
	int type = (int)(binder.checknumber(2));

	switch (type) {
		case 1:
			FSOUND_Stream_Play(1, (FSOUND_STREAM*)ret);
			break;
		case 2:
			FSOUND_PlaySound(2, (FSOUND_SAMPLE*)ret);
			break;
	}

	return 0;
}

static int GXMusic_Stop(lua_State *L)
{
	LuaBinder binder(L);
	void * ret = binder.checkusertype(1, GXMUSIC_CLASSNAME);
	FSOUND_Stream_Stop((FSOUND_STREAM*)ret);

	return 0;
}


//////////////////////////////////////////////////////////////////////////
static const luaL_reg GXMusicLib[] = {
	{"Init",		GXMusic_Init},
	{"Shutdown",	GXMusic_Shutdown},
	{"Load",		GXMusic_Load},
	{"UnLoad",		GXMusic_UnLoad},
	{"Play",		GXMusic_Play},
	{"Stop",		GXMusic_Stop},
	{NULL,			NULL}
};


//////////////////////////////////////////////////////////////////////////
int luaopen_GXMusicLib(lua_State* L)
{
	LuaBinder binder(L);
	binder.init(GXMUSIC_CLASSNAME, 0, GXMusicLib, GXMusic_Shutdown);

	return 1;
}

