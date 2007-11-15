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

		Description:		��꼸�κ����ڲ�ͷ�ļ�
 		Original Author:	�Ʒ� 
		Authors:
		Create Time:		2001/1/17
		Modify Time:		2001/9/12

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/
 
#ifndef _WINDSOUL_GEOMETRY_INTERNAL_H
#define _WINDSOUL_GEOMETRY_INTERNAL_H
  
struct WLineStruct : public WObjStruct, memory<WLineStruct> {
	int x;									// X ƫ��
	int y;									// Y ƫ��
	bool positive;
	WPixel color;							// ��ɫ
	int userdata;							// �û�����

	WLineStruct(int x,int y,WPixel color);
	WLineStruct() {}
	WLineStruct(const WLineStruct& line) { x=line.x,y=line.y,positive=line.positive,color=line.color,userdata=line.userdata; }
	using memory<WLineStruct>::operator new;
	using memory<WLineStruct>::operator delete;
	void *operator new(unsigned size,WObjectHeap *heap) { return WObjStruct::operator new(size,heap); }
#ifndef _BCB
	void operator delete(void *p,WObjectHeap *heap) {};
#endif    
	WLineStruct& operator=(const WLineStruct&box);		//�޴˺���
};  
  
inline WLineStruct::WLineStruct(int xx,int yy,WPixel color) : color(color) 
{
	if (xx>=0) kx=0,x=xx,positive=true;
	else kx=-xx,x=-xx,positive=false;
	if (yy>=0) ky=0,y=yy;
	else ky=-yy,y=-yy,positive=!positive;
}
 
struct WBoxStruct : public WObjStruct, memory<WBoxStruct> {
	int w;
	int h;
	int userdata;
	WPixel color;

	WBoxStruct(int w,int h,WPixel color) : w(w), h(h), color(color) { kx=ky=0; }
	WBoxStruct() {}
	WBoxStruct(const WBoxStruct &box) { w=box.w, h=box.h, userdata=box.userdata, color=box.color; }
	using memory<WBoxStruct>::operator new;
	using memory<WBoxStruct>::operator delete;
	void *operator new(unsigned size,WObjectHeap *heap) { return WObjStruct::operator new(size,heap); }
#ifndef _BCB
	void operator delete(void *p,WObjectHeap *heap) {};
#endif    
	WBoxStruct& operator=(const WBoxStruct&box);		//�޴˺���
};
 
#endif
