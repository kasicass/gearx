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

		Description:		���++ ���κ���
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2001/1/17
		Modify Time:		2001/11/13

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/
 
#ifndef _WINDSOUL_GEOMETRY_H
#define _WINDSOUL_GEOMETRY_H
 
#include "windsoul.h"

#define BLIT_XOR	0x4

struct WLineStruct;
struct WBoxStruct;

class WINDSOUL_API WLine : public WObject { 
	WLine(const WLine& line);							// �պ���,���ܿ�������
	WLine& operator=(const WLine& Line);
public:
	WLine(int x=0,int y=0,WPixel color=0);
	~WLine();

	int GetW() const;
	int GetH() const;
	BLIT_FUNC DrawFunc(DWORD style) const;				// ��� Draw ����ָ��
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WLineStruct *GetLineStruct() const { return reinterpret_cast<WLineStruct *>(objdata); }	// ��ȡ���ݽṹ
	bool Affect(int x,int y) const;						// �ж϶����Ƿ�Ӱ�� Canvas ��
	WLine& Color(WPixel color);							// ����ɫ
	WLine& Size(int x,int y);							// ����С
	void SetUserData(DWORD userdata) const;				// �����û�����
	const WLine& operator()(DWORD userdata) const { SetUserData(userdata); return *this; }
};

class WINDSOUL_API WBox : public WObject {
	WBox(const WBox& box);								// �պ���,���ܿ�������
	WBox& operator=(const WBox& box);
public:
	WBox(int w=0,int h=0,WPixel color=0);
	~WBox();

	int GetW() const;
	int GetH() const;
	BLIT_FUNC DrawFunc(DWORD style) const;				// ��� Draw ����ָ��
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WBoxStruct *GetBoxStruct() const { return reinterpret_cast<WBoxStruct *>(objdata); }	// ��ȡ���ݽṹ
	WBox& Color(WPixel color);							// ����ɫ
	WBox& Size(int w,int h);							// ����С
	void SetUserData(DWORD userdata) const;				// �����û�����
	const WBox& operator()(DWORD userdata) const { SetUserData(userdata); return *this; }
};

inline WORD PixelAlphaBlending(DWORD x,DWORD y,int alpha)
{
	DWORD result;
    x = ((x&0xFFFF) | (x<<16)) & 0x7E0F81F;
    y = ((y&0xFFFF) | (y<<16)) & 0x7E0F81F;

    result = ((y - x) * alpha / 32 + x) & 0x7E0F81F;
    return (WORD)((result&0xFFFF) | (result>>16));
}
  
#endif