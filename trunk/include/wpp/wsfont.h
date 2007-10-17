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
		Modify Time:		2001/11/12

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_FONT_H
#define _WINDSOUL_FONT_H
 
#ifndef _WINDOWS_
#error Include windows.h first!
#endif

#include "wsbitmap.h"

#define FONT_ALPHA		0
#define FONT_NOALPHA	1

struct WFontData; 
struct WCharStruct;
class WCanvas;

 ///	����
/////////////////////////

class WINDSOUL_API WFont {
	int m_CacheSize;
	int m_CacheNum;

	struct Data {
		unsigned int c;
		int freq;
		unsigned short id;
	} *m_Data;
	WFontData *m_FontData;

	HDC m_FontDC;
	HBITMAP m_FontBmp;
	WORD *m_Buffer;
	int m_Ascent;
	int m_Height;
	int m_Locked;
	int m_Freq;
	int m_Alpha;
	int m_MaxWidth;
private: 
	int SearchChar(unsigned int c) const;	// �� Cache ������һ���ַ�
	void ExpandCacheSize(int newsize);		// ��չ CacheSize
public:
	WFont() : m_CacheSize(0), m_Height(0) {}
	WFont(HFONT font,int alpha=16, int cachesize=128) : m_CacheSize(0) { Create(font,alpha,cachesize); }
	~WFont() { Destroy(); }

	WSERR Create(HFONT,int alpha=16,int cachesize=128);	// �� HFONT �д�������
	void Destroy();									// ��������
	WFontData *GetChar(unsigned int c);				// ��ȡһ���ֵ�����(�ڲ�ʹ��)
	int GetHeight() const { return m_Height; }		// ��ȡ����߶�
 
	void Lock() { m_Locked=m_Freq+1; }				// Lock Cache Buffer (����ɾ��)
	void Unlock() { m_Locked=0; }					// Unlock Cache Buffer
	DWORD BestStyle() const { return (m_Alpha==0)?FONT_NOALPHA:FONT_ALPHA; }
   
	DWORD GetLength(const char *str);
	void Draw(WBitmap &buffer,const char *str,WPixel color, DWORD style=FONT_ALPHA);		// ����ַ���
	void Draw(WCanvas &buffer,const char *str,WPixel color, DWORD style=FONT_ALPHA)	{
		Draw(*reinterpret_cast<WBitmap*>(&buffer),str,color,style);
	}
};   
         
 ///	�ַ����� 
/////////////////////////
  
class WINDSOUL_API WChar : public WObject {
public:
	WChar() {} 
	WChar(WFont &font,unsigned int c,WPixel color) { Create(font,c,color); }
	~WChar() { Destroy(); }
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WCharStruct *GetCharStruct() const { return reinterpret_cast<WCharStruct *>(objdata); }	// ��ȡ���ݽṹ
	WSERR Create(WFont &,unsigned int c,WPixel color);	// �����ַ�
	void Destroy();										// ����
	int GetW() const;									// ȡ���
	int GetH() const;									// ȡ�߶�
	int GetWidth() const;								// ȡ�ֿ�
	BLIT_FUNC DrawFunc(DWORD style) const;				// ��� Draw ����ָ��
};
 
#endif
