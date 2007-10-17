
/*!
 * \file	GXUtils.h
 * \author	ChenZaichun
 * \date	Oct 14, 2007
 * \brief	utilities for GearX
 */

#ifndef _GX_UTILS_H
#define _GX_UTILS_H

#define SAFEDELETE(x) if (x) { delete (x); x = NULL; }
#define SAFEDELETE_ARRAY(x) if (x) { delete [] x; x = NULL; }

#endif