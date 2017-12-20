	.arch armv8-a
	.file	"test.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.comm	a,720,8
	.comm	b,4,4
	.comm	c,4,4
	.comm	d,4,4
	.comm	e,144,8
	.comm	f,4,4
	.align	2
	.global	bb
	.type	bb, %function
bb:
.LFB0:
	.file 1 "./test.c"
	.loc 1 5 0
	.cfi_startproc
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	.loc 1 7 0
	ldr	w0, [sp, 12]
	.loc 1 8 0
	add	sp, sp, 16
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE0:
	.size	bb, .-bb
	.align	2
	.global	aa
	.type	aa, %function
aa:
.LFB1:
	.loc 1 10 0
	.cfi_startproc
	stp	x29, x30, [sp, -32]!
	.cfi_def_cfa_offset 16
	.cfi_offset 29, -16
	.cfi_offset 30, -8
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	.loc 1 12 0
	bl	bb
	.loc 1 13 0
	mov	w0, 1
	.loc 1 14 0
	ldp	x29, x30, [sp], 16
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 0
	ret
	.cfi_endproc
.LFE1:
	.size	aa, .-aa
	.align	2
	.global	_start
	.type	_start, %function
_start:
.LFB2:
	.loc 1 16 0
	.cfi_startproc
	sub	sp, sp, #4096
	.cfi_def_cfa_offset 4096
	sub	sp, sp, #784
	.cfi_def_cfa_offset 4880
	stp	x29, x30, [sp, -16]!
	.cfi_def_cfa_offset 4896
	.cfi_offset 29, -4896
	.cfi_offset 30, -4888
	add	x29, sp, 0
	.cfi_def_cfa_register 29
	str	w0, [x29, 28]
	str	w1, [x29, 24]
	.loc 1 24 0
	bl	aa
	.loc 1 25 0
	fmov	s0, wzr
	.loc 1 26 0
	ldp	x29, x30, [sp], 16
	.cfi_restore 30
	.cfi_restore 29
	.cfi_def_cfa 31, 4880
	add	sp, sp, 4096
	.cfi_def_cfa_offset 784
	add	sp, sp, 784
	.cfi_def_cfa_offset 0
	ret
	.cfi_endproc
.LFE2:
	.size	_start, .-_start
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x1dc
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.4byte	.LASF4
	.byte	0xc
	.4byte	.LASF5
	.4byte	.LASF6
	.8byte	.Ltext0
	.8byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.string	"bb"
	.byte	0x1
	.byte	0x5
	.4byte	0x6c
	.8byte	.LFB0
	.8byte	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x6c
	.uleb128 0x3
	.string	"a"
	.byte	0x1
	.byte	0x6
	.4byte	0x6c
	.uleb128 0x3
	.string	"b"
	.byte	0x1
	.byte	0x6
	.4byte	0x6c
	.uleb128 0x4
	.string	"c"
	.byte	0x1
	.byte	0x6
	.4byte	0x6c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -4
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x6
	.string	"aa"
	.byte	0x1
	.byte	0xa
	.4byte	0x6c
	.8byte	.LFB1
	.8byte	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xaf
	.uleb128 0x3
	.string	"a"
	.byte	0x1
	.byte	0xb
	.4byte	0x6c
	.uleb128 0x3
	.string	"b"
	.byte	0x1
	.byte	0xb
	.4byte	0x6c
	.uleb128 0x3
	.string	"c"
	.byte	0x1
	.byte	0xb
	.4byte	0x6c
	.byte	0
	.uleb128 0x7
	.4byte	.LASF7
	.byte	0x1
	.byte	0x10
	.4byte	0x12d
	.8byte	.LFB2
	.8byte	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x12d
	.uleb128 0x8
	.4byte	.LASF0
	.byte	0x1
	.byte	0x10
	.4byte	0x6c
	.uleb128 0x3
	.byte	0x91
	.sleb128 -4868
	.uleb128 0x8
	.4byte	.LASF1
	.byte	0x1
	.byte	0x10
	.4byte	0x6c
	.uleb128 0x3
	.byte	0x91
	.sleb128 -4872
	.uleb128 0x4
	.string	"a"
	.byte	0x1
	.byte	0x11
	.4byte	0x134
	.uleb128 0x3
	.byte	0x91
	.sleb128 -720
	.uleb128 0x3
	.string	"b"
	.byte	0x1
	.byte	0x11
	.4byte	0x6c
	.uleb128 0x3
	.string	"c"
	.byte	0x1
	.byte	0x11
	.4byte	0x6c
	.uleb128 0x3
	.string	"d"
	.byte	0x1
	.byte	0x12
	.4byte	0x6c
	.uleb128 0x4
	.string	"e"
	.byte	0x1
	.byte	0x12
	.4byte	0x151
	.uleb128 0x3
	.byte	0x91
	.sleb128 -864
	.uleb128 0x3
	.string	"f"
	.byte	0x1
	.byte	0x13
	.4byte	0x12d
	.byte	0
	.uleb128 0x9
	.byte	0x4
	.byte	0x4
	.4byte	.LASF2
	.uleb128 0xa
	.4byte	0x6c
	.4byte	0x14a
	.uleb128 0xb
	.4byte	0x14a
	.byte	0x9
	.uleb128 0xb
	.4byte	0x14a
	.byte	0x11
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0xa
	.4byte	0x6c
	.4byte	0x16d
	.uleb128 0xb
	.4byte	0x14a
	.byte	0x5
	.uleb128 0xb
	.4byte	0x14a
	.byte	0x1
	.uleb128 0xb
	.4byte	0x14a
	.byte	0x2
	.byte	0
	.uleb128 0xc
	.string	"a"
	.byte	0x1
	.byte	0x1
	.4byte	0x134
	.uleb128 0x9
	.byte	0x3
	.8byte	a
	.uleb128 0xc
	.string	"b"
	.byte	0x1
	.byte	0x1
	.4byte	0x6c
	.uleb128 0x9
	.byte	0x3
	.8byte	b
	.uleb128 0xc
	.string	"c"
	.byte	0x1
	.byte	0x1
	.4byte	0x6c
	.uleb128 0x9
	.byte	0x3
	.8byte	c
	.uleb128 0xc
	.string	"d"
	.byte	0x1
	.byte	0x2
	.4byte	0x6c
	.uleb128 0x9
	.byte	0x3
	.8byte	d
	.uleb128 0xc
	.string	"e"
	.byte	0x1
	.byte	0x2
	.4byte	0x151
	.uleb128 0x9
	.byte	0x3
	.8byte	e
	.uleb128 0xc
	.string	"f"
	.byte	0x1
	.byte	0x3
	.4byte	0x12d
	.uleb128 0x9
	.byte	0x3
	.8byte	f
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x2c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x8
	.byte	0
	.2byte	0
	.2byte	0
	.8byte	.Ltext0
	.8byte	.Letext0-.Ltext0
	.8byte	0
	.8byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF2:
	.string	"float"
.LASF0:
	.string	"argc"
.LASF6:
	.string	"/home/kevin/Documents/compiler/compilerAC/hw5/src"
.LASF5:
	.string	"./test.c"
.LASF4:
	.string	"GNU C11 5.4.0 20160609 -mlittle-endian -mabi=lp64 -g -O0"
.LASF7:
	.string	"_start"
.LASF3:
	.string	"sizetype"
.LASF1:
	.string	"argv"
	.ident	"GCC: (Ubuntu/Linaro 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
