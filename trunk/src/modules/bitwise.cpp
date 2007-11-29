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

    $Id: $
    ChenZaichun@gmail.com
*/

/**
 * @file   bitwise.cpp
 * @author ChenZaichun <ChenZaichun@gmail.com>
 * @date   Thu Nov 15 10:20:29 2007
 * 
 * @brief  bitwise operation to export for Lua
 * 
 * 
 */

#include "../binder.h"

///////////////////////////////////////////////////////////////////////////////
/** 
 * arithemtic not operation 
 * 
 * @param L pointer to lua state 
 * 
 * @return 
 */
static int int_bnot(lua_State* L)
{
	LuaBinder binder(L);
	int op1 = (int)(binder.checknumber(1));
	binder.pushnumber((lua_Number)(~op1));
	
	return 1;
}

static int int_band(lua_State* L)
{
	LuaBinder binder(L);
	int op1 = (int)(binder.checknumber(1));
	int op2 = (int)(binder.checknumber(2));

	binder.pushnumber((lua_Number)(op1 & op2));

	return 1;
}

static int int_bor(lua_State* L)
{
	LuaBinder binder(L);
	
	int op1 = (int)(binder.checknumber(1));
	int op2 = (int)(binder.checknumber(2));

	binder.pushnumber((lua_Number)(op1 | op2));

	return 1;
}

static int int_bxor(lua_State* L)
{
	LuaBinder binder(L);
	
	int op1 = (int)(binder.checknumber(1));
	int op2 = (int)(binder.checknumber(2));

	binder.pushnumber((lua_Number)(op1 ^ op2));

	return 1;
}

static int int_lshift(lua_State* L)
{
	LuaBinder binder(L);
	
	int op1 = (int)(binder.checknumber(1));
	int op2 = (int)(binder.checknumber(2));

	binder.pushnumber((lua_Number)(op1 << op2));

	return 1;
}

static int int_rshift(lua_State* L)
{
	LuaBinder binder(L);
	
	int op1 = (int)(binder.checknumber(1));
	int op2 = (int)(binder.checknumber(2));

	binder.pushnumber((lua_Number)(op1 >> op2));

	return 1;
}

static int int_mod(lua_State* L)
{
	LuaBinder binder(L);
	
	int op1 = (int)(binder.checknumber(1));
	int op2 = (int)(binder.checknumber(2));

	binder.pushnumber((lua_Number)(op1 %op2));

	return 1;
}

static int int_lowword(lua_State* L)
{
	LuaBinder binder(L);
	int op = (int)(binder.checknumber(1));

	binder.pushnumber((lua_Number)(op & 0x0000ffff));

	return 1;
}

static int int_hiword(lua_State* L)
{
	LuaBinder binder(L);
	int op = (int)(binder.checknumber(1));

	binder.pushnumber((lua_Number)(op >> 16));

	return 1;
}	

///////////////////////////////////////////////////////////////////////////////
static const struct luaL_reg bitlib[] = {
	{"bnot", 		int_bnot},
	{"band", 		int_band},
	{"bor",			int_bor},
	{"lshift",		int_lshift},
	{"rshift",		int_rshift},
	{"mod",			int_mod},
	{"loword",		int_lowword},
	{"hiword",		int_hiword},
	{NULL,			NULL},
};

///////////////////////////////////////////////////////////////////////////////
/**
 * export function, for lua loading lib
 * 
 * @param L pointer to lua state
 * 
 * @return 1
 */
int __stdcall luaopen_bit(lua_State* L)
{
	LuaBinder binder(L);
	binder.init("bit", 0, bitlib, 0);

	return 1;
}

