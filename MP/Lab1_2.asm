.model small
.data
	x dw 1190h
	y dw 2222h
.code
	mov ax , @data
	mov ds, ax

	mov ax, x
	add ax, y
	
	daa
	adc ah, 0
	mov bl, al
	mov al, ah
	daa
	mov bh, al
	mov ax, bx
	
	mov cl, 4
	mov ch, 4
	loopi:
		rol ax, cl
		mov bx, ax
		and al, 0fh
		mov dl, al
		add dl, '0'
		mov ah, 2h
		int 21h
		mov ax, bx
		dec ch
		cmp ch, 0
		jnz loopi	
	
	mov ah, 4ch
	int 21h
end