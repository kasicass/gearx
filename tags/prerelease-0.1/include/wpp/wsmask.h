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

		Description:		���λͼ�ڲ�ͷ�ļ�
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2001/3/24
		Modify Time:		2001/11/14

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_MASK_H
#define _WINDSOUL_MASK_H

#include "wsaddon.h"
#include "wscanvas.h"
  
struct WMaskStruct;  

#define BLIT_BLUE BLIT_TRANS

class WINDSOULADD_API WMask : public WObject {
public: 
	WMask(); 
	WMask(const WBitmap &bmp, int x,int y,int w,int h) { Create(bmp,x,y,w,h); }
	WMask(const WBitmap &bmp, int x,int y,int w,int h,void *ptr) { Create(bmp,x,y,w,h,ptr); }
	~WMask();
       
	void Create(const WBitmap &bmp, int x,int y,int w,int h);
	void Create(const WBitmap &bmp, int x,int y,int w,int h,void *ptr);	// ��ָ������������
	
	int GetW() const;
	int GetH() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetKx() const;
	int GetKy() const;
	BLIT_FUNC DrawFunc(DWORD style) const;	// ��� Draw ����ָ��
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WMaskStruct *GetMaskStruct() const { return reinterpret_cast<WMaskStruct *>(objdata); }	// ��ȡ���ݽṹ

	WMask& Clip(int x,int y,int w,int h);	// ��Ա���ͼ���ü��þ���
	WMask& Clip(const WObject &sprite,int x,int y);		// ���ݾ��������ü��þ���
	WMask& Clip(const WObject &sprite,WPoint p) { return Clip(sprite,p.x,p.y); }
	WMask& ClipEx(const WObject &sprite,WPoint p,int w,int h);	// ����ʹ�� Attach ͼƬ(320x240) ��Mask ������
 	void Draw(const WMask &mask);			// �ϲ� Mask
	bool IsCover(int x,int y) const;		// �ж��Ƿ��ڵ�
	bool IsCover(WPoint p) const { return IsCover(p.x,p.y); }
	bool IsCoverEx(int x,int y) const;		// �ж��Ƿ��ڵ�
	bool IsCoverEx(WPoint p) const { return IsCoverEx(p.x,p.y); }
	WSERR Load(const void *maskdata,const WBitmap &);		// ������������Mask
	void DeleteBuffer();
	void DrawBorder(WBitmap &buffer);
	void DrawBorder(WCanvas &buffer) { DrawBorder(*reinterpret_cast<WBitmap*>(&buffer)); }
//	void Clear();							// ��� Mask ������
//	char *ClipBox() const;     
};   
 
inline WMask& WMask::Clip(const WObject &sprite,int x,int y)
{
	ASSERT(sprite.IsValid());  
	return Clip(x-sprite.GetX(),y-sprite.GetY(),sprite.GetW(),sprite.GetH());
} 
  
inline WMask& WMask::ClipEx(const WObject &sprite,WPoint p,int ww,int hh)
{ 
	ASSERT(sprite.IsValid());
	int x=p.x-sprite.GetX();
	int y=p.y-sprite.GetY();
	int w=sprite.GetW(),h=sprite.GetH();
	if (x<0) w=MAX(0,w+x),x=0; 
	if (y<0) h=MAX(0,h+y),y=0;  
	return Clip(x,y,MIN(ww,x+w)-x,MIN(hh,y+h)-y);
}
      
#endif