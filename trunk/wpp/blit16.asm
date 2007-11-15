;
;                ..;;;;,                     ;;;,    
;            ..;;;"` ;;:           ,;;;;;: ,;;;:.,;..          _/
;      ,;..,;;"`    :;;'            :;;"`,;;;;;;"":;;         _/ 
;      ;;;"  `:;;. ;;'           ..;;:  .;;,.;;:',;;"    _/_/_/_/_/
;     .;;`   ,;;" .;"          ,;;;;;;" :;`',;",;;"         _/
;    ,;;,:.,;;;  ,;:          :" ,;:` , `:.;;;;;'`         _/   
;    ;;"'':;;:. .;; .          ,;;;,;:;;,;;;, ,;             _/
;   :;;..;;;;;; :;' :.        :;;;"` `:;;;;;,;,.;.          _/
; .;;":;;`  '"";;:  ';;       '""   .;;`.;";:;;;;` ;,  _/_/_/_/_/
;;;;" `'       "::. ,;;:          .;"`  ::. '   .,;;;     _/ 
;""             ';;;;;;;"        ""     ';;;;;;;;;;`     _/
;
;                       Windsoul++
;
;               by �Ʒ� (Cloud Wu)  1999-2001
;
;       http://member.netease.com/~cloudwu 
;		mailto:cloudwu@263.net
; 
;		���Ķ� readme.txt �еİ�Ȩ��Ϣ
;		See readme.txt for copyright information.
;
;		Description:		16λλͼ Blit
;		Original Author:	�Ʒ�
;		Authors:
;		Create Time:		2000/9/23
;		Modify Time:		2001/3/10
;
;:*W*:._.:*I*:_.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:

[bits 32]

%include "c32.mac"
%include "wpp.inc"
%include "bmpclip.mac"

[section .text class=code use32]

; ��������, ���� Blit
function _back_blit16
function __back_blit16@8
	mov eax,[esp+4]
	mov ecx,[esp+8]
	mov [esp+8],eax
	mov [esp+4],ecx			; ���� ��������

; �� 16 λλͼ bmp BLIT �� this λͼ��
;WSERR _stdcall _blit(WBmpStruct *,const WBmpStruct *);
function _blit16
proc __blit16@8
	saveesi
	saveedi
	saveebx
%$this	arg
%$bmp	arg
%$w	locvar
%$h	locvar
	endlocvar

	mov ecx,var(%$this)		; ���� this ָ��
	mov ebx,var(%$bmp)		; edx = bmp ָ��
	bmpclip	16			; ���ô���(16 bit)
					; ebx=bmp(Դ)ָ��,ecx=this(Ŀ��)ָ��
					; esi=Դ��ַ, edi=Ŀ���ַ
.blit:
	mov eax,var(%$w)
	mov edx,[ecx+WBmpStruct.pitch]	; Ŀ��ͼ pitch
	add eax,eax
	mov ebx,[ebx+WBmpStruct.pitch]	; Դͼ pitch
	sub edx,eax
	sub ebx,eax
	mov ecx,var(%$w)
	mov eax,var(%$h)
	cld
	align 4
.loop:	
	sub ecx,4
	jle .nextline 
	movq mm0,[esi]
	add esi,8
	movq [edi],mm0
	add edi,8
	jmp .loop
.nextline:
	add ecx,4
	rep movsw
	add esi,ebx
	add edi,edx
	mov ecx,var(%$w)
	dec eax
	jnz .loop
	emms
.end:	
	xor eax,eax
;	mov eax,var(%$this)		; ���� this ָ��
endproc

;WSERR _stdcall _clear16(WBmpStruct* bmp,WPixel color);
; ��λͼ��λ color ɫ
function _clear16
proc __clear16@8
	saveesi
	saveedi
%$this	arg
%$color	arg
	endlocvar

	mov ecx,var(%$this)		; ���� this ָ��
	mov esi,[ecx+WBmpStruct.w]
	mov edi,[ecx+WBmpStruct.ptr]
	test esi,esi
	jnz .can_blit
	mov eax,ecx			; ���Ϊ 0, ���� blit
	jmp .end
.can_blit:
	mov eax,var(%$color)
	mov edx,[ecx+WBmpStruct.pitch]
	movd mm0,eax
	add esi,esi
	punpcklwd mm0,mm0
	sub edx,esi			; edx Ϊ�м��
	punpckldq mm0,mm0
	cld
	mov esi,[ecx+WBmpStruct.h]		; esi Ϊ�߶�
	movd mm2,[ecx+WBmpStruct.w]	; mm2 Ϊ���
	test esi,esi
	jz .blit_end
	movd ecx,mm2
	align 4
.loop:
	sub ecx,4
	jle .nextline
	movq [edi],mm0
	add edi,8
	jmp .loop
.nextline:
	add ecx,4
	rep stosw
	add edi,edx
	movd ecx,mm2
	dec esi
	jnz .loop
.blit_end:
	xor eax,eax
;	mov eax,var(%$this)		; ���� this ָ��
	emms
.end:	
endproc

; �� 16 λλͼ bmp BLIT �� this λͼ�� (���͸��ɫ)
;WSERR _stdcall _mask_blit(WBmpStruct *,const WBmpStruct *);
function _mask_blit16
proc __mask_blit16@8
	saveesi
	saveedi
	saveebx
%$this	arg
%$bmp	arg
%$w	locvar
%$h	locvar
	endlocvar

	mov ecx,var(%$this)		; ���� this ָ��
	mov ebx,var(%$bmp)		; edx = bmp ָ��
	bmpclip	16			; ���ô���(16 bit)
					; ebx=bmp(Դ)ָ��,ecx=this(Ŀ��)ָ��
					; esi=Դ��ַ, edi=Ŀ���ַ
.blit:
	mov eax,var(%$w)
	mov edx,[ecx+WBmpStruct.pitch]	; Ŀ��ͼ pitch
	add eax,eax
	mov ebx,[ebx+WBmpStruct.pitch]	; Դͼ pitch
	sub edx,eax
	sub ebx,eax
	mov ecx,var(%$w)
	cld
	movq mm7,[mask]			; mm7 Ϊ��ɫ
	xor eax,eax
	align 4
.loop:	
	sub ecx,4
	jle .nextline 

	movq mm0,[esi]
	add esi,8
	movq mm1,mm0
	pcmpeqw mm0,mm7
	psubusw mm1,mm0
	pand mm0,[edi]
	por mm0,mm1
	movq [edi],mm0
	add edi,8
	jmp .loop
.nextline:
	add ecx,4
.looptail:
	lodsw
	cmp eax,0xf81f
	jz .skip_pixel
	mov [edi],ax
.skip_pixel:
	add edi,2
	dec ecx
	jnz .looptail
	add esi,ebx
	add edi,edx
	mov ecx,var(%$w)
	dec dword var(%$h)
	jnz .loop
	emms
.end:	
	xor eax,eax
;	mov eax,var(%$this)		; ���� this ָ��
endproc

function _additive_blit16
proc __additive_blit16@8
	saveesi
	saveedi
	saveebx
%$this	arg
%$bmp	arg
%$w	locvar
%$h	locvar
	endlocvar

	mov ecx,var(%$this)		; ���� this ָ��
	mov ebx,var(%$bmp)		; edx = bmp ָ��
	bmpclip	16			; ���ô���(16 bit)
					; ebx=bmp(Դ)ָ��,ecx=this(Ŀ��)ָ��
					; esi=Դ��ַ, edi=Ŀ���ַ
.blit:
	mov eax,var(%$w)
	mov edx,[ecx+WBmpStruct.pitch]	; Ŀ��ͼ pitch
	add eax,eax
	mov ebx,[ebx+WBmpStruct.pitch]	; Դͼ pitch
	sub edx,eax
	sub ebx,eax
	mov ecx,eax
	pcmpeqb mm7,mm7
	shr ecx,3
	cld
	and eax,7
	jnz .notzero
	mov eax,8
	dec ecx
.notzero:
	shl eax,3
	movd mm6,eax
	shr eax,3
	psllq mm7,mm6
	mov var(%$w),ecx
	add ebx,eax
	add edx,eax
	align 4
.loop:	
	dec ecx
	jl .nextline 
	movq mm0,[esi]
	movq mm3,[edi]
	movq mm1,mm0
	movq mm2,mm0
	movq mm4,mm3
	movq mm5,mm3
	psllw mm1,5
	psllw mm4,5
	psllw mm2,11
	psllw mm5,11
	paddusw mm0,mm3			; ��ɫ��
	paddusw mm1,mm4			; ��ɫ��
	paddusw mm2,mm5			; ��ɫ��
	psrlw mm1,5                                     
	psrlw mm2,11                                    
	pand mm0,[mask_r]
	pand mm1,[mask_g]
	por mm0,mm2
	por mm0,mm1
	add esi,8
	movq [edi],mm0
	add edi,8
	jmp .loop
.nextline:
	movq mm0,[esi]
	psubusb mm0,mm7
	movq mm3,[edi]
	movq mm1,mm0
	movq mm2,mm0
	movq mm4,mm3
	movq mm5,mm3
	psllw mm1,5
	psllw mm4,5
	psllw mm2,11
	psllw mm5,11
	paddusw mm0,mm3			; ��ɫ��
	paddusw mm1,mm4			; ��ɫ��
	paddusw mm2,mm5			; ��ɫ��
	psrlw mm1,5                                     
	psrlw mm2,11                                    
	pand mm0,[mask_r]
	pand mm1,[mask_g]
	por mm0,mm2
	por mm0,mm1
	add esi,ebx
	movq [edi],mm0
	add edi,edx
	mov ecx,var(%$w)
	dec dword var(%$h)
	jz .loop_end
	jmp .loop
.loop_end:
	emms
.end:	
	xor eax,eax
;	mov eax,var(%$this)		; ���� this ָ��
endproc

function _subtract_blit16
proc __subtract_blit16@8
	saveesi
	saveedi
	saveebx
%$this	arg
%$bmp	arg
%$w	locvar
%$h	locvar
	endlocvar

	mov ecx,var(%$this)		; ���� this ָ��
	mov ebx,var(%$bmp)		; edx = bmp ָ��
	bmpclip	16			; ���ô���(16 bit)
					; ebx=bmp(Դ)ָ��,ecx=this(Ŀ��)ָ��
					; esi=Դ��ַ, edi=Ŀ���ַ
.blit:
	mov eax,var(%$w)
	mov edx,[ecx+WBmpStruct.pitch]	; Ŀ��ͼ pitch
	add eax,eax
	mov ebx,[ebx+WBmpStruct.pitch]	; Դͼ pitch
	sub edx,eax
	sub ebx,eax
	mov ecx,eax
	pcmpeqb mm7,mm7
	shr ecx,3
	cld
	and eax,7
	jnz .notzero
	mov eax,8
	dec ecx
.notzero:
	shl eax,3
	movd mm6,eax
	shr eax,3
	psllq mm7,mm6
	mov var(%$w),ecx
	add ebx,eax
	add edx,eax
	align 4
.loop:	
	dec ecx
	jl .nextline 
	movq mm0,[edi]
	movq mm3,[esi]
	movq mm1,mm0
	movq mm2,mm0
	movq mm4,mm3
	movq mm5,mm3
	psllw mm1,5
	psllw mm4,5
	psllw mm2,11
	psllw mm5,11
	psubusw mm0,mm3			; ��ɫ��
	psubusw mm1,mm4			; ��ɫ��
	psubusw mm2,mm5			; ��ɫ��
	psrlw mm1,5                                     
	psrlw mm2,11                                    
	pand mm0,[mask_r]
	pand mm1,[mask_g]
	por mm0,mm2
	por mm0,mm1
	add esi,8
	movq [edi],mm0
	add edi,8
	jmp .loop
.nextline:
	movq mm3,[esi]
	movq mm0,[edi]
	psubusb mm3,mm7
	movq mm1,mm0
	movq mm2,mm0
	movq mm4,mm3
	movq mm5,mm3
	psllw mm1,5
	psllw mm4,5
	psllw mm2,11
	psllw mm5,11
	psubusw mm0,mm3			; ��ɫ��
	psubusw mm1,mm4			; ��ɫ��
	psubusw mm2,mm5			; ��ɫ��
	psrlw mm1,5                                     
	psrlw mm2,11                                    
	pand mm0,[mask_r]
	pand mm1,[mask_g]
	por mm0,mm2
	por mm0,mm1
	add esi,ebx
	movq [edi],mm0
	add edi,edx
	mov ecx,var(%$w)
	dec dword var(%$h)
	jz .loop_end
	jmp .loop
.loop_end:
	emms
.end:	
	xor eax,eax
;	mov eax,var(%$this)		; ���� this ָ��
endproc

function _trans_blit16
proc __trans_blit16@8
	saveesi
	saveedi
	saveebx
%$this	arg
%$bmp	arg
%$w	locvar
%$h	locvar
	endlocvar

	mov ebx,var(%$bmp)		; edx = bmp ָ��
	mov ecx,var(%$this)		; this ָ��
	bmpclip	16			; ���ô���(16 bit)
					; ebx=bmp(Դ)ָ��,ecx=this(Ŀ��)ָ��
					; esi=Դ��ַ, edi=Ŀ���ַ
.blit:
	mov eax,0x1000100
	movd mm5,[ebx+WBmpStruct.data]
	movd mm7,eax
	punpcklwd mm5,mm5
	punpckldq mm7,mm7
	punpckldq mm5,mm5		; mm5=alpha
	movq mm6,mm7			; mm6=mm7= 0x100 0100 0100 0100
	mov eax,var(%$w)
	mov edx,[ecx+WBmpStruct.pitch]	; Ŀ��ͼ pitch
	add eax,eax
	mov ebx,[ebx+WBmpStruct.pitch]	; Դͼ pitch
	sub edx,eax
	sub ebx,eax
	mov ecx,eax
	pcmpeqb mm0,mm0
	shr ecx,3
	cld
	and eax,7
	jnz .notzero
	mov eax,8
	dec ecx
.notzero:
	shl eax,3
	movd mm4,eax
	shr eax,3
	psllq mm0,mm4
	mov var(%$w),ecx
	pandn mm0,mm5
	add ebx,eax
	psubw mm6,mm0
	psubw mm7,mm5
	psrlw mm6,3
	psrlw mm7,3
	add edx,eax
	align 4
.loop:	
	dec ecx
	jge .blend4
	jmp .nextline
.blend4:
	movq mm3,[esi]
	movq mm0,[edi]
	movq mm4,mm3
	movq mm5,mm3
	psrlw mm3,5
	pand mm4,[mask_g]
	pand mm5,[mask_b]
	movq mm1,mm0
	movq mm2,mm0
	psrlw mm0,5
	pand mm1,[mask_g]
	pand mm2,[mask_b]
	psubw mm0,mm3
	psubw mm1,mm4
	pmullw mm0,mm7
	psubw mm2,mm5
	pmullw mm1,mm7
	paddw mm0,[esi]
	pmullw mm2,mm7
	psrlw mm1,5
	psrlw mm2,5
	paddw mm1,mm4
	paddw mm2,mm5
	pand mm0,[mask_r]
	pand mm1,[mask_g]
	pand mm2,[mask_b]
	por mm0,mm1
	por mm0,mm2
	add esi,8
	movq [edi],mm0
	add edi,8
	jmp .loop
.nextline:
	movq mm3,[esi]
	movq mm0,[edi]
	movq mm4,mm3
	movq mm5,mm3
	psrlw mm3,5
	pand mm4,[mask_g]
	pand mm5,[mask_b]
	movq mm1,mm0
	movq mm2,mm0
	psrlw mm0,5
	pand mm1,[mask_g]
	pand mm2,[mask_b]
	psubw mm0,mm3
	psubw mm1,mm4
	pmullw mm0,mm6
	psubw mm2,mm5
	pmullw mm1,mm6
	paddw mm0,[esi]
	pmullw mm2,mm6
	psrlw mm1,5
	psrlw mm2,5
	paddw mm1,mm4
	paddw mm2,mm5
	pand mm0,[mask_r]
	pand mm1,[mask_g]
	pand mm2,[mask_b]
	por mm0,mm1
	por mm0,mm2
	add esi,ebx
	movq [edi],mm0
	add edi,edx
	mov ecx,var(%$w)
	dec dword var(%$h)
	jz .end
	jmp .loop
.end:	
	emms
	xor eax,eax
;	mov eax,var(%$this)		; ���� this ָ��
endproc

function _mask_trans_blit16
proc __mask_trans_blit16@8
	saveesi
	saveedi
	saveebx
%$this	arg
%$bmp	arg
%$w	locvar
%$h	locvar
	endlocvar

	mov ebx,var(%$bmp)		; edx = bmp ָ��
	mov ecx,var(%$this)		; this ָ��
	bmpclip	16			; ���ô���(16 bit)
					; ebx=bmp(Դ)ָ��,ecx=this(Ŀ��)ָ��
					; esi=Դ��ַ, edi=Ŀ���ַ
.blit:
	mov eax,0x1000100
	movd mm5,[ebx+WBmpStruct.data]
	movd mm7,eax
	punpcklwd mm5,mm5
	punpckldq mm7,mm7
	punpckldq mm5,mm5		; mm5=alpha
	movq mm6,mm7			; mm6=mm7= 0x100 0100 0100 0100
	mov eax,var(%$w)
	mov edx,[ecx+WBmpStruct.pitch]	; Ŀ��ͼ pitch
	add eax,eax
	mov ebx,[ebx+WBmpStruct.pitch]	; Դͼ pitch
	sub edx,eax
	sub ebx,eax
	mov ecx,eax
	pcmpeqb mm0,mm0
	shr ecx,3
	cld
	and eax,7
	jnz .notzero
	mov eax,8
	dec ecx
.notzero:
	shl eax,3
	movd mm4,eax
	shr eax,3
	psllq mm0,mm4
	mov var(%$w),ecx
	pandn mm0,mm5
	add ebx,eax
	psubw mm6,mm0
	psubw mm7,mm5
	psrlw mm6,3
	psrlw mm7,3
	add edx,eax
	paddusw mm7,[xffdf]
	paddusw mm6,[xffdf]
	movq [alpha],mm7
	movq [mask_alpha],mm6
	align 4
.loop:	
	dec ecx
	jge .blend4
	jmp .nextline
.blend4:
	movq mm1,[mask]
	movq mm3,[esi]
	movq mm0,[edi]
	movq mm7,[alpha]
	pcmpeqw mm1,mm3
	movq mm4,mm3
	paddusw mm7,mm1
	movq mm5,mm3
	psubusw mm7,[xffdf]

	psrlw mm3,5
	pand mm4,[mask_g]
	pand mm5,[mask_b]
	movq mm1,mm0
	movq mm2,mm0
	psrlw mm0,5
	pand mm1,[mask_g]
	pand mm2,[mask_b]
	psubw mm0,mm3
	psubw mm1,mm4
	pmullw mm0,mm7
	psubw mm2,mm5
	pmullw mm1,mm7
	paddw mm0,[esi]
	pmullw mm2,mm7
	psrlw mm1,5
	psrlw mm2,5
	paddw mm1,mm4
	paddw mm2,mm5
	pand mm0,[mask_r]
	pand mm1,[mask_g]
	pand mm2,[mask_b]
	por mm0,mm1
	por mm0,mm2
	add esi,8
	movq [edi],mm0
	add edi,8
	jmp .loop
.nextline:
	movq mm1,[mask]
	movq mm3,[esi]
	movq mm0,[edi]
	movq mm6,[mask_alpha]
	pcmpeqw mm1,mm3
	movq mm4,mm3
	paddusw mm6,mm1
	movq mm5,mm3
	psubusw mm6,[xffdf]

	psrlw mm3,5
	pand mm4,[mask_g]
	pand mm5,[mask_b]
	movq mm1,mm0
	movq mm2,mm0
	psrlw mm0,5
	pand mm1,[mask_g]
	pand mm2,[mask_b]
	psubw mm0,mm3
	psubw mm1,mm4
	pmullw mm0,mm6
	psubw mm2,mm5
	pmullw mm1,mm6
	paddw mm0,[esi]
	pmullw mm2,mm6
	psrlw mm1,5
	psrlw mm2,5
	paddw mm1,mm4
	paddw mm2,mm5
	pand mm0,[mask_r]
	pand mm1,[mask_g]
	pand mm2,[mask_b]
	por mm0,mm1
	por mm0,mm2

	add esi,ebx
	movq [edi],mm0
	add edi,edx
	mov ecx,var(%$w)
	dec dword var(%$h)
	jz .end
	jmp .loop
.end:	
	emms
	xor eax,eax
;	mov eax,var(%$this)		; ���� this ָ��
endproc

[section .data class=data use32]
mask	dd	0xf81ff81f,0xf81ff81f
xffdf	dd	0xffdfffdf,0xffdfffdf
mask_r	dd	0xf800f800,0xf800f800
mask_g	dd	0x07e007e0,0x07e007e0
mask_b	dd	0x001f001f,0x001f001f

[section .bss class=bss use32]
alpha	resq	1
mask_alpha	resq	1
