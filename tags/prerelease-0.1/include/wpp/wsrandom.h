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

		Description:		�����
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2001/7/18
		Modify Time:		2001/10/28

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_RANDOM_H
#define _WINDSOUL_RANDOM_H

#pragma once

#include "wsaddon.h"

class WINDSOULADD_API WRandom {
	enum { Number=0x1000 };
	unsigned long *m_Buffer;
	unsigned long m_Seed;
	unsigned m_Ptr;

	void Batch();
public:
	WRandom();
	~WRandom();

	void Seed(unsigned long seed);	// �̶�����
	unsigned long Seed();					// �������

	unsigned short GetWord();		// ��һ�� Word
	unsigned long GetDWord();		// ��һ�� DWord
};

#endif