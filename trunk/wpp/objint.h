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

                  ���� DirectX ����Ϸ�����               
        A Game Programming Library Base On DirectX    
  
                by �Ʒ� (Cloud Wu)  1999-2000                          
 
		http://member.netease.com/~cloudwu 
		mailto:cloudwu@263.net
 
		���Ķ� readme.txt �еİ�Ȩ��Ϣ
		See readme.txt for copyright information.

		Description:		�������ڲ�ͷ�ļ�
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2000/1/2
		Modify Time:

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef WINDSOUL_OBJECT_INTERNAL_H_
#define WINDSOUL_OBJECT_INTERNAL_H_

struct WObjStruct {
	int kx;									// ���ĵ� x
	int ky;									// ���ĵ� y
	void *operator new(unsigned size,WObjectHeap *heap);		// ��ָ���ѷ���(�������ͷ�)
	void operator delete(void *p,WObjectHeap *heap) {};
};

#endif
