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

		Description:		���++ ����֧��ͷ�ļ�
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2000/10/20
		Modify Time:		2001/10/18

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_CANVAS_H
#define _WINDSOUL_CANVAS_H

//#define _RECORD_CANVAS

#include "wstimer.h"

class WCanvasBlock;
struct WCanvasInternalData;
class WCanvas;

class WINDSOUL_API memory<WCanvas>::manager;
template class WINDSOUL_API memory<WCanvas>;

class WINDSOUL_API WCanvas : WBitmap, public memory<WCanvas> {
	WTimer m_Timer;
public:
	int m_FrameTime;
protected:
	enum WCanvasChangedTag { change_null,change_full,change_self } changed;	// �ı���
	WCanvasInternalData *data;			// �ڲ�����
	WCanvasBlock *block;	// ��ͼ��
	int row;				// ����Ŀ
	int col;				// ����Ŀ
	int block_x;			// ��ʼ�� X
	int block_y;			// ��ʼ�� Y

	friend class WSurface;

	using WBitmap::operator();
public:
	using memory<WCanvas>::operator new;
	using memory<WCanvas>::operator delete;
	WCanvas(int width,int height);
	~WCanvas();
	void Update();
	void NextFrame();		// ׼����һ֡
	void SkipFrame();		// ������һ֡
	void Reset(int f);		// ʱ�Ӹ�λ
	void MoveTo(int x,int y);	// �ƶ��� p
	void MoveTo(WPoint p) { MoveTo(p.x,p.y); }
	void Move(int x,int y);	// �ƶ� (x,y)
	void Move(WPoint p) { Move(p.x,p.y); }
	int GetX() const;		// ��ȡ�������� X
	int GetY() const;		// ��ȡ�������� Y
	int GetW() const;		// ��� Canvas �Ŀ��ӿ��
	int GetH() const;		// ��� Canvas �Ŀ��Ӹ߶�
	WPoint GetViewPort(int x,int y) const;	// ��ȡ�ӿ�����ö�Ӧ��������
	WPoint GetViewPort(WPoint p) const { return GetViewPort(p.x,p.y); }
	void Clear(WPixel color);												// ��� Canvas
	void Clear();															// Canvas ��Ϣ�� 0
	WSERR Draw(const WObject &bmp, DWORD style);							// ��һ��ͼ
	WSERR DrawEx(const WObject &bmp, DWORD style);							// ��һ��ͼ(��������Ƿ����� Canvas ����)
	void Draw(const char *str, WPixel color);								// д ASCII String
	void Draw(WCanvas &canvas,DWORD style=BLIT_COPY);						// ������һ������
	void SetOvlRect(int w,int h);											// ��Ӹ��Ǿ���
	void SetOvlRect(const WRect &rect) { operator()(rect.x,rect.y); SetOvlRect(rect.w,rect.h); }
	WCanvas& operator() (int x,int y) { return SetPos(x,y); }				// ���ùؼ���
	WCanvas& operator() (WPoint p) { return SetPos(p.x,p.y); }				// ���ùؼ���
	WCanvas& SetPos(int x,int y);											// ���ùؼ���
	WCanvas& SetPos(WPoint p) { return SetPos(p.x,p.y); }
	WCanvas& AddPos(int x,int y);											// ���ùؼ���
	WCanvas& AddPos(WPoint p) { return AddPos(p.x,p.y); }
	WCanvas& ViewPort(int x,int y);											// �����ӿڹؼ���
	WCanvas& ViewPort(WPoint p) {return ViewPort(p.x,p.y); }				// �����ӿڹؼ���
	WCanvas& UnChange() { changed=change_null; return *this; }	// ���û���״̬Ϊ�����֡�����
	WCanvas& Change() { changed=change_full; return *this; }	// ���û���״̬Ϊ�����֡���
	WCanvas& SelfChange() { changed=change_self; return *this; }	//  ���û���״̬Ϊ�����֡������
	const WCanvas& operator()(DWORD userdata) const { SetUserData(userdata); return *this; }
	bool IsMoved() const;					// �Ƿ��ƶ�
	bool IsChanged() const { return (changed!=change_null); }
	void Update2DC(HDC hDC,int x,int y) const;		// ����ˢ��һ�ε� DC
	void Blit2DC(HDC hDC,int x,int y);      		// ���Ƶ� DC
	void BlitTo(WBitmap &bmp);						// copy ��λͼ
	void Blit(HDC hDC,int x,int y);					// Blit һ֡
	void SleepFrame();								// �ȴ�����֡ʱ�����
	void Laptop(bool Set=true);						// ���ñʼǱ�ģʽ

#ifdef _RECORD_CANVAS
	void Record(const char* path="d:/record");
#endif

	using WBitmap::SetUserData;
}; 

#endif
