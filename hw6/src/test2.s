	.arch armv8-a
	.file	"test2.c"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	sub	sp, sp, #48
	str	w0, [sp, 28]
	str	w1, [sp, 24]
	str	w2, [sp, 20]
	str	w3, [sp, 16]
	str	w4, [sp, 12]
	ldr	w0, [sp, 28]
	cmp	w0, 0
	bne	.L2
	ldr	w0, [sp, 24]
	cmp	w0, 0
	bne	.L2
	ldr	w0, [sp, 20]
	cmp	w0, 0
	beq	.L3
	ldr	w0, [sp, 16]
	cmp	w0, 0
	bne	.L2
.L3:
	ldr	w0, [sp, 12]
	cmp	w0, 0
	beq	.L4
.L2:
	mov	w0, 1
	b	.L5
.L4:
	mov	w0, 0
.L5:
	str	w0, [sp, 44]
	mov	w0, 0
	add	sp, sp, 48
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 7.2.0"
	.section	.note.GNU-stack,"",@progbits
