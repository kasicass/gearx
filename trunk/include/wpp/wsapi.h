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

		Description:		��� API ͷ�ļ�
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2001/1/4
		Modify Time:

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_API_H
#define _WINDSOUL_API_H

#ifdef WINDSOUL_EXPORTS
	#define WSDLL_API __declspec(dllexport)
#else
	#define WSDLL_API __declspec(dllimport)
#endif

#define WSAPI __stdcall

typedef int ws_handle;
typedef unsigned long ws_color;

extern "C" {
WSDLL_API ws_handle WSAPI create_bitmap(int w,int h);									//���� w * h ��λͼ
WSDLL_API ws_handle WSAPI create_sub_bitmap(ws_handle handle,int x,int y,int w,int h);	// ��һ��λͼ�ﴴ����һ����λͼ
WSDLL_API ws_handle WSAPI load_bitmap(const char *);									// ��һ���ļ�����һ��λͼ
WSDLL_API void WSAPI destroy_bitmap(ws_handle handle);									// ɾ��λͼ
WSDLL_API void WSAPI destroy_canvas(ws_handle handle);
WSDLL_API int WSAPI bitmap_command(ws_handle handle,int command,int param1,int param2);	// λͼ����ָ��
WSDLL_API ws_handle WSAPI create_canvas(int w,int h);						// ����һ�� canvas (w * h)
WSDLL_API int WSAPI canvas_command(ws_handle handle,int command,int param1,int param2);	// canvas ����ָ��
WSDLL_API int WSAPI canvas_command_stream(ws_handle handle,int command_num,int *);		// canvas ����ָ��
WSDLL_API void WSAPI refresh_canvas(ws_handle handle,void *hdc);						// ˢ�� canvas
WSDLL_API void WSAPI skipframe_canvas(ws_handle handle);								// ����һ֡ˢ��
WSDLL_API void WSAPI update_canvas(ws_handle handle,void *hdc);							// ˢ��һ֡ͼƬ
WSDLL_API void WSAPI update_bitmap(ws_handle handle,void *hdc);
WSDLL_API ws_handle WSAPI create_text();												// �������ֶ���
WSDLL_API void WSAPI destroy_text(ws_handle str);										// �������ֶ���
WSDLL_API void WSAPI set_text(ws_handle handle,const char *);							// �������ֶ���
};

// �趨�ؼ��� (int x,int y)
#define	C_SETPOS	1
// ��� (ws_color color,null)
#define C_CLEAR		2
// BLIT (ws_handle,DWORD style)
#define C_BLIT		3
// д����	(ws_handle,ws_color)
#define C_DRAWTEXT		4
// У��Ϸ���
#define C_ISVALID		5
// �õ����ص�	(int x,int y)
#define C_GETPIXEL		101
// �������ص�	(ws_color,null)
#define C_PUTPIXEL		102
// ������Ļ����	(x,y)
#define C_SETSCREENPOS	103
// CanvasBlit (ws_handle,null)
#define C_BLITCANVAS	201
// ���ø���״̬	(int changed,null)
#define C_CHANGE		202

#define C_MOVE			203
#define C_MOVETO		204

// blit ��ʽ
#define BLIT_COPY	0
#define BLIT_ADDITIVE	0x1
#define BLIT_SUBTRACT	0x2
#define BLIT_TRANS		0x3
#define BLIT_MASK		0x4

#define CANVAS_NOCHANGE	0
#define CANVAS_CHANGE	1
#define CANVAS_SELFCHANGE	2

#endif