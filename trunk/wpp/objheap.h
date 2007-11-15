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

		Description:		���λͼ�ڲ�ͷ�ļ� (������ʹ��)
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2000/12/9
		Modify Time:		2001/9/12

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_CANVASHEAP_INTERNAL_H
#define _WINDSOUL_CANVASHEAP_INTERNAL_H

#define MAXOBJECTSTRUCTSIZE 40

struct WObjectHeapPage {
	enum { size=128 };
	BYTE objstruct[size][MAXOBJECTSTRUCTSIZE];
	WObjectHeapPage *next;
	WObjectHeapPage() : next(0) {}
};

class WObjectHeap {
	int num;
	WObjectHeapPage *recent;
	WObjectHeapPage page;
public:
	WObjectHeap() : num(0) { recent=&page; }
	~WObjectHeap() { 
		WObjectHeapPage *p=page.next,*next;
		while (p) {
			next=p->next;
			delete p;
			p=next;
		}
	}
	void Clear() { num=0; recent=&page; }
	void *AllocObjectStruct() {
		if (num==WObjectHeapPage::size-1) {
			if (recent->next==0) recent->next=new WObjectHeapPage;
			recent=recent->next;
			num=0;
		}
		return (void*)(recent->objstruct[num++]);
	}
};
 
#endif