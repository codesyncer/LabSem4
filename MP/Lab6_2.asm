.model small
.data
	str1 db 8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,'$'
	str db 10,'$'
.code
	mov ax, @data
	mov ds, ax
	
	start:
	mov ah, 2ah
	int 21h
	
	mov al, dl
	call dispNum
	
	mov dl, '/'
	call dispChar
	
	mov al, dh
	call dispNum
	
	mov dl, '/'
	call dispChar
	
	add cx, 0f830h
	mov al, cl
	call dispNum
	
	mov dl, ' '
	call dispChar
	
	mov ah, 2ch
	int 21h
	
	mov al, ch
	call dispNum
	
	mov ah, 2ch
	int 21h
	
	mov dl, ':'
	call dispChar
	
	mov al, cl
	call dispNum
	
	mov dl, ':'
	call dispChar
	
	mov al, dh
	call dispNum
	
	lea dx, str
	mov ah, 9h
	int 21h
	
	jmp start
	
	mov ah, 4ch
	int 21h

dispChar proc
	mov ah, 2h
	int 21h
	ret
dispChar endp

dispNum proc
	aam
	mov bx, ax
	add bx, 3030h
	mov dl, bh
	mov ah, 2h
	int 21h
	mov dl, bl
	mov ah, 2h
	int 21h
	ret
dispNum endp

end
