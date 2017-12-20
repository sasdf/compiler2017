	.arch armv8-a
	.file	"test.c"
	.comm	a,720,8
	.comm	b,4,4
	.comm	c,4,4
	.comm	d,4,4
	.comm	e,144,8
	.comm	f,4,4
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	sub	sp, sp, #4032
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	str	w0, [x29, 28]
	str	w1, [x29, 24]
	adrp	x0, __stack_chk_guard
	add	x0, x0, :lo12:__stack_chk_guard
	ldr	x1, [x0]
	str	x1, [x29, 4040]
	mov	x1,0
	fmov	s0, wzr
	adrp	x0, __stack_chk_guard
	add	x0, x0, :lo12:__stack_chk_guard
	ldr	x1, [x29, 4040]
	ldr	x0, [x0]
	eor	x0, x1, x0
	cmp	x0, 0
	beq	.L3
	bl	__stack_chk_fail
.L3:
	ldp	x29, x30, [sp], 16
	add	sp, sp, 4032
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
