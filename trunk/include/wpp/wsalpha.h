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

		Description:		��� Alpha ͨ��ͷ�ļ�
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2001/3/15
		Modify Time:		2001/12/21

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_ALPHACHANNEL_H
#define _WINDSOUL_ALPHACHANNEL_H

struct WAlphaBmpStruct;

class WINDSOUL_API WAlphaBitmap : public WBitmap {
public:
	WAlphaBitmap() {}
	WAlphaBitmap(int w,int h) { Create(w,h); }
	WAlphaBitmap(int w,int h,void *ptr) { Create(w,h,ptr); }
	WAlphaBitmap(const WAlphaBitmap& bmp) {*this=bmp;}
	WAlphaBitmap(const WAlphaBitmap& bmp,int x,int y,int width,int height) { Create(bmp,x,y,width,height); }
	~WAlphaBitmap() { Destroy(); }
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WAlphaBitmap& operator=(const WAlphaBitmap& bmp);	// ����λͼ(����������)
	WAlphaBmpStruct *GetAlphaBmpStruct() const { return reinterpret_cast<WAlphaBmpStruct *>(objdata); }	// ��ȡ���ݽṹ
	WSERR Create(int w,int h);							// ����λͼ
	WSERR Create(int w,int h,void *ptr);				// ��ָ������������λͼ
	WSERR Create(const WAlphaBitmap& parent,int x,int y,int width,int height);
	WBitmap* SubBitmap(int x,int y,int width,int height) const;	// ������ͼ
	void Destroy();										// ����λͼ
	BYTE * ChannelLine(int y) const;					// ���� Channel ͨ��ָ��
	const WAlphaBitmap& operator()(int userdata) const { SetUserData(userdata); return *this; }
	WAlphaBitmap operator() (int x,int y,int width,int height) const { return WAlphaBitmap(*this,x,y,width,height); }
	BLIT_FUNC DrawFunc(DWORD style) const;				// ��� Draw ����ָ��
	WSERR LoadTGA(const void *tgadata);					// ������������λͼ
	WSERR Combine(const WAlphaBitmap& bmp);				// �ϲ����� Alpha λͼ
	void ClearChannel(int alpha);						// ��� Alpha Channel
	WSERR SaveTGA(const char *filename) const;
	bool IsCover(WPoint p) const;
};

#endif
