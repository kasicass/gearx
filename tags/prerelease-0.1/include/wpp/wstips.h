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

		Description:		Tips ��
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2001/11/13
		Modify Time:		2001/11/28

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/
  
#ifndef _WINDSOUL_TIPS_H_
#define _WINDSOUL_TIPS_H_

#pragma once

#include "windsoul.h"
#include "wsaddon.h"

struct WTipsStruct;
class WFont;
class WString;

class WINDSOULADD_API WTips : public WObject {
public:
	WTips() {}
	WTips(WFont &font, const char *str) { Create(font,str); }
	~WTips() { Destroy(); };
	 
	void Create(WFont &font, const char *str);
	void Destroy();
	int GetW() const;    
	int GetH() const;
	BLIT_FUNC DrawFunc(DWORD style) const;				// ��� Draw ����ָ��
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WTipsStruct *GetTipsStruct() const { return reinterpret_cast<WTipsStruct *>(objdata); }	// ��ȡ���ݽṹ
	void SetUserData(DWORD userdata) const;				// �����û�����
	void SetColor(WPixel color);						// ������ɫ
	const WTips& operator()(DWORD userdata) const { SetUserData(userdata); return *this; }
};          

#endif