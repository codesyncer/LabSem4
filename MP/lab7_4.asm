.model small
.data
.code
	mov ax, @data
	mov ds, ax
	mov bh, '9'
	mov bl, '9'
	mov dl, '9'
	mov ah, 2h
	int 21h
	int 21h
	
	printLoop:
		mov cx, 799h
		loopi:
			push cx
			mov cx, 130h
			loopj:
			loop loopj
			pop cx
		loop loopi
		
		
		mov dl, 8
		mov ah, 2h
		int 21h
		
		mov ah, 3h
		int 10h
		mov ah, 2h
		mov dl, 01h
		int 10h
		
		mov dl, bl
		mov ah, 2h
		int 21h
		
		dec bl
		dec bl
		cmp bl, '0'
		jge printLoop
		dec bh
		cmp bh, '0'
		jl outside
		
		
		mov ah, 3h
		int 10h
		mov ah, 2h
		mov dl, 0h
		int 10h
		
		mov dl, 8
		mov ah, 2h
		int 21h
		int 21h
		
		mov dl, bh
		mov ah, 2h
		int 21h
		
		mov dl, '9'
		mov ah, 2h
		int 21h
		
		mov bl, '9'
		
		jmp printLoop
	outside:
	mov ah, 4ch
	int 21h
end