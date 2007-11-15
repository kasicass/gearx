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
;		Description:		16λAlphaλͼ Blit
;		Original Author:	�Ʒ�
;		Authors:
;		Create Time:		2001/3/10
;		Modify Time:
;
;:*W*:._.:*I*:_.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:

[bits 32]

%include "c32.mac"
%include "wpp.inc"
%include "bmpclip.mac"

[section .text class=code use32]

; �� 16 λ Alpha λͼ bmp BLIT �� this λͼ��
;WSERR _stdcall _alpha_blit16(WBmpStruct *,const WAlphaBmpStruct *);
function _alpha_blit16
proc __alpha_blit16@8
	saveesi
	saveedi
	saveebx
	saveebp
%$this	arg
%$bmp	arg
%$w	locvar
%$h	locvar
%$w4	locvar
	endlocvar

	mov ebx,var(%$bmp)		; edx = bmp ָ��
	mov ecx,var(%$this)		; ���� this ָ��
	mov ebp,[ebx+WBmpStruct.ptr]	; ebp ΪԴͼָ��
	bmpclip	16			; ���ô���(16 bit)
					; ebx=bmp(Ŀ��)ָ��,ecx=this(Դ)ָ��
					; esi=Դ��ַ, edi=Ŀ���ַ
.blit:
	pcmpeqd mm6,mm6
	sub ebp,esi
	mov edx,[ecx+WBmpStruct.pitch]	; Ŀ��ͼ pitch
	neg ebp
	mov eax,var(%$w)
	shr ebp,1
	sub eax,4
	xor ecx,ecx
	mov var(%$w4),eax
	and eax,3
	add ebp,[ebx+WAlphaBmpStruct.channel]
	shl eax,4
	mov ebx,[ebx+WBmpStruct.pitch]	; Դͼ pitch
	movd mm5,eax
	sar ebx,1
	psllq mm6,mm5
	cld
	align 4
.loop:	
	mov eax,0x20202020
	cmp ecx,var(%$w)
	jl .loop_pixel
.nextline:
	xor ecx,ecx
	add ebp,ebx
	lea esi,[esi+ebx*2]
	add edi,edx
	dec dword var(%$h)
	jnz .loop
	emms
	jmp .end
.skip4pixel:
	add ecx,4
	jmp .loop
.loop_pixel:
	sub eax,[ebp+ecx]		; 32-alpha ֵ
	jz .4pixel
	cmp eax,0x20202020
	jz .skip4pixel
	pxor mm4,mm4
	movd mm7,eax
	movq mm0,[edi+ecx*2]		; Ŀ������
	punpcklbw mm7,mm4		; mm7 = 32-alpha ͨ��
	movq mm1,mm0
	movq mm4,mm0
	movq mm2,[mask_b]
	psrlw mm0,11			; mm0 = red
	pand mm2,mm4			; mm2 = blue
	pand mm1,[mask_g]		; mm1 = green
	pmullw mm0,mm7
	psrlw mm1,5
	pmullw mm2,mm7
	psllw mm0,6
	pmullw mm1,mm7
	psrlw mm2,5
;	psrlw mm1,3
	pand mm0,[mask_r]
	pand mm1,[mask_g]
	por mm0,mm2
	por mm0,mm1
	cmp ecx,var(%$w4)
	paddw mm0,[esi+ecx*2]
	jle .not_tail
.clip:
	pand mm4,mm6
	psubusw mm0,mm6
	por mm0,mm4
	movq [edi+ecx*2],mm0
	jmp .nextline
.4pixel:
	cmp ecx,var(%$w4)
	movq mm0,[esi+ecx*2]
	jle .neednotclip
	movq mm4,[edi+ecx*2]
	jmp .clip
.neednotclip:
	movq [edi+ecx*2],mm0
	add ecx,4
	jmp .loop
.not_tail:
	movq [edi+ecx*2],mm0
	add ecx,4
	jmp .loop
.end:	
	xor eax,eax
;	mov eax,var(%$this)		; ���� this ָ��
endproc

function _alpha_trans_blit16
proc __alpha_trans_blit16@8
	saveesi
	saveedi
	saveebx
	saveebp
%$this	arg
%$bmp	arg
%$w	locvar
%$h	locvar
%$w4	locvar
	endlocvar

	mov ebx,var(%$bmp)		; edx = bmp ָ��
	movd mm7,[ebx+WBmpStruct.data]
	mov ecx,var(%$this)		; this ָ��
	psrlw mm7,3
	mov ebp,[ebx+WBmpStruct.ptr]	; ebp ΪԴͼָ��
	bmpclip	16			; ���ô���(16 bit)
					; ebx=bmp(Ŀ��)ָ��,ecx=this(Դ)ָ��
					; esi=Դ��ַ, edi=Ŀ���ַ
.blit:
	punpcklwd mm7,mm7
	pcmpeqd mm6,mm6
	punpckldq mm7,mm7		; mm7=alpha
	sub ebp,esi
	mov edx,[ecx+WBmpStruct.pitch]	; Ŀ��ͼ pitch
	neg ebp
	mov eax,var(%$w)
	shr ebp,1
	sub eax,4
	xor ecx,ecx
	mov var(%$w4),eax
	and eax,3
	add ebp,[ebx+WAlphaBmpStruct.channel]
	shl eax,4
	mov ebx,[ebx+WBmpStruct.pitch]	; Դͼ pitch
	movd mm5,eax
	sar ebx,1
	psllq mm6,mm5
	cld
	movq [mask],mm6
	align 4
.loop:	
	cmp ecx,var(%$w)
	jl .loop_pixel
.nextline:
	xor ecx,ecx
	add ebp,ebx
	lea esi,[esi+ebx*2]
	add edi,edx
	dec dword var(%$h)
	jnz .loop
	emms
	jmp .end
.skip4pixel:
	add ecx,4
	jmp .loop
.loop_pixel:
	mov eax,[ebp+ecx]		; alpha ֵ
	test eax,eax
	jz .skip4pixel

	movd mm6,eax
	movq mm4,[solid]
	movq mm3,[edi+ecx*2]
	punpcklbw mm6,mm4
	movq mm0,[esi+ecx*2]		; Ŀ������
	pcmpeqw mm6,mm4
	movq mm4,mm3
	pand mm6,mm7			; mm6 = alpha
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
	movq mm3,[edi+ecx*2]
	psubw mm2,mm5
	pmullw mm1,mm6
	paddw mm0,mm3
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

	cmp ecx,var(%$w4)
	jle .not_tail
	pand mm3,[mask]
	psubusw mm0,[mask]
	por mm0,mm3
	movq [edi+ecx*2],mm0
	jmp .nextline
.not_tail:
	movq [edi+ecx*2],mm0
	add ecx,4
	jmp .loop
.end:	
	xor eax,eax
endproc

[section .data class=data use32]
mask_r	dd	0xf800f800,0xf800f800
mask_g	dd	0x07e007e0,0x07e007e0
mask_b	dd	0x001f001f,0x001f001f
solid	dd	0x20202020,0x20202020

[section .bss class=bss use32]
mask	resq	1