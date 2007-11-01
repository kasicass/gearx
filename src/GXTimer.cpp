
/*!
* $Id$
*
* \brief	WTimer Lua bind
*/

#include "GXTimer.h"

//////////////////////////////////////////////////////////////////////////
/*
class GXTimer
{
public:
	GXTimer();
	
	void Start() {
		QueryPerformanceCounter(&_lasttime);
	}
	
	DWORD Stop() {
		QueryPerformanceFrequency(&_frequency);
		QueryPerformanceCounter(&_current);
		int delta = (_current.LowPart - _lasttime.LowPart) * (int)_frequency;
		_lasttime = _current;
		return delta;
	}
	DWORD GetTime() {
		QueryPerformanceFrequency(&_frequency);
		QueryPerformanceCounter(&_current);
		int delta = (_current.LowPart - _lasttime.LowPart)*_frequency;
		_lasttime = _current;
		return delta;
	}

	void Reset() {
		QueryPerformanceCounter(&_current);
		_lasttime = _current;
	}

private:
	LARGE_INTEGER			_lasttime;					/// last time info	
	LARGE_INTEGER			_current;
	static LARGE_INTEGER	_frequency;					/// current frequence of the CPU
};
*/
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

