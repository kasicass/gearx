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

		Description:		RichText ��
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2001/11/15
		Modify Time:

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/
  
#ifndef _WINDSOUL_RICHTEXT_H_
#define _WINDSOUL_RICHTEXT_H_

#pragma once

#include "windsoul.h"
#include "wsaddon.h"
#include "wsstring.h"
#include "wscanvas.h"
#include "wsprite.h"

#pragma warning( disable : 4251 )

class WFont;
struct WRichTextArray;

class WINDSOULADD_API WRichText {
	WString m_Text;
	int m_MaxLines;
	int m_Lines;
	WString *m_Line;			// ÿ�е�չ������
	WRichTextArray &m_Array;	// ��������

	WPixel m_Color;
	WFont *m_Font;

	void IncreaseLines();		// ��������
	static WSpriteAni* s_Sprite;	// ���鶯��
	static int s_SpriteNumber;
	static unsigned s_SpriteSpeed;
public:
	WRichText();
	WRichText(const WString &text);
	~WRichText();

	static void LoadSprite(const char *path,int speed=5);	// ��ȡ·��

	void SetString(const WString &text) { m_Text=text; }
	const WString& GetString() const { return m_Text; } 
	int Format(WFont &font,int width);			// �����ؿ�ȸ�ʽ����, ��������
	int GetLines() const { return m_Lines; }	// �ϴ� Format �������
	void SetColor(WPixel color) { m_Color=color; }	// ������ɫ
	void Draw(int n,WBitmap &buffer,DWORD style=0,int alpha=128);		// ����ַ���
	void Draw(int n,WCanvas &buffer,DWORD style=0,int alpha=128);
	int GetLength(int n) const;					// ��ȡ�� n �еĿ��
	int GetHeight(int n) const;					// ��ȡ�� n �еĸ߶�
	int GetHeight() const;
	const WString & GetLine(int n) const { return m_Line[n]; }
	int GetWord(int n) const;
	static void Release();
};

#endif