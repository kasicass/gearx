/*  emacs: -*- mode: c; coding: utf-8; -*-  */

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
 * @file   Binder.h
 * @author ChenZaichun <ChenZaichun@gmail.com>
 * @date   Sun Nov 25 17:35:51 2007
 * 
 * @brief  Extensible full binder
 *			Uses full userdata with extensiblity
 * 
 */

///////////////////////////////////////////////////////////////////////////////
#ifndef _BINDER_H
#define _BINDER_H

#include <assert.h>
#include "GXLua.hpp"

///////////////////////////////////////////////////////////////////////////////
int newindex (lua_State* L);
int index (lua_State* L);

///////////////////////////////////////////////////////////////////////////////

class LuaBinder
{
public:
	LuaBinder (lua_State* L)
		: L(L)
	{
	}

	void pushint(int n) {
		lua_pushinteger(L, n);
	}

	int checkint(int idx) {
		return luaL_checkint(L, idx);
	}
	
	void pushnumber (lua_Number n)
	{
		lua_pushnumber(L,n);
	}

	lua_Number checknumber (int index)
	{
		return luaL_checknumber(L,index);
	}

	void pushboolean(bool b) {
		lua_pushboolean(L, b);
	}

	bool checkboolean(int index) {
		if (lua_isboolean(L, index)) {
			return (lua_toboolean(L, index)) ? true : false;
		}

		assert(false);

		return false;
	}

	void pushstring (const char* s)
	{
		lua_pushstring(L,s); 
	}

	const char* checkstring (int index)
	{
		return luaL_checkstring(L,index);
	}
	
	void init (const char* tname,				// type name
			   const char* bname,				// base type name
			   const luaL_reg *flist,			// function list
			   int (*destroy)(lua_State*))		// Destory function
	{ 
		lua_newtable(L);				        // create table for uniqueness
		lua_pushstring(L, "v");
		lua_setfield(L, -2, "__mode");		    // set as weak-value table
		lua_pushvalue(L, -1);			        // duplicate table
		lua_setmetatable(L, -2);		        // set itself as metatable 
		lua_replace(L, LUA_ENVIRONINDEX);		// set table as env table
		luaL_register(L, tname, flist);			// create libtable
		lua_pushvalue(L, -1);		            // duplicate
		lua_setfield(L, LUA_ENVIRONINDEX, "__index");  // envtable.__index = libtable
		luaL_newmetatable(L, tname);		    // create udata metatable
		lua_pushcfunction(L, index);
		lua_setfield(L, -2, "__index");		    // mt.__index = index func
		lua_pushcfunction(L, newindex);
		lua_setfield(L, -2, "__newindex");		// mt.__newindex = newindex func
		lua_pushcfunction(L, destroy);	
		lua_setfield(L, -2, "__gc");		    // mt.__gc = destroy
		if (bname) {
			luaL_getmetatable(L,bname);
			lua_setfield(L,-2,"_base");			// mt._base = base mt
		}
		lua_pop(L, 1);							// pop metatable
		if (bname) {
			lua_getfield(L, LUA_GLOBALSINDEX, bname);
			lua_setfield(L, -2, "__index");		// libtable.__index = base libtable
			lua_pushvalue(L, -1);				// duplicate libtable
			lua_setmetatable(L, -2);			// set itself as metatable
		}
	}
	
	void pushusertype (void* udata, char* tname) 
	{
		lua_pushlightuserdata(L, udata);
		lua_rawget(L, LUA_ENVIRONINDEX);       // get udata in table
		if (lua_isnil(L, -1)) {
			void** ubox = (void**)lua_newuserdata(L, sizeof(void*));
			*ubox = udata;                     // store address in udata
			luaL_getmetatable(L, tname);	   // get metatable 
			lua_setmetatable(L, -2);	       // set metatable for udata
			lua_pushlightuserdata(L, udata);   // push address
			lua_pushvalue(L, -2);              // push udata
			lua_rawset(L, LUA_ENVIRONINDEX);   // envtable[address] = udata
		}
	} 

	void pushpointer(void* udata) {
		lua_pushlightuserdata(L, udata);
	}
	
	void* checkpointer(int idx) {
		return lua_touserdata(L, idx);
	}

	void *checkusertype (int index, const char *tname) 
	{
		lua_getfield(L, LUA_REGISTRYINDEX, tname);   /* get metatable of given type */
		lua_getmetatable(L, index);                  /* get associated metatable */
		while (lua_istable(L, -1)) {
			if (lua_rawequal(L, -1, -2)) {
				lua_pop(L, 2);
				return *((void**)lua_touserdata(L, index));
			}
			lua_getfield(L,-1, "_base");            // get mt._base
			lua_replace(L, -2);                     // replace: mt = mt._base
		}
		luaL_typerror(L, index, tname);
		return NULL;
	}
	
private:
	lua_State* L;
};

#endif

///////////////////////////////////////////////////////////////////////////////
// end of Binder.h

