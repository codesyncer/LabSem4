.model small
.data
	x dw 0
	y dw 20
	ten db 10
	ans db 0
	msg1 db 10,13,"Enter a number: $"
	msg2 db 10,13,"Sum: $"
	msg3 db 10,13,"Sub: $"
	
.code
	mov ax , @data
	mov ds, ax

	mov dx, offset msg1
	mov ah, 9h
	int 21h

	read1:
		mov ah, 1h
		int 21h
		cmp al, 13
		je outside1
		sub al, '0'
		mov bl, al
		mov ax, x
		mul ten
		add al, bl
		mov x, ax
		jmp read1
	outside1:
	
	mov dx, offset msg1
	mov ah, 9h
	int 21h

	read2:
		mov ah, 1h
		int 21h
		cmp al, 13
		je outside2
		sub al, '0'
		mov bl, al
		mov ax, y
		mul ten
		add al, bl
		mov y, ax
		jmp read2
	outside2:
	
	
	mov ax, x
	sub ax, y
	mov dl, al
	add dl, '0'
	mov ah, 2h
	int 21h
	
	mov ah, 4ch
	int 21h
end