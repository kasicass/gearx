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

		Description:		���εؿ�
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2001/10/14
		Modify Time:		20001/10/29

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/
 
#ifndef _WINDSOUL_LOZENGE_H
#define _WINDSOUL_LOZENGE_H

#pragma once

#include "wsaddon.h"
 
struct WLozengeStruct;
        
class WINDSOULADD_API WLozenge : public WObject {
public:      
	WLozenge(WPixel color=0,int size=16);
	WLozenge(const WBitmap &father,int x,int y,int size=16);
	WLozenge(const WLozenge &);
	~WLozenge();

	const WLozenge& operator=(const WLozenge&);
	WSERR Create(WPixel color=0,int size=16);						// ������ɫ�����εؿ�
	WSERR Create(const WBitmap &father,int x,int y,int size=16);	// ��һ��λͼ�д��������εؿ�
    
	int GetW() const;
	int GetH() const;

	void SetUserData(DWORD userdata) const ;	// �����û�����(��ɫ)
	BLIT_FUNC DrawFunc(DWORD style) const;	// ��� Draw ����ָ��
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WLozengeStruct *GetLozengeStruct() const { return reinterpret_cast<WLozengeStruct *>(objdata); }	// ��ȡ���ݽṹ
};       
 
#endif