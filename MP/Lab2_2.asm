.model small
.data
	pal_msg db "Palindrome$"
	not_msg db "Not $"
	nl_msg db 10,13,"$"
	stri db "ABBA$"
	rev db ?
.code
	mov ax , @data
	mov ds, ax
	
	mov dx, offset stri
	mov ah, 9h
	int 21h
	
	mov dx, offset nl_msg
	mov ah, 9h
	int 21h
	
	mov di, -1
	strlen:
		inc di
		cmp stri[di], '$'
		jne strlen
	dec di
	
	mov cx, di
	mov si, di
	mov di, 0
	loopi:
		mov dl, stri[si]
		mov rev[di], dl
		dec si
		inc di
		cmp si, 0
		jge loopi
	mov rev[di], '$'
	mov di, cx
	
	mov dx, offset rev
	mov ah, 9h
	int 21h
	
	
	mov dx, offset nl_msg
	mov ah, 9h
	int 21h
	
	mov si, 0
	scan:
		cmp si, di
		jge print_pal
		mov al, stri[si]
		cmp al, stri[di]
		jne print_not
		inc si
		dec di
		jmp scan
		
	print_not:
	mov dx, offset not_msg
	mov ah, 9h
	int 21h
	
	print_pal:
	mov dx, offset pal_msg
	mov ah, 9h
	int 21h
	
	mov ah, 4ch
	int 21h
end