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

		Description:		��� Windows ����֧��
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2001/3/12
		Modify Time:		2001/9/12

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_FONT_INTERNAL_H
#define _WINDSOUL_FONT_INTERNAL_H

#include "windsoul.h"

struct WFontData {
	int w;									// ���
	int h;									// �߶�
	int width;								// �ֿ�
	int kx;									// X ƫ��
	int ky;									// Y ƫ��
	int size;								// ����
	BYTE *data;								// ʵ������
};
      
struct WCharStruct : public WObjStruct, memory<WCharStruct> {
	int w;									// ���
	int h;									// �߶�
	BYTE *data;								// ��һɨ����ָ��
	WPixel color;							// ��ɫ
	short int width;						// �ֿ�(���ּ��)

	WCharStruct() {}
	WCharStruct(const WCharStruct& c) {w=c.w,h=c.h,data=c.data,color=c.color;}
 	WCharStruct& operator=(const WCharStruct& c);	//�޴˺���
	using memory<WCharStruct>::operator new;
	using memory<WCharStruct>::operator delete;
	void *operator new(unsigned size,WObjectHeap *heap) { return WObjStruct::operator new(size,heap); }
#ifndef _BCB
	void operator delete(void *p,WObjectHeap *heap) {};
#endif    
};    
   
#endif