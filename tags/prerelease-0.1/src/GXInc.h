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

/**
 * @file   GXInc.h
 * @author ChenZaichun <ChenZaichun@gmail.com>
 * @date   Mon Nov 12 17:22:14 2007
 * 
 * @brief  global include file
 * 
 * 
 */

#ifndef _GX_INC_H
#define _GC_INC_H

#include <windows.h>
#include "windsoul.h"
#include "wsfile.h"
#include "wsapp.h"
#include "wscanvas.h"
#include "wsurface.h"

#include "wstimer.h"
#include "wsstring.h"
#include "wsalpha.h"
#include "wsfont.h"
#include "wsgeo.h"

// Lua header
#include "GXLua.hpp"

#include "GXUtils.h"

// Lua binder
#include "Binder.h"


#define GXBITMAP_CLASSNAME	"WBitmap"
#define GXCANVAS_CLASSNAME	"WCanvas"
#define GXFILE_CLASSNAME	"WFile"				/// 用于注册类名
#define GXOBJECT_CLASNAME	"WObject"
#define GXSURFACE_CLASSNAME	"WSurface"
#define GXFONT_CLASSNAME	"WFont"

/// music name explose in Lua
#define GXMUSIC_CLASSNAME	"GXMusic"


#define new debug_new

#endif
