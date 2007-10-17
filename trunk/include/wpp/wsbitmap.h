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

		Description:		���λͼ��
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2000/12/9
		Modify Time:		2001/11/21

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_BITMAP_H
#define _WINDSOUL_BITMAP_H

#include "wshelper.h"

 ///	Blit ��ʽ
/////////////////////////

#define BLIT_NORMAL	0
#define BLIT_COPY	0
#define BLIT_ADDITIVE	0x1
#define BLIT_SUBTRACT	0x2
#define BLIT_TRANS		0x3
#define BLIT_MASK		0x4
#define BLIT_BACK		0x5

 ///	WPixel ����
/////////////////////////

#pragma pack (push)
#pragma pack (1)

struct WPixel {
	union {
		WORD color;								// 16bit �߲�
		struct {
			WORD blue:5;						// 5bit ��ɫ
			WORD green:6;						// 6bit ��ɫ
			WORD red:5;							// 5bit ��ɫ
		};
	};
	WPixel() {}
	WPixel(DWORD c) { color = (WORD)((c>>8&0xf800)|(c>>5&0x7e0)|(c>>3&0x1f)); }
	WPixel(int r,int g,int b) : red(r>>3),green(g>>2),blue(b>>3) {}
	operator DWORD() const {
		return (color<<5&0x7fc00)|(color<<8&0xf80000)|((color<<3|(color&7))&0x3ff);
	}
};

#pragma pack (pop)

 ///	WBitmap λͼ
/////////////////////////

struct WBmpStruct;
struct WObjStruct;
class WObjectHeap;

typedef DWORD (_stdcall *BLIT_FUNC)(DWORD,DWORD);

struct WINDSOUL_API WObjStruct {
	int kx;									// ���ĵ� x
	int ky;									// ���ĵ� y
	void *operator new(unsigned size, WObjectHeap *heap);		// ��ָ���ѷ���(�������ͷ�)
	void operator delete(void *,WObjectHeap *) {};
};

struct WBmpData;

struct WINDSOUL_API WBmpStruct : public WObjStruct {
	int w;									// ���
	int h;									// �߶�
	int pitch;								// �п��ֽ�
	void *ptr;								// ��һɨ����ָ��
	WBmpData *mem;							// �����ڴ��ָ��
	DWORD userdata;							// ��������

	WBmpStruct() {}
	WBmpStruct (const WBmpStruct&);
	~WBmpStruct();
	void *operator new(unsigned size) { return ::operator new(size); }
	void operator delete(void *p) { ::operator delete(p); };
#if defined(_DEBUG) && !defined(_DISABLE_WINDSOUL_NEW)
	void *operator new(unsigned size,const char *file,unsigned line) { return ::operator new(size,file,line); }
	void operator delete(void *p,const char *file,unsigned line) { ::operator delete(p,file,line); };
#endif
	void *operator new(unsigned size,WObjectHeap *heap) { return WObjStruct::operator new(size,heap); }
	void operator delete(void *,WObjectHeap *) {};
	WBmpStruct& operator=(const WBmpStruct& bmp);
	void Empty() { w=h=0,ptr=0,mem=0; }		// ��սṹ
};

class WObject;

class WINDSOUL_API memory<WObject>::manager;
template class WINDSOUL_API memory<WObject>;

class WINDSOUL_API WObject : public memory<WObject> {
protected:
	void *objdata;
public:
	WObject() : objdata(0) {}
	virtual ~WObject() {};
	void SetData(void *p) { objdata=p; }				// ���� data
	WObjStruct *GetObjStruct() const { return reinterpret_cast<WObjStruct *>(objdata); }	// ��ȡ���ݽṹ
	virtual bool IsValid() const { return (objdata!=0); }		// �ж�λͼ�Ƿ���Ч
	void *GetData() const { return objdata; }			// �� data
	WObject& SetPos(const WPoint &p) { WObjStruct *data=GetObjStruct(); data->kx=p.x,data->ky=p.y; return *this;}	// ���ùؼ���
	WObject& SetPos(int x,int y) { WObjStruct *data=GetObjStruct(); data->kx=x,data->ky=y; return *this;}	// ���ùؼ���
	WObject& AddPos(const WPoint &p) { WObjStruct *data=GetObjStruct(); data->kx+=p.x,data->ky+=p.y; return *this;}	// ���ùؼ���
	WObject& AddPos(int x,int y) { WObjStruct *data=GetObjStruct(); data->kx+=x,data->ky+=y; return *this;}	// ���ùؼ���
	int GetX() const { return GetObjStruct()->kx; }		// ��ȡ kx
	int GetY() const { return GetObjStruct()->ky; }		// ��ȡ ky
	virtual int GetW() const=0;
	virtual int GetH() const=0;
	virtual BLIT_FUNC DrawFunc(DWORD style) const=0;	// ��� Draw ����ָ��
	virtual WObjStruct *Duplicate(WObjectHeap *heap) const=0;	// ���Լ������������
	virtual bool Affect(int, int) const { return true; }	// �ж϶����Ƿ�Ӱ�� Canvas ��
	virtual void SetUserData(DWORD) const {};			// �����û�����չ����
	virtual bool IsCover(WPoint p) const;				// �ж��Ƿ񸲸�һ����
};

inline bool WObject::IsCover(WPoint p) const
{
	return WRect(-GetX(),-GetY(),GetW(),GetH()).IsCover(p);
}

class WINDSOUL_API WBitmap : public WObject {
public:
	WBitmap() {}
	WBitmap(int w,int h) { Create(w,h); }
	WBitmap(int w,int h,void *ptr) { Create(w,h,ptr); }
	WBitmap(const WBitmap& bmp) {*this=bmp;}
	WBitmap(const WBitmap& bmp,int x,int y,int width,int height) { Create(bmp,x,y,width,height); }
	~WBitmap() { Destroy(); }
	WObjStruct *Duplicate(WObjectHeap *heap) const;
	WBitmap& operator=(const WBitmap& bmp);				// ����λͼ(����������)
	WBmpStruct *GetBmpStruct() const { return reinterpret_cast<WBmpStruct *>(objdata); }	// ��ȡ���ݽṹ
	virtual WSERR Create(int w,int h);					// ����λͼ
	virtual WSERR Create(int w,int h,void *ptr);		// ��������������λͼ
	WSERR Create(const WBitmap& parent,int x,int y,int width,int height);
	virtual WBitmap* SubBitmap(int x,int y,int width,int height) const;	// ������ͼ
	virtual void Destroy();								// ����λͼ
	WSERR Blit2DC(HDC hDC,int x,int y,int offset=0) const;	// ���͵� DC (����и�λͼ ,offset Ϊ���ڸ�ͼ�ϵ� X ƫ��)
	WSERR Blit2DC(HDC hDC,int dx,int dy,int x,int y,int w,int h) const;	// BLIT һ�����β��ֵ� DC
	int GetW() const;									// ȡ���
	int GetH() const;									// ȡ�߶�
	WPixel * operator[](int y) const;					// ����һ��ɨ����ָ��
	void SetUserData(DWORD userdata) const;				// �����û�����
	const WBitmap& operator()(DWORD userdata) const { SetUserData(userdata); return *this; }
	WBitmap& operator()(int x,int y) { SetPos(x,y); return *this; }
	WBitmap& operator()(WPoint p) { SetPos(p); return *this; }
	WBitmap operator() (int x,int y,int width,int height) const { return WBitmap(*this,x,y,width,height); }
	virtual WSERR Draw(const WObject &bmp, DWORD style);		// �� bmp ���Ƶ� this ��
	WSERR Clear(WPixel color);							// ��λͼ
	void Draw(const char *s,WPixel color);				// ��� Ascii �ַ���
	static BLIT_FUNC ClearFunc();						// ��� Clear ����ָ��
	BLIT_FUNC DrawFunc(DWORD style) const;				// ��� Draw ����ָ��
	static void RegisterDrawFunc(BLIT_FUNC,DWORD style);// ע���ͼ����
	WSERR Load(void *bmpdata);					// ������������λͼ
	WSERR Save(const char *filename) const;
	bool IsCover(WPoint p) const;				// �ж��Ƿ񸲸�һ����
};

#endif