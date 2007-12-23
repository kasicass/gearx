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
 * @file   buffer.h
 * @author ChenZaichun <ChenZaichun@gmail.com>
 * @date   Tue Nov 20 11:54:31 2007
 * 
 * @brief  buffer for socket
 * 
 * 
 */

#ifndef _BUFFER_H_G
#define _BUFFER_H_G

#define BUF_SIZE 4086				/// default buffer size

#define BUFFER_CLASSNAME "buffer"	/// buffer class name for lua

/// buffer control structure
typedef struct t_buffer_ {
	size_t sent;				/**< bytes sent */
	size_t recv;				/**< bytes recevied */
	char   recvbuf[BUF_SIZE];	/**< receive data buffer */
    char   sendbuf[BUF_SIZE];	/**< send data buffer */
} t_buffer;


#endif

