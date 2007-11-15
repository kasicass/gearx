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

#include "GXTimer.h"

///////////////////////////////////////////////////////////////////////////////
/** 
 * 使用QueryPerformanceCount来计时
 * 
 */
class GXTimer
{
public:
	/** 
	 * 
	 * 
	 */
	void Start() {
		QueryPerformanceCounter(&_lasttime);
	}

	/** 
	 * 
	 * 
	 * 
	 * @return 
	 */
	DWORD Stop() {
		QueryPerformanceFrequency(&_frequency);
		QueryPerformanceCounter(&_current);
		double delta = ((double)(_current.QuadPart-_lasttime.QuadPart)) * 1000 
					/(double)_frequency.QuadPart;
		_lasttime = _current;
		return (DWORD)(delta);
	}

	/** 
	 * 
	 * 
	 * 
	 * @return 
	 */
	DWORD GetTime() {
		QueryPerformanceFrequency(&_frequency);
		QueryPerformanceCounter(&_current);
		double delta = ((double)(_current.QuadPart-_lasttime.QuadPart)) * 1000 
						/(double)_frequency.QuadPart;
		_lasttime = _current;
		return (DWORD)(delta);
	}

	/** 
	 * 
	 * 
	 */
	void Reset() {
		QueryPerformanceCounter(&_current);
		_lasttime = _current;
	}

private:
	LARGE_INTEGER			_lasttime; 		/**< last time  */
	LARGE_INTEGER			_current; 		/**< for storing current time */
	static LARGE_INTEGER	_frequency;		/**< current frequence of the CPU */
};

LARGE_INTEGER GXTimer::_frequency;

///////////////////////////////////////////////////////////////////////////////
static int GXTimer_Create(lua_State* L)
{
	LuaBinder binder(L);
	GXTimer* timer = new GXTimer;

	binder.pushusertype(timer, GXTIMER_CLASSNAME);

	return 1;
}

static int GXTimer_Destory(lua_State* L)
{
	LuaBinder binder(L);
	GXTimer* timer = (GXTimer*)(binder.checkusertype(1, GXTIMER_CLASSNAME));

	SAFEDELETE(timer);

	return 0;
}

static int GXTimer_Start(lua_State* L)
{
	LuaBinder binder(L);
	GXTimer* timer = (GXTimer*)(binder.checkusertype(1, GXTIMER_CLASSNAME));

	timer->Start();

	return 0;	
}

static int GXTimer_Stop(lua_State* L)
{
	LuaBinder binder(L);
	GXTimer* timer = (GXTimer*)(binder.checkusertype(1, GXTIMER_CLASSNAME));

	timer->Stop();

	return 0;
}

static int GXTimer_GetTime(lua_State* L)
{
	LuaBinder binder(L);
	GXTimer* timer = (GXTimer*)(binder.checkusertype(1, GXTIMER_CLASSNAME));
	int time = timer->GetTime();

	binder.pushnumber((double)(time));

	return 1;
}

static int GXTimer_Reset(lua_State* L)
{
	LuaBinder binder(L);
	GXTimer* timer = (GXTimer*)(binder.checkusertype(1, GXTIMER_CLASSNAME));

	timer->Reset();

	return 0;
}
/*
//////////////////////////////////////////////////////////////////////////
static int GXTimer_Create(lua_State* L)
{
	LuaBinder binder(L);
	WTimer* timer = new WTimer;

	binder.pushusertype(timer, GXTIMER_CLASSNAME);

	return 1;
}

static int GXTimer_Destory(lua_State* L)
{
	LuaBinder binder(L);
	WTimer* timer = (WTimer*)(binder.checkusertype(1, GXTIMER_CLASSNAME));

	SAFEDELETE(timer);

	return 0;
}

static int GXTimer_Start(lua_State* L)
{
	LuaBinder binder(L);
	WTimer* timer = (WTimer*)(binder.checkusertype(1, GXTIMER_CLASSNAME));

	timer->Start();
	return 0;
}

static int GXTimer_Stop(lua_State* L)
{
	LuaBinder binder(L);
	WTimer* timer = (WTimer*)(binder.checkusertype(1, GXTIMER_CLASSNAME));
	timer->Stop();

	return 0;
}

static int GXTimer_GetTime(lua_State* L)
{
	LuaBinder binder(L);
	WTimer* timer = (WTimer*)(binder.checkusertype(1, GXTIMER_CLASSNAME));
	int ret = timer->GetTime() / 10;
	binder.pushnumber((double)(ret));

	return 1;
}

static int GXTimer_Reset(lua_State* L)
{
	LuaBinder binder(L);
	WTimer* timer = (WTimer*)(binder.checkusertype(1, GXTIMER_CLASSNAME));
	timer->Reset();

	return 0;
}
*/

//////////////////////////////////////////////////////////////////////////
static const luaL_reg GXTimerLib[] = {
	{"Create",			GXTimer_Create},
	{"Start",			GXTimer_Start},
	{"Stop",			GXTimer_Stop},
	{"GetTime",			GXTimer_GetTime},
	{"Reset",			GXTimer_Reset},
	{NULL,				NULL}
};

//////////////////////////////////////////////////////////////////////////
int luaopen_GXTimer(lua_State* L)
{
	LuaBinder binder(L);
	binder.init(GXTIMER_CLASSNAME, 0, GXTimerLib, GXTimer_Destory);

	return 1;
}

