PUBLIC getfs
PUBLIC getgs
PUBLIC getfs2c
PUBLIC getgs58
PUBLIC get_tls_vars_ptr

_TEXT SEGMENT
getfs proc
	mov rax, FS
	ret
getfs endp
_TEXT ENDS

_TEXT SEGMENT
getgs proc
	mov rax, GS
	ret
getgs endp
_TEXT ENDS

_TEXT SEGMENT
getfs2c proc
	mov rax, FS:[02ch]
	ret
getfs2c endp
_TEXT ENDS

_TEXT SEGMENT
getgs58 proc
	mov rax, GS:[058h]
	ret
getgs58 endp
_TEXT ENDS

_TEXT SEGMENT
get_tls_vars_ptr proc
	mov rax, GS:[058h]
	mov rax, [rax]
	add rax, rcx
	ret
get_tls_vars_ptr endp
_TEXT ENDS

end
