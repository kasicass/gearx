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
 * @file   socket.cpp
 * @author ChenZaichun <ChenZaichun@gmail.com>
 * @date   Sun Nov 18 20:15:57 2007
 * 
 * @brief  windows socket bind for Lua
 * 
 * 
 */

#include <winsock2.h>
#include "GXUtils.h"
#include "binder.h"
#include "socket.h"

#pragma comment(lib, "ws2_32.lib")

/** 
 * init windows socket lib
 * 
 * @param L 
 * 
 * @return 0
 */
static int socket_init(lua_State* L)
{
	WSADATA		wsa_data;

	if (WSAStartup(MAKEWORD(2, 0), &wsa_data))  {
		printf("init winsocket lib failed: %d\n", WSAGetLastError());
	}

	return 0;
}

/** 
 * clean up windows socket lib
 * 
 * @param L 
 * 
 * @return 0
 */
static int socket_shutdown(lua_State* L)
{
	WSACleanup();

	return 0;
}

/** 
 * craete a socket
 * 
 * @param L pointer to lua state
 *
 * @note we only use tcp/ip family
 * 
 * @return created socket
 */
static int socket_create(lua_State* L)
{
	LuaBinder binder(L);
	SOCKET s;

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	binder.pushnumber((lua_Number)(s));

	return 1;
}

/** 
 * 
 * 
 * @param L 
 * 
 * @return 
 */
static int socket_close(lua_State* L)
{
	LuaBinder binder(L);
	SOCKET s = (SOCKET)(binder.checknumber(1));
	closesocket(s);

	return 0;
}

static int socket_bind(lua_State* L)
{
	LuaBinder binder(L);

	// check for parameters
	int n = lua_gettop(L);
	assert(n == 2 || n == 3);
	
	SOCKET s = (SOCKET)(binder.checknumber(1));
	int port = (int)(binder.checknumber(2));

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (n == 3) {
		// applyed for connecting address
		const char* paddr = binder.checkstring(3);
		addr.sin_addr.s_addr = inet_addr(paddr);
	} else {
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
#if defined DEBUG || defined _DEBUG
		printf("bind in port: %d, any\n", port);
#endif
	}

	if (bind(s, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN))) {
		printf("bind server socket to port: %d failed, err: %d\n",
			   port, WSAGetLastError());
	}

	return 0;
}

static int socket_listen(lua_State* L)
{
	LuaBinder binder(L);
	SOCKET s= (SOCKET)(binder.checknumber(1));
	listen(s, 5);

	return 0;
}

static int socket_accept(lua_State* L)
{
	LuaBinder binder(L);
	SOCKET s = (SOCKET)(binder.checknumber(1));
	t_socket* pts = (t_socket*)(binder.checkusertype(2, SOCKET_TYPE_NAME));

	SOCKADDR_IN addr;
	int size = sizeof(SOCKADDR_IN);
	pts->socket = (int)accept(s, (SOCKADDR*)(&addr), &size);
	
//	binder.pushusertype(pts, SOCKET_TYPE_NAME);

	return 0;
}

static int socket_connect(lua_State* L)
{
	LuaBinder binder(L);
	int n = lua_gettop(L);
	t_socket* pts = (t_socket*)(binder.checkusertype(1, SOCKET_TYPE_NAME));
	int port = (int)(binder.checknumber(2));
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (n == 2) {
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	} else {
		addr.sin_addr.s_addr = inet_addr(binder.checkstring(3));
#if defined _DEBUG || defined DEBUG
		printf("connect to : %s:%d\n", binder.checkstring(3), port);
#endif
	}
	if (connect(pts->socket, (SOCKADDR*)(&addr), sizeof(SOCKADDR_IN))) {
		printf("connect to server failed, err: %d\n", WSAGetLastError());
	}
	
	return 0;
}

static int socket_send(lua_State* L)
{
	LuaBinder binder(L);
	t_socket* pts = (t_socket*)(binder.checkusertype(1, SOCKET_TYPE_NAME));

	int ret = send(pts->socket, pts->buf.sendbuf, (int)(pts->buf.sent)+1, 0);
	pts->buf.sent -= ret;

	binder.pushnumber((lua_Number)(ret));
	return 1;
}

static int socket_recv(lua_State* L)
{
	LuaBinder binder(L);
	//	printf("recv begin\n");
	t_socket* pts = (t_socket*)(binder.checkusertype(1, SOCKET_TYPE_NAME));
	int ret = recv(pts->socket, pts->buf.recvbuf, BUF_SIZE, 0);
	pts->buf.recv = ret;

	binder.pushnumber((lua_Number)(ret));

	return 1;
}

static int socket_selectread(lua_State* L)
{
	LuaBinder binder(L);
	fd_set* fdread = (fd_set*)(binder.checkusertype(1, FDSET_TYPENAME));

	int ret = select(0, fdread, 0, 0, 0);

	binder.pushnumber((lua_Number)(ret));

	return 1;
}

static int socket_selectwrite(lua_State* L)
{
	LuaBinder binder(L);
	fd_set* fdwrite = (fd_set*)(binder.checkusertype(1, FDSET_TYPENAME));

	int ret = select(0, 0, fdwrite, 0, 0);
	binder.pushnumber((lua_Number)(ret));
	
	return 1;
}

static int socket_selectexcept(lua_State* L)
{
	LuaBinder binder(L);
	fd_set* fdexcep = (fd_set*)(binder.checkusertype(1, FDSET_TYPENAME));

	int ret = select(0, 0, 0, fdexcep, 0);
	binder.pushnumber((lua_Number)(ret));

	return 1;
}

static int socket_eq(lua_State* L)
{
	LuaBinder binder(L);
	//	printf("socket eq check\n");
	SOCKET s1 = (SOCKET)(binder.checknumber(1));
	SOCKET s2 = (SOCKET)(binder.checknumber(2));

	binder.pushboolean(s1 == s2);

	return 1;
}

///////////////////////////////////////////////////////////////////////////////
static int socket_fdcreate(lua_State* L)
{
	LuaBinder binder(L);
	fd_set* fd = new fd_set;

	binder.pushusertype(fd, FDSET_TYPENAME);

	return 1;
}

static int socket_fdrelease(lua_State* L)
{
	LuaBinder binder(L);
	fd_set* fd = (fd_set*)(binder.checkusertype(1, FDSET_TYPENAME));
	SAFEDELETE(fd);

	return 0;
}

static int socket_fdzero(lua_State* L)
{
	LuaBinder binder(L);
	fd_set* fd = (fd_set*)(binder.checkusertype(1, FDSET_TYPENAME));

	FD_ZERO(fd);

	return 0;
}

static int socket_fdset(lua_State* L)
{
	LuaBinder binder(L);
	fd_set* fd = (fd_set*)(binder.checkusertype(1, FDSET_TYPENAME));
	SOCKET s = (SOCKET)(binder.checknumber(2));
	FD_SET(s, fd);

	return 0;
}

static int socket_fdisset(lua_State* L)
{
	LuaBinder binder(L);
	fd_set* fd = (fd_set*)(binder.checkusertype(1, FDSET_TYPENAME));
	SOCKET s = (SOCKET)(binder.checknumber(2));

	binder.pushboolean(FD_ISSET(s, fd) != 0);

	return 1;
}

static int socket_fdclr(lua_State* L)
{
	LuaBinder binder(L);
	fd_set* fd = (fd_set*)(binder.checkusertype(1, FDSET_TYPENAME));
	SOCKET s = (SOCKET)(binder.checknumber(2));

	FD_CLR(s, fd);

	return 0;
}

static int socket_fddup(lua_State* L)
{
	LuaBinder binder(L);
	fd_set* fddst = (fd_set*)(binder.checkusertype(1, FDSET_TYPENAME));
	fd_set* fdsrc = (fd_set*)(binder.checkusertype(2, FDSET_TYPENAME));

	memcpy(fddst, fdsrc, sizeof(fd_set));

	return 0;
}

static int socket_fdcount(lua_State* L)
{
	LuaBinder binder(L);
	fd_set* fd = (fd_set*)(binder.checkusertype(1, FDSET_TYPENAME));

	binder.pushnumber((lua_Number)(fd->fd_count));

	return 1;
}

static int socket_fdgetsocket(lua_State* L)
{
	LuaBinder binder(L);
	fd_set* fd = (fd_set*)(binder.checkusertype(1, FDSET_TYPENAME));
	size_t idx = (size_t)(binder.checknumber(2));

	binder.pushnumber((lua_Number)(fd->fd_array[idx]));

	return 1;
}

///////////////////////////////////////////////////////////////////////////////
static int t_socket_create(lua_State* L)
{
	LuaBinder binder(L);
	t_socket* pts = new t_socket;

	pts->socket = (int)socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	binder.pushusertype(pts, SOCKET_TYPE_NAME);

	return 1;
}

static int t_socket_setsenddata(lua_State* L)
{
	LuaBinder binder(L);
	t_socket* pts = (t_socket*)(binder.checkusertype(1, SOCKET_TYPE_NAME));
    const char* data = binder.checkstring(2);
	size_t size = (size_t)(binder.checknumber(3));

	assert(size <= BUF_SIZE);
	memcpy(pts->buf.sendbuf, data, size);
	pts->buf.sent = size;
	pts->buf.sendbuf[size] = 0;

	return 0;
}

static int t_socket_getrecvdata(lua_State* L)
{
	LuaBinder binder(L);
	//	printf("get data\n");
	t_socket* pts = (t_socket*)(binder.checkusertype(1, SOCKET_TYPE_NAME));

//	pts->buf.recv = 0;
	binder.pushstring(pts->buf.recvbuf);

	return 1;
}

static int t_socket_release(lua_State* L)
{
	LuaBinder binder(L);
	//	printf("called t_socket release\n");
	t_socket* pts = (t_socket*)(binder.checkusertype(1, SOCKET_TYPE_NAME));
	//	printf("%p socket: %d\n", pts, pts->socket);
	closesocket(pts->socket);
	SAFEDELETE(pts);

	return 0;
}

static int t_socket_getsentsize(lua_State* L)
{
	LuaBinder binder(L);
	t_socket* pts = (t_socket*)(binder.checkusertype(1, SOCKET_TYPE_NAME));

	binder.pushnumber((lua_Number)(pts->buf.sent));

	return 1;
}

static int t_socket_getrecvsize(lua_State* L)
{
	LuaBinder binder(L);
	t_socket* pts = (t_socket*)(binder.checkusertype(1, SOCKET_TYPE_NAME));

	binder.pushnumber((lua_Number)(pts->buf.recv));

	return 1;
}

static int t_socket_getsocket(lua_State* L)
{
	LuaBinder binder(L);
	//	printf("get socket\n");
	t_socket* pts = (t_socket*)(binder.checkusertype(1, SOCKET_TYPE_NAME));
	assert(pts);
	assert(pts->socket);

	binder.pushnumber((lua_Number)(pts->socket));

	return 1;
}

static int t_socket_socketeq(lua_State* L)
{
	LuaBinder binder(L);
	t_socket* pts1 = (t_socket*)(binder.checkusertype(1, SOCKET_TYPE_NAME));
	t_socket* pts2 = (t_socket*)(binder.checkusertype(2, SOCKET_TYPE_NAME));

	binder.pushboolean(pts1->socket == pts2->socket);

	return 1;
}

///////////////////////////////////////////////////////////////////////////////
static const luaL_reg socketlib[] = {
	{"init", 		socket_init},
	{"shutdown", 	socket_shutdown},
	{"create", 		socket_create},
	{"bind",		socket_bind},
	{"listen", 		socket_listen},
	{"accept",		socket_accept},
	{"close",		socket_close},
	{"connect",		socket_connect},
	{"send", 		socket_send},
	{"recv",		socket_recv},
	{"selectread",	socket_selectread},
	{"selectwrite",	socket_selectwrite},
	{"selectexcept",socket_selectexcept},
	//	{"iseq",		socket_eq},
	{NULL,			NULL},
};

static const luaL_reg t_socketlib [] = {
	{"create", 		t_socket_create},
	{"senddata",	t_socket_setsenddata},
	{"recvdata",	t_socket_getrecvdata},
	{"sendsize",	t_socket_getsentsize},
	{"recvsize",	t_socket_getrecvsize},
	//	{"__eq",		t_socket_socketeq},
	{"getsocket",	t_socket_getsocket},
	{NULL,			NULL},
};

static const luaL_reg fdlib [] = {
	{"create",		socket_fdcreate},
	{"zero",		socket_fdzero},
	{"set",			socket_fdset},
	{"isset",		socket_fdisset},
	{"clr",			socket_fdclr},
	{"dup",			socket_fddup},
	{"count",		socket_fdcount},
	{"getsocket",	socket_fdgetsocket},
	{NULL,			NULL},
};

///////////////////////////////////////////////////////////////////////////////
extern "C" {
__declspec(dllexport) int luaopen_socket(lua_State* L)
{
	LuaBinder binder(L);
	binder.init(SOCKET_LIBNAME, 0, socketlib, socket_close);
	binder.init(SOCKET_TYPE_NAME, 0, t_socketlib, t_socket_release);
	binder.init(FDSET_TYPENAME, 0, fdlib, socket_fdrelease);

	return 1;
}
}

BOOL APIENTRY DllMain( HANDLE hModule,
					   DWORD ul_reason_for_call,
					   LPVOID lpReserved
					   )
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}
