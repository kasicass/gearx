
/*!
 * $Id$
 * 
 * \brief	Extensible full binder
 *			Uses full userdata with extensibility
 */

#include "Binder.h"

int newindex (lua_State* L)
{
	lua_getfenv(L, 1);                       // get env table
	if (lua_equal(L, -1, LUA_ENVIRONINDEX)) {  
		lua_newtable(L);                     // create new table
		lua_pushvalue(L, -1);                // duplicate it
		lua_setfenv(L, 1);                   // set as env table to udata
		lua_pushvalue(L, -1);                // duplicate env table
		lua_setmetatable(L, -2);             // set itself as metatable
		lua_getfield(L, LUA_ENVIRONINDEX, "__index"); // get libtable
		lua_setfield(L, -2, "__index");      // envtable.__index = libtable
	}
	lua_pushvalue(L, 2);
	lua_pushvalue(L, 3);
	lua_rawset(L, -3);                       // store key in env table
	return 0;
}

int index (lua_State* L)
{
     lua_getfenv(L, 1);
     lua_pushvalue(L, 2);
     lua_gettable(L, -2);                    // access env table
     return 1;
}