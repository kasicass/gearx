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

		Description:		λͼ�ڴ����ͷ�ļ�
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2000/9/15
		Modify Time:		2001/9/8

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_BMPMEM_H
#define _WINDSOUL_BMPMEM_H

#include <windows.h>
#include <ddraw.h>
#include "windsoul.h"

#define MAXOBJECTSTRUCTSIZE 40

struct WBmpData : public memory<WBmpData> {
//	int times;								// ���ô���
	union {
		HBITMAP hBmp;						// λͼ���
		HGLOBAL hMem;						// �ڴ���
		LPDIRECTDRAWSURFACE lpDS;			// DirectDraw Surface
		void *lpMem;						// �ڴ�ָ��
	};
	void (*destroy)(DWORD ptr);				// �ͷź���
public:
//	WBmpData() : times(0) {}
	~WBmpData() { destroy((DWORD)lpMem); }
	static void destroy_lpMem(DWORD ptr);	// �ͷ� lpMem
	static void destroy_hBmp(DWORD ptr);	// �ͷ� hBmp
};

/*
inline WBmpData::~WBmpData() 
{
//	if (!lpMem) return;
// ���ͷ� BMP MemPage ��ʱ��, ���е� times ���� 0, ���ﲻ������
	if (--times==0) {
		destroy((DWORD)lpMem);
//		MEMORY::bmp_data.free(this);
	}
//	lpMem=0;
}
*/

#endif