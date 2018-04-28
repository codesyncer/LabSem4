.model small
.data
	n db 4
	r db 2
; ncr = n-1cr + n-1cr-1
.code
	mov ax, @data
	mov ds, ax
	
	mov bh, n
	mov bl, r
	call ncr
	
	mov bx, ax
	
	mov dl, al
	add dl, '0'
	mov ah, 2h
	int 21h
	
	mov ah, 4ch
	int 21h
	
ncr proc
	cmp bh, bl
	je ret1
	cmp bl, 0
	je ret1
	push bx
	dec bh
	call ncr
	push ax
	dec bl
	call ncr
	pop bx
	add ax, bx
	pop bx
	ret
ret1:
	mov ax, 1
	ret
ncr endp
end
