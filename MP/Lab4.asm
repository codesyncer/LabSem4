.model small
.data
	str2 db "Strin1g$"
	str1 db "String2$"
	not_msg db "Not $"
	equal_msg db "Equal Strings!$"
	msg1 db "Length equal!",10,13,"$"
	msg2 db "Length not equal!",10,13,"$"
.code
	mov ax , @data
	mov ds, ax
	
	mov si, 0
	len1:
		mov ah, str1[si]
		inc si
		cmp ah, '$'
		jne len1
	
	mov di, 0
	len2:
		mov ah, str2[di]
		inc di
		cmp ah, '$'
		jne len2

	cmp si, di
	jne len_not_eq
	lea dx, msg1
	mov ah, 9h
	int 21h
	
	mov si, -1
	
	cmpare:
		inc si
		mov ah, str1[si]
		mov al, str2[si]
		cmp ah, '$'
		je eos1
		cmp ah, al
		je cmpare
		jmp not_eq
		; End of str1

		eos1:
		cmp al, '$'
		je equal
		jmp not_eq
		
	len_not_eq:
		lea dx, msg2
		mov ah, 9h
		int 21h
		
	not_eq:
		lea dx, not_msg
		mov ah, 9h
		int 21h
		
	equal:
		lea dx, equal_msg
		mov ah, 9h
		int 21h
		
	; End of program	
	eop:
	mov ah, 4ch
	int 21h
end