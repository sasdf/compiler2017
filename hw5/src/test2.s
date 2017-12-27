	.arch armv8-a
	.file	"test2.c"
	.comm	g4,4,4
	.text
	.align	2
	.global	MAIN
	.type	MAIN, %function
MAIN:
	adrp	x0, g4
	add	x0, x0, :lo12:g4
	fmov	s0, 4.0e+0
	str	s0, [x0]
	adrp	x0, g4
	add	x0, x0, :lo12:g4
	ldr	s0, [x0]
	fcvtzs	w0, s0
	ret
	.size	MAIN, .-MAIN
	.ident	"GCC: (GNU) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
