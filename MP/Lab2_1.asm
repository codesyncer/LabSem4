.model small
.data
	msg1 db 10,13,"Enter a digit: $"
	msg2 db 10,13,"Found @ index $"
	msg3 db 10,13,"Not Found!$"
	arr db "1242636$"
.code
	mov ax , @data
	mov ds, ax
	
	mov dx, offset msg1
	mov ah, 9h
	int 21h
	
	mov ah, 1h
	int 21h
	
	mov bl, al
	mov al, 0
	mov si, -1
	search:
		inc si
		mov bh, arr[si]
		cmp bh, '$'
		je outside
		cmp bh, bl
		jne search
		mov dx, offset msg2
		mov ah, 9h
		int 21h
		mov dx, si
		add dl, '0'
		mov ah, 2h
		int 21h
		mov al, 1
		jmp search
	outside:
	cmp al, 0
	jne eop
	
	mov dx, offset msg3
	mov ah, 9h
	int 21h	
	
	eop:
	mov ah, 4ch
	int 21h
end