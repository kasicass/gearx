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

		Description:		ָ��ӳ��
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2000/12/12
		Modify Time:

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#ifndef _MAP_PTR2PTR_H
#define _MAP_PTR2PTR_H

class WMapPtr {
	enum {blocksize=2};
	int size;							// �ռ��С
	int num;							// ����Ԫ�ظ���
	void **ptr;							// ָ��ռ�
public:
	WMapPtr() : size(blocksize), num(0) ,ptr(new void*[blocksize*2]) {};
	~WMapPtr() { delete []ptr; }
	void * LookUp(void *) const;		// ����ָ��
	void Insert(void *key,void *var);	// ����ָ�� [key]=var
	void Delete(void *);				// ɾ��ָ��
};

#endif