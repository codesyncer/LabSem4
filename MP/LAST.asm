.model small
.data
	menuText db 10,13,"1) CREATE   2) DELETE",10,13,"Enter the option: $"
	invalidText db 10,13,"INVALID$"
	filenameText db 10,13,"Enter the filename: $"
	errorText db 10,13,"ERROR$"
	buff db 100 dup(?)
.stack

.code
	mov ax, @data
	mov ds, ax
	
	call menu
	
	mov ah, 1h
	int 21h
	cmp al, '1'
	jne cmp2
	lea dx, filenameText
	mov ah, 9h
	int 21h
	call scans
	lea dx, buff
	mov ah, 3ch
	mov cx, 020h
	int 21h
	jmp exit
	cmp2:
	cmp al, '2'
	jne cmp3
	lea dx, filenameText
	mov ah, 9h
	int 21h
	call scans
	lea dx, buff
	mov ah, 41h
	int 21h
	jnc exit
	lea dx, errorText
	mov ah, 9h
	int 21h
	jmp exit
	cmp3:
	lea dx, invalidText
	mov ah, 9h
	int 21h
	
	exit:
	mov ah, 4ch
	int 21h
	
menu proc
	lea dx, menuText
	mov ah, 9h
	int 21h
	ret
menu endp

scans proc
	mov si, 0
	
	scanloop:
	mov ah, 1h
	int 21h
	cmp al, 0Dh
	je outscan
	mov buff[si], al
	inc si
	jmp scanloop
	
	outscan:
	mov buff[si], 0
	ret
scans endp
end
