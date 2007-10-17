
/*!
 * $Id$
 *
 * \brief	Lua header files for C++
 *			<<extern "C">> not supplied automatically because Lua 
 *			also compiles as C++
 */

#ifndef _GX_LUA_HPP
#define _GX_LUA_HPP

#ifdef __cplusplus
extern "C" {
#endif
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib, "lua51.lib")

//void error(lua_State* L, const char* fmt, ...)
//{
//	va_list argp;
//	va_start(argp, fmt);
//	vfprintf(stderr, fmt, argp);
//	va_end(argp);
//	lua_close(L);
//	exit(EXIT_FAILURE);
//}

#endif