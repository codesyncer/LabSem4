.model small
.data
	str1 db "9870651324$"
	cnt dw 10
.code
	mov ax , @data
	mov ds, ax
	
	mov cx, cnt
	loopi:
		mov si, 0
		loopj:
			inc si
			cmp si, cx
			jge outj
			mov ah, str1[si]
			cmp str1[si-1], ah
			jle loopj
			xchg str1[si-1], ah
			mov str1[si], ah
			jmp loopj
		outj:
	loop loopi
			
	lea dx, str1
	mov ah, 9h
	int 21h
	
	mov ah, 4ch
	int 21h
end