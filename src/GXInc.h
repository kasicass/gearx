
/*!
 * $Id$
 * 
 * \date	Oct 14, 2007
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

#define new debug_new

#endif