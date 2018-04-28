.model small
.data
	x db 0
	y db 0
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
	
	mov ah, 1h
	int 21h
	mov x, al
	sub x, '0'
	
	mov dx, offset msg1
	mov ah, 9h
	int 21h
	
	mov ah, 1h
	int 21h
	mov y, al
	sub y, '0'
	
	mov dx, offset msg2
	mov ah, 9h
	int 21h
	
	mov dl, x
	add dl, y
	add dl, '0'
	mov ah, 2h
	int 21h	
	
	mov dx, offset msg3
	mov ah, 9h
	int 21h
	
	mov dl, x
	sub dl, y
	add dl, '0'
	mov ah, 2h
	int 21h	
	
	mov ah, 4ch
	int 21h
end