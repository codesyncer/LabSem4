.model small
.data
	n db 10
	r db 5
; ncr = n-1cr + n-1cr-1
.code
	mov ax, @data
	mov ds, ax
	
	mov bh, n
	mov bl, r
	call ncr
	
	mov bx, ax
	
	mov cx, 0404h
	loopi:
		rol bx, cl
		mov dl, bl
		and dl, 0fh
		add dl, '0'
		mov ah, 2h
		int 21h
		dec ch
		cmp ch, 0
		jnz loopi	

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
	daa
	adc ah, 0
	xchg al, ah
	daa
	xchg al, ah
	pop bx
	ret
ret1:
	mov ax, 1
	ret
ncr endp
end
