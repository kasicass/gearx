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
 * @file   socket.h
 * @author ChenZaichun <ChenZaichun@gmail.com>
 * @date   Sun Nov 18 20:13:50 2007
 * 
 * @brief  windows socket bind for Lua
 * 
 * 
 */

#ifndef _SOCKET_H
#define _SOCKET_H

#include "buffer.h"

#define SOCKET_LIBNAME  		"socket"
#define SOCKET_TYPE_NAME		"t_socket"
#define FDSET_TYPENAME			"fdset"

/** 
 * open socket lib 
 * 
 * @param L pointer to lua state
 * 
 * @return 1
 */
extern "C"
__declspec(dllexport) int luaopen_socket(lua_State* L);

/// socket
typedef struct t_socket_ {
	int socket;					/**< socket */
	t_buffer buf;				/**< buffer for control */
} t_socket;


#endif



