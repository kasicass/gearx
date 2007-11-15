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

		Description:		�� TGA λͼ
 		Original Author:	�Ʒ�
		Authors:
		Create Time:		2001/3/10
		Modify Time:		2001/12/21

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include "windsoul.h"
//#include "bmpint.h"
//#include "achannel.h"
#include "wsalpha.h"
#define new debug_new

#pragma pack (push)
#pragma pack (1)

struct TGAFILEHEADER{
	BYTE bIDLength;						//������Ϣ����
	BYTE bPalType;						//��ɫ����Ϣ(��֧��)
	BYTE bImageType;					//ͼ������(ֻ֧�� 3,10)
	WORD wPalIndex;						//��ɫ���һ������ֵ
	WORD wPalLength;					//��ɫ��������
	BYTE bPalBits;						//һ����ɫ�嵥λλ��(15,16,24,32)
	WORD wLeft;							//ͼ���������(��������)
	WORD wBottom;						//ͼ��׶�����(��������)
	WORD wWidth;						//ͼ����
	WORD wHeight;						//ͼ��߶�
	BYTE bBits;							//һ������λ��
	BYTE bAlphaBits:4;					//Alphaλ��
	BYTE bReserved:1;					//����,����Ϊ0
	BYTE bTopDown:1;					//Ϊ1��ʾ���ϵ���(ֻ֧�ִ��µ���)
	BYTE bInterleaving:2;				//����(һ��Ϊ0)
};

#pragma pack (pop)

WSERR WAlphaBitmap::LoadTGA(const void *tgadata)
{
	DWORD dataptr;
	WPixel *line;
	BYTE *alpha_line;
	int i,j,width,height,ii;
	TGAFILEHEADER *head=(TGAFILEHEADER *)tgadata;
	if ((head->bImageType!=2 && head->bImageType!=10)
		|| head->bBits!=32 || head->bInterleaving!=0) {
		if (head->bBits==24) {
			// û��ͨ��
			if (objdata!=0) Destroy();
			Create(width=(int)head->wWidth,height=(int)head->wHeight);
			dataptr=(DWORD)tgadata+sizeof(TGAFILEHEADER)+head->bIDLength;
			if (head->bImageType==2) {
				// ��ѹ��, �ѵ�ǰ������byte�����ʲô�ؼ�����?
				int rr=0,gg=0,bb=0;
				bb=*(BYTE*)dataptr;
				gg=*(BYTE*)(dataptr+1);
				rr=*(BYTE*)(dataptr+2);
				for (ii=height-1;ii>=0;ii--) {
					if (head->bTopDown) i=height-1-ii;
					else i=ii;
					line=(*this)[i];
					alpha_line=ChannelLine(i);
					for (j=0;j<width;j++) {
						int red,green,blue;
		//				line[j]=*(DWORD *)dataptr;
						blue=*(BYTE*)dataptr++;
						green=*(BYTE*)dataptr++;
						red=*(BYTE*)dataptr++;
						if (red==rr && green==gg && blue==bb)
							line[j].color=0,alpha_line[j]=0;
						else {
							line[j]=WPixel(red,green,blue);
							alpha_line[j]=32;
						}
					}
				}
			}
			else {
				// RLE ѹ��
				int run=0,raw=0;
				WPixel runpixel;
				int runalpha;
				int red,green,blue;
				int rr,gg,bb;
				bb=*(BYTE*)(dataptr+1);
				gg=*(BYTE*)(dataptr+2);
				rr=*(BYTE*)(dataptr+3);
				for (ii=height-1;ii>=0;ii--) {
					if (head->bTopDown) i=height-1-ii;
					else i=ii;
					line=(*this)[i];
					alpha_line=ChannelLine(i);
					for (j=0;j<width;) {
						if (run>0) {
							line[j]=runpixel,alpha_line[j]=runalpha,--run;
							++j;
						}
						else if (raw>0) {
		//					line[j]=*(DWORD *)dataptr;
							blue=*(BYTE*)dataptr++;
							green=*(BYTE*)dataptr++;
							red=*(BYTE*)dataptr++;
							if (red==rr && green==gg && blue==bb)
								line[j].color=0,alpha_line[j]=0;
							else {
								line[j]=WPixel(red,green,blue);
								alpha_line[j]=32;
							}
							--raw;
							++j;
						}
						else {
							BYTE packhead=*(BYTE*)dataptr++;
							if (packhead&0x80) {
								run=(packhead&0x7f)+1;

								blue=*(BYTE*)dataptr++;
								green=*(BYTE*)dataptr++;
								red=*(BYTE*)dataptr++;
								if (red==rr && green==gg && blue==bb)
									runpixel.color=0,runalpha=0;
								else {
									runpixel=WPixel(red,green,blue);
									runalpha=32;
								}
							}
							else {
								raw=packhead+1;
							}
						}
					}
				}
			}
			return WS_OK;
		}
		return WS_INVALIDBMPTYPE;
	}
	if (objdata!=0) Destroy();
	Create(width=(int)head->wWidth,height=(int)head->wHeight);
	dataptr=(DWORD)tgadata+sizeof(TGAFILEHEADER)+head->bIDLength;
	if (head->bImageType==2) {
// ��ѹ��
		int rr=0,gg=0,bb=0;
		if ((*(BYTE*)(dataptr+3))==0) {
			bb=*(BYTE*)dataptr;
			gg=*(BYTE*)(dataptr+1);
			rr=*(BYTE*)(dataptr+2);
		}
		for (ii=height-1;ii>=0;ii--) {
			if (head->bTopDown) i=height-1-ii;
			else i=ii;
			line=(*this)[i];
			alpha_line=ChannelLine(i);
			for (j=0;j<width;j++) {
				int red,green,blue,alpha;
//				line[j]=*(DWORD *)dataptr;
				blue=*(BYTE*)dataptr++;
				green=*(BYTE*)dataptr++;
				red=*(BYTE*)dataptr++;
				alpha=*(BYTE*)dataptr++;
				if (alpha==0) {
					line[j]=0;
				}
				else {
					if (alpha<255) {
						red-=rr*(256-alpha)/256;
						green-=gg*(256-alpha)/256;
						blue-=bb*(256-alpha)/256;
						red=MAX(0,MIN(alpha,red));
						green=MAX(0,MIN(alpha,green));
						blue=MAX(0,MIN(alpha,blue));
						alpha=(alpha+7)/8;
					}
					else alpha=32;
					line[j]=WPixel(red,green,blue);
				}
//				alpha=MAX(MAX(MAX(red,green),blue),alpha);
				alpha_line[j]=alpha;
			}
		}
	}
	else {
// RLE ѹ��
		int run=0,raw=0;
		WPixel runpixel;
		int runalpha;
		int red,green,blue,alpha;
		int rr=0,gg=0,bb=0;
		if ((*(BYTE*)(dataptr+4))==0) {
			bb=*(BYTE*)(dataptr+1);
			gg=*(BYTE*)(dataptr+2);
			rr=*(BYTE*)(dataptr+3);
		}
		for (ii=height-1;ii>=0;ii--) {
			if (head->bTopDown) i=height-1-ii;
			else i=ii;

			line=(*this)[i];
			alpha_line=ChannelLine(i);
			for (j=0;j<width;) {
				if (run>0) {
					line[j]=runpixel,alpha_line[j]=runalpha,--run;
					++j;
				}
				else if (raw>0) {
//					line[j]=*(DWORD *)dataptr;
					blue=*(BYTE*)dataptr++;
					green=*(BYTE*)dataptr++;
					red=*(BYTE*)dataptr++;
					alpha=*(BYTE*)dataptr++;
					if (alpha==0) {
						line[j]=0;
					}
					else {
						if (alpha<255) {
							red-=rr*(256-alpha)/256;
							green-=gg*(256-alpha)/256;
							blue-=bb*(256-alpha)/256;
							red=MAX(0,MIN(alpha,red));
							green=MAX(0,MIN(alpha,green));
							blue=MAX(0,MIN(alpha,blue));
							alpha=(alpha+7)/8;
						}
						else alpha=32;
						line[j]=WPixel(red,green,blue);
					}
					alpha_line[j]=alpha;
					--raw;
					++j;
				}
				else {
					BYTE packhead=*(BYTE*)dataptr++;
					if (packhead&0x80) {
						run=(packhead&0x7f)+1;

						blue=*(BYTE*)dataptr++;
						green=*(BYTE*)dataptr++;
						red=*(BYTE*)dataptr++;
						runalpha=*(BYTE*)dataptr++;
						if (runalpha==0) runpixel=0;
						else {
							if (runalpha<255) {
								red-=rr*(256-runalpha)/256;
								green-=gg*(256-runalpha)/256;
								blue-=bb*(256-runalpha)/256;
								red=MAX(0,MIN(runalpha,red));
								green=MAX(0,MIN(runalpha,green));
								blue=MAX(0,MIN(runalpha,blue));
								runalpha=(runalpha+7)/8;
							}
							else {
								runalpha=32;
							}
							runpixel=WPixel(red,green,blue);
						}
					}
					else {
						raw=packhead+1;
					}
				}
			}
		}
	}

	return WS_OK;
}

#include <stdio.h>
#include <malloc.h>
#include <string.h>

WSERR WAlphaBitmap::SaveTGA(const char *filename) const
{
	FILE *f;
	f=fopen(filename,"wb");
	if (f==0)
		return WS_CANTOPEN;
	int i,j;
	TGAFILEHEADER head;
	memset(&head,0,sizeof(TGAFILEHEADER));
	head.bImageType=2;	// ��ѹ��
	head.bBits=32;		// 32bit
	head.wWidth=GetW();
	head.wHeight=GetH();
	head.bAlphaBits=8;

	fwrite(&head,1,sizeof(head),f);
	DWORD *line=(DWORD*)_alloca(GetW()*4);
	WPixel *data_line;
	BYTE *channel_line;

// ��ѹ��
	for (i=GetH()-1;i>=0;i--) {
		data_line=operator[](i);
		channel_line=ChannelLine(i);
		for (j=0;j<GetW();j++,++data_line,++channel_line) {
			int r,g,b;
			r=data_line->red;
			if (r>0) r=(r<<3|0x7)<<16;
			g=data_line->green;
			if (g>0) g=(g<<2|0x3)<<8;
			b=data_line->blue;
			if (b>0) b=(b<<3|0x7);
//			line[j]=(DWORD)(*data_line)|(*channel_line<<24);
			line[j]=(DWORD)r|g|b|(*channel_line<<24);
		}
		fwrite(line,GetW()*4,1,f);
	}
	fclose(f);
	return WS_OK;
}
