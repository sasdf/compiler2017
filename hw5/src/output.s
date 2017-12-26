.data
_g_g1: .word 0
_g_g2: .word 0
_g_g3: .word 0
_g_g4: .word 0
_g_g5: .space 8
_g_g6: .space 8
_g_g7: .space 8
_g_g8: .space 8
_g_g9: .word 0
_g_g10: .word 0
.text
_start_MAIN:
str x30, [sp, #-8]
str x29, [sp, #-16]
str x19, [sp, #-24]
str x20, [sp, #-32]
str x21, [sp, #-40]
str x22, [sp, #-48]
str x23, [sp, #-56]
str x24, [sp, #-64]
str x25, [sp, #-72]
str x26, [sp, #-80]
str x27, [sp, #-88]
str x28, [sp, #-96]
str x29, [sp, #-104]
add x29, sp, #-112
.data
_AR_SIZE_0: .word 48
.align 3
.text
ldr w19, _AR_SIZE_0
sub sp, x29, w19
.data
_INT_CONST_0: .word 1
.align 3
.text
ldr x19, _INT_CONST_0
ldr w20, =_g_g1
str w19, [x20, #0]
.data
_FLOAT_CONST_0: .float 2.000000
.align 3
.text
ldr s19, _FLOAT_CONST_0
ldr s20, =_g_g2
str w19, [x20, #0]
.data
_INT_CONST_1: .word 3
.align 3
.text
ldr x19, _INT_CONST_1
ldr w20, =_g_g3
str w19, [x20, #0]
.data
_FLOAT_CONST_1: .float 4.000000
.align 3
.text
ldr s19, _FLOAT_CONST_1
ldr s20, =_g_g4
str w19, [x20, #0]
.data
_INT_CONST_2: .word 5
.align 3
.text
ldr x19, _INT_CONST_2
ldr x20, =_g_g5
mov x21, #0
.data
_INT_CONST_3: .word 2
.align 3
.text
ldr x22, _INT_CONST_3
mul x21, x21, x22
.data
_INT_CONST_4: .word 0
.align 3
.text
ldr x22, _INT_CONST_4
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_INT_CONST_5: .word 55
.align 3
.text
ldr x19, _INT_CONST_5
ldr x20, =_g_g5
mov x21, #0
.data
_INT_CONST_6: .word 2
.align 3
.text
ldr x22, _INT_CONST_6
mul x21, x21, x22
.data
_INT_CONST_7: .word 1
.align 3
.text
ldr x22, _INT_CONST_7
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_FLOAT_CONST_2: .float 6.000000
.align 3
.text
ldr s19, _FLOAT_CONST_2
ldr x20, =_g_g6
mov x21, #0
.data
_INT_CONST_8: .word 2
.align 3
.text
ldr x22, _INT_CONST_8
mul x21, x21, x22
.data
_INT_CONST_9: .word 0
.align 3
.text
ldr x22, _INT_CONST_9
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_FLOAT_CONST_3: .float 66.000000
.align 3
.text
ldr s19, _FLOAT_CONST_3
ldr x20, =_g_g6
mov x21, #0
.data
_INT_CONST_10: .word 2
.align 3
.text
ldr x22, _INT_CONST_10
mul x21, x21, x22
.data
_INT_CONST_11: .word 1
.align 3
.text
ldr x22, _INT_CONST_11
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_INT_CONST_12: .word 7
.align 3
.text
ldr x19, _INT_CONST_12
ldr x20, =_g_g7
mov x21, #0
.data
_INT_CONST_13: .word 2
.align 3
.text
ldr x22, _INT_CONST_13
mul x21, x21, x22
.data
_INT_CONST_14: .word 0
.align 3
.text
ldr x22, _INT_CONST_14
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_INT_CONST_15: .word 77
.align 3
.text
ldr x19, _INT_CONST_15
ldr x20, =_g_g7
mov x21, #0
.data
_INT_CONST_16: .word 2
.align 3
.text
ldr x22, _INT_CONST_16
mul x21, x21, x22
.data
_INT_CONST_17: .word 1
.align 3
.text
ldr x22, _INT_CONST_17
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_FLOAT_CONST_4: .float 8.000000
.align 3
.text
ldr s19, _FLOAT_CONST_4
ldr x20, =_g_g8
mov x21, #0
.data
_INT_CONST_18: .word 2
.align 3
.text
ldr x22, _INT_CONST_18
mul x21, x21, x22
.data
_INT_CONST_19: .word 0
.align 3
.text
ldr x22, _INT_CONST_19
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_FLOAT_CONST_5: .float 88.000000
.align 3
.text
ldr s19, _FLOAT_CONST_5
ldr x20, =_g_g8
mov x21, #0
.data
_INT_CONST_20: .word 2
.align 3
.text
ldr x22, _INT_CONST_20
mul x21, x21, x22
.data
_INT_CONST_21: .word 1
.align 3
.text
ldr x22, _INT_CONST_21
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_INT_CONST_22: .word 9
.align 3
.text
ldr x19, _INT_CONST_22
ldr x20, =_g_g9
mov x21, #0
.data
_INT_CONST_23: .word 2
.align 3
.text
ldr x22, _INT_CONST_23
mul x21, x21, x22
.data
_INT_CONST_24: .word 0
.align 3
.text
ldr x22, _INT_CONST_24
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_INT_CONST_25: .word 99
.align 3
.text
ldr x19, _INT_CONST_25
ldr x20, =_g_g9
mov x21, #0
.data
_INT_CONST_26: .word 2
.align 3
.text
ldr x22, _INT_CONST_26
mul x21, x21, x22
.data
_INT_CONST_27: .word 1
.align 3
.text
ldr x22, _INT_CONST_27
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_FLOAT_CONST_6: .float 10.000000
.align 3
.text
ldr s19, _FLOAT_CONST_6
ldr x20, =_g_g10
mov x21, #0
.data
_INT_CONST_28: .word 2
.align 3
.text
ldr x22, _INT_CONST_28
mul x21, x21, x22
.data
_INT_CONST_29: .word 0
.align 3
.text
ldr x22, _INT_CONST_29
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_FLOAT_CONST_7: .float 100.000000
.align 3
.text
ldr s19, _FLOAT_CONST_7
ldr x20, =_g_g10
mov x21, #0
.data
_INT_CONST_30: .word 2
.align 3
.text
ldr x22, _INT_CONST_30
mul x21, x21, x22
.data
_INT_CONST_31: .word 1
.align 3
.text
ldr x22, _INT_CONST_31
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_INT_CONST_32: .word 1
.align 3
.text
ldr x19, _INT_CONST_32
.data
_INT_CONST_33: .word 0
.align 3
.text
ldr x20, _INT_CONST_33
sub x20, x29, x20
str w19, [x20, #0]
.data
_FLOAT_CONST_8: .float 2.000000
.align 3
.text
ldr s19, _FLOAT_CONST_8
.data
_INT_CONST_34: .word 4
.align 3
.text
ldr x20, _INT_CONST_34
sub x20, x29, x20
str s19, [x20, #0]
.data
_INT_CONST_35: .word 3
.align 3
.text
ldr x19, _INT_CONST_35
.data
_INT_CONST_36: .word 8
.align 3
.text
ldr x20, _INT_CONST_36
sub x20, x29, x20
str w19, [x20, #0]
.data
_FLOAT_CONST_9: .float 4.000000
.align 3
.text
ldr s19, _FLOAT_CONST_9
.data
_INT_CONST_37: .word 12
.align 3
.text
ldr x20, _INT_CONST_37
sub x20, x29, x20
str s19, [x20, #0]
.data
_INT_CONST_38: .word 5
.align 3
.text
ldr x19, _INT_CONST_38
.data
_INT_CONST_39: .word 16
.align 3
.text
ldr x20, _INT_CONST_39
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_40: .word 2
.align 3
.text
ldr x22, _INT_CONST_40
mul x21, x21, x22
.data
_INT_CONST_41: .word 0
.align 3
.text
ldr x22, _INT_CONST_41
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_INT_CONST_42: .word 55
.align 3
.text
ldr x19, _INT_CONST_42
.data
_INT_CONST_43: .word 16
.align 3
.text
ldr x20, _INT_CONST_43
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_44: .word 2
.align 3
.text
ldr x22, _INT_CONST_44
mul x21, x21, x22
.data
_INT_CONST_45: .word 1
.align 3
.text
ldr x22, _INT_CONST_45
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_FLOAT_CONST_10: .float 6.000000
.align 3
.text
ldr s19, _FLOAT_CONST_10
.data
_INT_CONST_46: .word 20
.align 3
.text
ldr x20, _INT_CONST_46
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_47: .word 2
.align 3
.text
ldr x22, _INT_CONST_47
mul x21, x21, x22
.data
_INT_CONST_48: .word 0
.align 3
.text
ldr x22, _INT_CONST_48
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_FLOAT_CONST_11: .float 66.000000
.align 3
.text
ldr s19, _FLOAT_CONST_11
.data
_INT_CONST_49: .word 20
.align 3
.text
ldr x20, _INT_CONST_49
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_50: .word 2
.align 3
.text
ldr x22, _INT_CONST_50
mul x21, x21, x22
.data
_INT_CONST_51: .word 1
.align 3
.text
ldr x22, _INT_CONST_51
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_INT_CONST_52: .word 7
.align 3
.text
ldr x19, _INT_CONST_52
.data
_INT_CONST_53: .word 24
.align 3
.text
ldr x20, _INT_CONST_53
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_54: .word 2
.align 3
.text
ldr x22, _INT_CONST_54
mul x21, x21, x22
.data
_INT_CONST_55: .word 0
.align 3
.text
ldr x22, _INT_CONST_55
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_INT_CONST_56: .word 77
.align 3
.text
ldr x19, _INT_CONST_56
.data
_INT_CONST_57: .word 24
.align 3
.text
ldr x20, _INT_CONST_57
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_58: .word 2
.align 3
.text
ldr x22, _INT_CONST_58
mul x21, x21, x22
.data
_INT_CONST_59: .word 1
.align 3
.text
ldr x22, _INT_CONST_59
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_FLOAT_CONST_12: .float 8.000000
.align 3
.text
ldr s19, _FLOAT_CONST_12
.data
_INT_CONST_60: .word 28
.align 3
.text
ldr x20, _INT_CONST_60
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_61: .word 2
.align 3
.text
ldr x22, _INT_CONST_61
mul x21, x21, x22
.data
_INT_CONST_62: .word 0
.align 3
.text
ldr x22, _INT_CONST_62
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_FLOAT_CONST_13: .float 88.000000
.align 3
.text
ldr s19, _FLOAT_CONST_13
.data
_INT_CONST_63: .word 28
.align 3
.text
ldr x20, _INT_CONST_63
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_64: .word 2
.align 3
.text
ldr x22, _INT_CONST_64
mul x21, x21, x22
.data
_INT_CONST_65: .word 1
.align 3
.text
ldr x22, _INT_CONST_65
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_INT_CONST_66: .word 9
.align 3
.text
ldr x19, _INT_CONST_66
.data
_INT_CONST_67: .word 32
.align 3
.text
ldr x20, _INT_CONST_67
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_68: .word 2
.align 3
.text
ldr x22, _INT_CONST_68
mul x21, x21, x22
.data
_INT_CONST_69: .word 0
.align 3
.text
ldr x22, _INT_CONST_69
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_INT_CONST_70: .word 99
.align 3
.text
ldr x19, _INT_CONST_70
.data
_INT_CONST_71: .word 32
.align 3
.text
ldr x20, _INT_CONST_71
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_72: .word 2
.align 3
.text
ldr x22, _INT_CONST_72
mul x21, x21, x22
.data
_INT_CONST_73: .word 1
.align 3
.text
ldr x22, _INT_CONST_73
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_FLOAT_CONST_14: .float 10.000000
.align 3
.text
ldr s19, _FLOAT_CONST_14
.data
_INT_CONST_74: .word 36
.align 3
.text
ldr x20, _INT_CONST_74
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_75: .word 2
.align 3
.text
ldr x22, _INT_CONST_75
mul x21, x21, x22
.data
_INT_CONST_76: .word 0
.align 3
.text
ldr x22, _INT_CONST_76
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
.data
_FLOAT_CONST_15: .float 100.000000
.align 3
.text
ldr s19, _FLOAT_CONST_15
.data
_INT_CONST_77: .word 36
.align 3
.text
ldr x20, _INT_CONST_77
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_78: .word 2
.align 3
.text
ldr x22, _INT_CONST_78
mul x21, x21, x22
.data
_INT_CONST_79: .word 1
.align 3
.text
ldr x22, _INT_CONST_79
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str s19, [x20, #0]
ldr w19, =_g_g1
mov w0, w19
bl _write_int
.data
_STR_CONST_0: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_0
mov x0, x19
bl _write_str
ldr s19, =_g_g2
fmov s0, s19
bl _write_float
.data
_STR_CONST_1: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_1
mov x0, x19
bl _write_str
ldr w19, =_g_g3
mov w0, w19
bl _write_int
.data
_STR_CONST_2: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_2
mov x0, x19
bl _write_str
ldr s19, =_g_g4
fmov s0, s19
bl _write_float
.data
_STR_CONST_3: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_3
mov x0, x19
bl _write_str
ldr x19, =_g_g5
mov x20, #0
.data
_INT_CONST_80: .word 2
.align 3
.text
ldr x21, _INT_CONST_80
mul x20, x20, x21
.data
_INT_CONST_81: .word 0
.align 3
.text
ldr x21, _INT_CONST_81
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_4: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_4
mov x0, x19
bl _write_str
ldr x19, =_g_g5
mov x20, #0
.data
_INT_CONST_82: .word 2
.align 3
.text
ldr x21, _INT_CONST_82
mul x20, x20, x21
.data
_INT_CONST_83: .word 1
.align 3
.text
ldr x21, _INT_CONST_83
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_5: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_5
mov x0, x19
bl _write_str
ldr x19, =_g_g6
mov x20, #0
.data
_INT_CONST_84: .word 2
.align 3
.text
ldr x21, _INT_CONST_84
mul x20, x20, x21
.data
_INT_CONST_85: .word 0
.align 3
.text
ldr x21, _INT_CONST_85
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_6: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_6
mov x0, x19
bl _write_str
ldr x19, =_g_g6
mov x20, #0
.data
_INT_CONST_86: .word 2
.align 3
.text
ldr x21, _INT_CONST_86
mul x20, x20, x21
.data
_INT_CONST_87: .word 1
.align 3
.text
ldr x21, _INT_CONST_87
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_7: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_7
mov x0, x19
bl _write_str
ldr x19, =_g_g7
mov x20, #0
.data
_INT_CONST_88: .word 2
.align 3
.text
ldr x21, _INT_CONST_88
mul x20, x20, x21
.data
_INT_CONST_89: .word 0
.align 3
.text
ldr x21, _INT_CONST_89
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_8: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_8
mov x0, x19
bl _write_str
ldr x19, =_g_g7
mov x20, #0
.data
_INT_CONST_90: .word 2
.align 3
.text
ldr x21, _INT_CONST_90
mul x20, x20, x21
.data
_INT_CONST_91: .word 1
.align 3
.text
ldr x21, _INT_CONST_91
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_9: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_9
mov x0, x19
bl _write_str
ldr x19, =_g_g8
mov x20, #0
.data
_INT_CONST_92: .word 2
.align 3
.text
ldr x21, _INT_CONST_92
mul x20, x20, x21
.data
_INT_CONST_93: .word 0
.align 3
.text
ldr x21, _INT_CONST_93
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_10: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_10
mov x0, x19
bl _write_str
ldr x19, =_g_g8
mov x20, #0
.data
_INT_CONST_94: .word 2
.align 3
.text
ldr x21, _INT_CONST_94
mul x20, x20, x21
.data
_INT_CONST_95: .word 1
.align 3
.text
ldr x21, _INT_CONST_95
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_11: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_11
mov x0, x19
bl _write_str
ldr x19, =_g_g9
mov x20, #0
.data
_INT_CONST_96: .word 2
.align 3
.text
ldr x21, _INT_CONST_96
mul x20, x20, x21
.data
_INT_CONST_97: .word 0
.align 3
.text
ldr x21, _INT_CONST_97
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_12: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_12
mov x0, x19
bl _write_str
ldr x19, =_g_g9
mov x20, #0
.data
_INT_CONST_98: .word 2
.align 3
.text
ldr x21, _INT_CONST_98
mul x20, x20, x21
.data
_INT_CONST_99: .word 1
.align 3
.text
ldr x21, _INT_CONST_99
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_13: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_13
mov x0, x19
bl _write_str
ldr x19, =_g_g10
mov x20, #0
.data
_INT_CONST_100: .word 2
.align 3
.text
ldr x21, _INT_CONST_100
mul x20, x20, x21
.data
_INT_CONST_101: .word 0
.align 3
.text
ldr x21, _INT_CONST_101
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_14: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_14
mov x0, x19
bl _write_str
ldr x19, =_g_g10
mov x20, #0
.data
_INT_CONST_102: .word 2
.align 3
.text
ldr x21, _INT_CONST_102
mul x20, x20, x21
.data
_INT_CONST_103: .word 1
.align 3
.text
ldr x21, _INT_CONST_103
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_15: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_15
mov x0, x19
bl _write_str
.data
_INT_CONST_104: .word 0
.align 3
.text
ldr x19, _INT_CONST_104
sub x19, x29, x19
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_16: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_16
mov x0, x19
bl _write_str
.data
_INT_CONST_105: .word 4
.align 3
.text
ldr x19, _INT_CONST_105
sub x19, x29, x19
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_17: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_17
mov x0, x19
bl _write_str
.data
_INT_CONST_106: .word 8
.align 3
.text
ldr x19, _INT_CONST_106
sub x19, x29, x19
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_18: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_18
mov x0, x19
bl _write_str
.data
_INT_CONST_107: .word 12
.align 3
.text
ldr x19, _INT_CONST_107
sub x19, x29, x19
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_19: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_19
mov x0, x19
bl _write_str
.data
_INT_CONST_108: .word 16
.align 3
.text
ldr x19, _INT_CONST_108
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_109: .word 2
.align 3
.text
ldr x21, _INT_CONST_109
mul x20, x20, x21
.data
_INT_CONST_110: .word 0
.align 3
.text
ldr x21, _INT_CONST_110
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_20: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_20
mov x0, x19
bl _write_str
.data
_INT_CONST_111: .word 16
.align 3
.text
ldr x19, _INT_CONST_111
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_112: .word 2
.align 3
.text
ldr x21, _INT_CONST_112
mul x20, x20, x21
.data
_INT_CONST_113: .word 1
.align 3
.text
ldr x21, _INT_CONST_113
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_21: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_21
mov x0, x19
bl _write_str
.data
_INT_CONST_114: .word 20
.align 3
.text
ldr x19, _INT_CONST_114
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_115: .word 2
.align 3
.text
ldr x21, _INT_CONST_115
mul x20, x20, x21
.data
_INT_CONST_116: .word 0
.align 3
.text
ldr x21, _INT_CONST_116
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_22: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_22
mov x0, x19
bl _write_str
.data
_INT_CONST_117: .word 20
.align 3
.text
ldr x19, _INT_CONST_117
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_118: .word 2
.align 3
.text
ldr x21, _INT_CONST_118
mul x20, x20, x21
.data
_INT_CONST_119: .word 1
.align 3
.text
ldr x21, _INT_CONST_119
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_23: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_23
mov x0, x19
bl _write_str
.data
_INT_CONST_120: .word 24
.align 3
.text
ldr x19, _INT_CONST_120
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_121: .word 2
.align 3
.text
ldr x21, _INT_CONST_121
mul x20, x20, x21
.data
_INT_CONST_122: .word 0
.align 3
.text
ldr x21, _INT_CONST_122
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_24: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_24
mov x0, x19
bl _write_str
.data
_INT_CONST_123: .word 24
.align 3
.text
ldr x19, _INT_CONST_123
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_124: .word 2
.align 3
.text
ldr x21, _INT_CONST_124
mul x20, x20, x21
.data
_INT_CONST_125: .word 1
.align 3
.text
ldr x21, _INT_CONST_125
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_25: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_25
mov x0, x19
bl _write_str
.data
_INT_CONST_126: .word 28
.align 3
.text
ldr x19, _INT_CONST_126
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_127: .word 2
.align 3
.text
ldr x21, _INT_CONST_127
mul x20, x20, x21
.data
_INT_CONST_128: .word 0
.align 3
.text
ldr x21, _INT_CONST_128
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_26: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_26
mov x0, x19
bl _write_str
.data
_INT_CONST_129: .word 28
.align 3
.text
ldr x19, _INT_CONST_129
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_130: .word 2
.align 3
.text
ldr x21, _INT_CONST_130
mul x20, x20, x21
.data
_INT_CONST_131: .word 1
.align 3
.text
ldr x21, _INT_CONST_131
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_27: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_27
mov x0, x19
bl _write_str
.data
_INT_CONST_132: .word 32
.align 3
.text
ldr x19, _INT_CONST_132
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_133: .word 2
.align 3
.text
ldr x21, _INT_CONST_133
mul x20, x20, x21
.data
_INT_CONST_134: .word 0
.align 3
.text
ldr x21, _INT_CONST_134
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_28: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_28
mov x0, x19
bl _write_str
.data
_INT_CONST_135: .word 32
.align 3
.text
ldr x19, _INT_CONST_135
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_136: .word 2
.align 3
.text
ldr x21, _INT_CONST_136
mul x20, x20, x21
.data
_INT_CONST_137: .word 1
.align 3
.text
ldr x21, _INT_CONST_137
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_29: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_29
mov x0, x19
bl _write_str
.data
_INT_CONST_138: .word 36
.align 3
.text
ldr x19, _INT_CONST_138
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_139: .word 2
.align 3
.text
ldr x21, _INT_CONST_139
mul x20, x20, x21
.data
_INT_CONST_140: .word 0
.align 3
.text
ldr x21, _INT_CONST_140
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_30: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_30
mov x0, x19
bl _write_str
.data
_INT_CONST_141: .word 36
.align 3
.text
ldr x19, _INT_CONST_141
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_142: .word 2
.align 3
.text
ldr x21, _INT_CONST_142
mul x20, x20, x21
.data
_INT_CONST_143: .word 1
.align 3
.text
ldr x21, _INT_CONST_143
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_31: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_31
mov x0, x19
bl _write_str
.data
_INT_CONST_144: .word 0
.align 3
.text
ldr x19, _INT_CONST_144
mov w0, w19
add sp, x29, #112
ldr x29, [x29, #8]
ldr x28, [x29, #16]
ldr x27, [x29, #24]
ldr x26, [x29, #32]
ldr x25, [x29, #40]
ldr x24, [x29, #48]
ldr x23, [x29, #56]
ldr x22, [x29, #64]
ldr x21, [x29, #72]
ldr x20, [x29, #80]
ldr x19, [x29, #88]
ldr x30, [sp, #-8]
ldr x29, [sp, #-16]
ret x30
