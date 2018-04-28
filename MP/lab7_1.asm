.model small
.data
.code
	mov ax, @data
	mov ds, ax
	mov bh, '0'
	mov bl, '0'
	mov dl, '0'
	mov ah, 2h
	int 21h
	;int 21h
	
	printLoop:
		mov cx, 799h
		loopi:
			push cx
			mov cx, 130h
			loopj:
			loop loopj
			pop cx
		loop loopi
		
		;mov dl, 8
		;mov ah, 2h
		;int 21h
		
		mov ah, 3h
		int 10h
		mov ah, 2h
		mov dl, 01h
		int 10h
		
		mov dl, bl
		mov ah, 2h
		int 21h
		
		
		inc bl
		cmp bl, 58
		jl printLoop
		inc bh
		cmp bh, 58
		jge outside
		
		mov ah, 3h
		int 10h
		mov ah, 2h
		mov dl, 00h
		int 10h
		
		;mov dl, 8
		;mov ah, 2h
		;int 21h
		;int 21h
		
		mov dl, bh
		mov ah, 2h
		int 21h
		
		;mov dl, '0'
		;mov ah, 2h
		;int 21h
		
		mov bl, '0'
		
		jmp printLoop
	outside:
	mov ah, 4ch
	int 21h
end