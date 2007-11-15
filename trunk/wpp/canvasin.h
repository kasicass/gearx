/*
 "               ..;;;;,                     ;;;,    
 '           ..;;;"` ;;:           ,;;;;;: ,;;;:.,;..          _/
 `     ,;..,;;"`    :;;'            :;;"`,;;;;;;"":;;         _/ 
       ;;;"  `:;;. ;;'           ..;;:  .;;,.;;:',;;"    _/_/_/_/_/
      .;;`   ,;;" .;"          ,;;;;;;" :;`',;",;;"         _/
     ,;;,:.,;;;  ,;:          :" ,;:` , `:.;;;;;'`         _/   
     ;;"'':;;:. .;; .          ,;;;,;:;;,;;;, ,;             _/
    :;;..;;;;;; :;' :.        :;;;"` `:;;;;;,;,.;.          _/
  .;;":;;`  '"";;:  ';;       '""   .;;`.;";:;;;;` ;,  _/_/_/_/_/
 ;;;" `'       "::. ,;;:          .;"`  ::. '   .,;;;     _/ 
 ""             ';;;;;;;"        ""     ';;;;;;;;;;`     _/
 
                        Windsoul++

                by �Ʒ� (Cloud Wu)  1999-2001
 
		http://member.netease.com/~cloudwu 
		mailto:cloudwu@263.net
 
		���Ķ� readme.txt �еİ�Ȩ��Ϣ
		See readme.txt for copyright information.

		Description:		��껭���ڲ�ͷ�ļ�
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2000/12/14
		Modify Time:		2001/9/12

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_CANVAS_INTERNAL_H
#define _WINDSOUL_CANVAS_INTERNAL_H

//�������,�㽫�������Ż��� Canvas ����
// #define _DEBUG_CANVAS

#include "objheap.h"

struct CANVAS_LINK {
	BLIT_FUNC blit_func;
	DWORD param;
	CANVAS_LINK *next;
};

struct CANVAS_RECTLINK {
	WRect rect;
	CANVAS_RECTLINK *next;
};

template <class T,int size=128>
class CANVAS_LINKPAGE {
	T page[size];
	CANVAS_LINKPAGE *next;
	int top;
public:
	CANVAS_LINKPAGE() : next(0), top(0) {}
	~CANVAS_LINKPAGE() { if (next) delete(next); }
	void clear() { top=0; }	// ���
	void clearobj(WObjectHeap &heap);	// ��ͬ����һ�����
	T *alloc();				// ����һ���ڵ�
};

template <class T,int size>
void CANVAS_LINKPAGE<T,size>::clearobj(WObjectHeap &heap)
{
//	CANVAS_LINKPAGE *p;
//	int i;
//	for (p=this;p;p=p->next)
//		for (i=0;i<p->top;i++)
//			p->page[i].~T();
	heap.Clear();
	top=0;
}

template <class T,int size>
T* CANVAS_LINKPAGE<T,size>::alloc()
{
	CANVAS_LINKPAGE *p=this;
	while (p->top>=size) 
		p=p->next;
	if (++p->top>=size) {
		if (p->next) p->next->top=0;
		else p->next=new CANVAS_LINKPAGE<T,size>;
	}
	return &p->page[p->top-1];
}

class WCanvasBlock : public WBitmap {
	int last;				// ��һ֡������Ŀ
	int obj;				// ��ǰ���϶�����Ŀ
	int offset;				// ��λͼ�е�Xƫ��
	bool m_IsTrans;			// �Ƿ���͸����
	bool m_IsOvl;			// �Ƿ񱻸���
	CANVAS_LINK link;		// ��������ͷ
	CANVAS_LINK *change;	// ��ʼ�ı�Ľڵ�
#ifdef _DEBUG_CANVAS
	bool m_IsMasked;		// �Ƿ�Ϊû�ı�Ŀ����� Mask
#endif
friend class WSurface;
friend class WCanvas;
public:
#ifdef _DEBUG_CANVAS
	WCanvasBlock() : obj(0), last(0), m_IsMasked(false) {}
#else
	WCanvasBlock() : obj(0), last(0) {}
#endif
};

#ifdef _RECORD_CANVAS

struct WCanvasRecorder {
	struct Block {
		WBitmap bmp;
		WORD id;
		Block *next;
	};
	Block *blocks;
	WORD block_x;
	WORD block_y;
	WORD offset_x;
	WORD offset_y;
	WCanvasRecorder *next;
};
#endif

struct WCanvasInternalData {
	CANVAS_RECTLINK rect_link;	// ���Ǿ�������ͷ
	CANVAS_LINKPAGE<CANVAS_LINK> object_mem;
	CANVAS_LINKPAGE<CANVAS_RECTLINK> rect_mem;
	WPoint offset;				// ��ʼ��
	WRect viewport;				// ��ʾ����
	bool moved;					// �������
	bool laptop;
	WObjectHeap heap;			// Canvas�õķ����
	short timer;				// fps ����ʹ��

#ifdef _RECORD_CANVAS
	WCanvasRecorder *recorder_head;
	WCanvasRecorder *recorder_p;

	WCanvasInternalData(int width,int height) : viewport(0,0,width,height),offset(0,0),moved(false),timer(0),recorder_head(0),laptop(false) {}
#else
	WCanvasInternalData(int width,int height) : viewport(0,0,width,height),offset(0,0),moved(false),timer(0),laptop(false) {}
#endif
};

#endif