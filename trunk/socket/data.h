
/*  emacs: -*- mode: c++; coding: gbk -*- TAB SIZE: 4 -*-  */

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
 * @file   data.h
 * @author ChenZaichun <ChenZaichun@gmail.com>
 * @date   Tue Nov 20 15:37:58 2007
 * 
 * @brief  network data for gearx
 * 
 * 
 */


#ifndef _DATA_H_G
#define _DATA_H_G

/// data type for network data
typedef enum t_data_type_ {
	MESSAGE,
	GAME_DATA,
} t_data_type;

/// data structure for gearx network
typedef struct t_data_ {
	t_data_type type;
	size_t size;
	void* data;
} t_data;



#endif
