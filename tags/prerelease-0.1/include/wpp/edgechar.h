#ifndef _WINDSOUL_EDGE_CHAR_H_
#define _WINDSOUL_EDGE_CHAR_H_

#pragma once

#include "windsoul.h"
#include "wsaddon.h"

struct WEdgeCharStruct;

class WINDSOULADD_API WEdgeChar : public WObject {
public:
	WEdgeChar() {} 
	WEdgeChar(int size,unsigned int c,WPixel color,WPixel edge) { Create(size,c,color,edge); }
	~WEdgeChar() { Destroy(); }
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WEdgeCharStruct *GetEdgeCharStruct() const { return reinterpret_cast<WEdgeCharStruct *>(objdata); }	// ��ȡ���ݽṹ
	WSERR Create(int size,unsigned int c,WPixel color,WPixel edge);	// �����ַ�
	void Destroy();										// ����
	int GetW() const;									// ȡ���
	int GetH() const;									// ȡ�߶�
	int GetWidth() const;								// ȡ�ֿ�
	BLIT_FUNC DrawFunc(DWORD style) const;				// ��� Draw ����ָ��
};

#endif