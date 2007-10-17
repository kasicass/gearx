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

		Description:		���Ӧ�ó���ͷ�ļ�
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2000/12/12
		Modify Time:		2002/3/4

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_APPLICATION_H
#define _WINDSOUL_APPLICATION_H

#ifndef _WINDOWS_
#error Include windows.h first!
#endif

//class WMapPtr;

class WWindow;

typedef int (WWindow::*WWndFunc)(DWORD,DWORD);

struct WMessageFunc {
	DWORD id;
	WWndFunc func;
};

#define MAP_MESSAGE_FUNC()								\
public:													\
virtual const WMessageFunc* GetMessageEntries() { return messageEntries; }	\
static const WMessageFunc messageEntries[];


#define BEGIN_MAP_MESSAGE(thisclass,baseclass)			\
const WMessageFunc thisclass::messageEntries[]={		\
	{(DWORD)(baseclass::messageEntries),0},
#define MAP_MESSAGE(id,func) {id,(WWndFunc)&func},
#define END_MAP_MESSAGE() {0,0}};

class WINDSOUL_API WWindow {
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WWndProc(WWindow *wnd,UINT message, WPARAM wParam, LPARAM lParam);
	enum { blocksize=32 };
	int maxchildwnd;				// ����Ӵ�������
	int num;						// �Ӵ�������
	WWindow **childwnd;				// �Ӵ���
protected:
	HWND hWnd;
public:
	WWindow() : hWnd(0), maxchildwnd(0), num(0) {};
	virtual ~WWindow();
	HWND GetHandle() const { return hWnd; }
	bool Create(const char *name,DWORD style=WS_OVERLAPPEDWINDOW, int w=CW_USEDEFAULT, int h=0, int x=CW_USEDEFAULT, int y=0,HWND parent=0);	// ��������
	bool CreateEx(DWORD exstyle, const char *name,DWORD style=WS_OVERLAPPEDWINDOW, int w=CW_USEDEFAULT, int h=0, int x=CW_USEDEFAULT, int y=0,HWND parent=0);	// ��������
	WWindow *CreateChild(const char *classname,const char *name,DWORD style,int x,int y,int w,int h,DWORD id);	// �����Ӵ���
	const char *GetText();							// �õ�������
	void SetText(const char *text);					// ���ô�����
	static void Init(HINSTANCE hInstance);			// ��ʼ������
	static ATOM RegisterWndClass(const char *classname,DWORD style,HICON icon,HCURSOR cursor,HBRUSH brush,const char *menuname);	// ע�ᴰ����
	int Show(int show=SW_SHOWDEFAULT) const;		// ��ʾ����
	int Update() const;								// ˢ�´���
	HDC GetDC() const;								// ��ô��� DC (��ȫ�ͷ�)
	void ReleaseDC(HDC) const;						// �ͷ� DC (���Բ�����)
	MAP_MESSAGE_FUNC()								// ��Ϣӳ���
};

class WINDSOUL_API WApplication : public WWindow {
	MAP_MESSAGE_FUNC()
	int OnDestroy(DWORD w,DWORD l);					// ���ڹر�, ��һ�˳���Ϣ
protected:
	virtual void AfterCreate() {};					// �������֮�����
	virtual void BeforeExit() {};					// �˳�֮ǰ����
	virtual void Idle() {};							// ����ʱ������ (��Ϸ��ѭ��)
public:
	WApplication(HINSTANCE hInst);
	virtual ~WApplication() {};
	
	// ����������
	virtual bool CreateMainWindow(const char *szTitle = "WindSoul", 
								  DWORD style=WS_OVERLAPPEDWINDOW,
								  int width = CW_USEDEFAULT, int height = CW_USEDEFAULT);
	
	void Excute();									// ����
	void Quit();									// �رմ����˳�����
};

#endif