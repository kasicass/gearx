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

		Description:		��� Alpha ͨ���ڲ�ͷ�ļ�
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2001/3/9
		Modify Time:		2001/9/12

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _WINDSOUL_ALPHACHANNEL_INTERNAL_H
#define _WINDSOUL_ALPHACHANNEL_INTERNAL_H
 
struct WBmpData;
struct WChannelData;

struct WAlphaBmpStruct : public WBmpStruct, memory<WAlphaBmpStruct> {
	BYTE *channel;							// Alpha ͨ��
	void *cmem;								// Alpha ͨ���ڴ��

	WAlphaBmpStruct() {}
	WAlphaBmpStruct (const WAlphaBmpStruct&);

	~WAlphaBmpStruct();
	using memory<WAlphaBmpStruct>::operator new;
	using memory<WAlphaBmpStruct>::operator delete;
	void *operator new(unsigned size,WObjectHeap *heap) { return WObjStruct::operator new(size,heap); }
#ifndef _BCB
	void operator delete(void *p,WObjectHeap *heap) {};
#endif    
	WAlphaBmpStruct& operator=(const WAlphaBmpStruct& abmp);

	void Empty() { w=h=0,ptr=0,mem=0; }		// ��սṹ
};

#endif
