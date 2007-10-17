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

		Description:		���++ DDraw Surface
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2000/12/27
		Modify Time:		2002/4/15

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_SURFACE_H
#define _WINDSOUL_SURFACE_H

#include "wscanvas.h"

struct WSurfaceData;

class WINDSOUL_API WSurface {
protected:
	HWND m_hWnd;
	WSurfaceData *data;					// Surface �Ľṹ
	WCanvas *Canvas;
	WSERR CreateSurface();				// ���� Surface
	WSERR RestoreSurface();				// �л�����ʱ�ָ� Surface
	void Refresh();						// ˢ��
public:
	WSurface();
	~WSurface();
	void Release();						// �ͷ� DirectDraw
	WSERR RestoreDesktop();				// �ָ�����ֱ���
	WSERR SetDisplay(int w,int h);		// ���÷ֱ���
	WSERR Create(HWND hWnd,WCanvas& canvas);// �����Դ� Surface
	WSERR Blit2Screen(int x=0,int y=0);		// ���䵽��Ļ
};

#endif