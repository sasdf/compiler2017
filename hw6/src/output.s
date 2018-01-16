.data
_g_dim: .word 2
_g_a: .space 256
_g_b: .space 256
_g_c: .space 256
.text
_start_print:
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
str s19, [sp, #-104]
str s20, [sp, #-112]
str s21, [sp, #-120]
str s22, [sp, #-128]
str s23, [sp, #-136]
str s24, [sp, #-144]
str s25, [sp, #-152]
str s26, [sp, #-160]
str s27, [sp, #-168]
str s28, [sp, #-176]
add x29, sp, #-176
.data
_AR_SIZE_0: .word 16
.align 3
.text
ldr w19, _AR_SIZE_0
sub sp, x29, w19
.data
_INT_CONST_0: .word 0
_INT_CONST_1: .word 0
.align 3
.text
ldr x19, _INT_CONST_0
.data
_INT_CONST_2: .word 0
_INT_CONST_3: .word 0
.align 3
.text
ldr x20, _INT_CONST_2
sub x20, x29, x20
str w19, [x20, #0]
_FOR_0:
.data
_INT_CONST_4: .word 0
_INT_CONST_5: .word 0
.align 3
.text
ldr x19, _INT_CONST_4
sub x19, x29, x19
ldr w19, [x19, #0]
ldr x20, =_g_dim
ldr w20, [x20, #0]
cmp w19, w20
cset w19, lt
cmp w19, #0
beq _FOR_END_0
.data
_INT_CONST_6: .word 0
_INT_CONST_7: .word 0
.align 3
.text
ldr x19, _INT_CONST_6
.data
_INT_CONST_8: .word 4
_INT_CONST_9: .word 0
.align 3
.text
ldr x20, _INT_CONST_8
sub x20, x29, x20
str w19, [x20, #0]
_FOR_1:
.data
_INT_CONST_10: .word 4
_INT_CONST_11: .word 0
.align 3
.text
ldr x19, _INT_CONST_10
sub x19, x29, x19
ldr w19, [x19, #0]
ldr x20, =_g_dim
ldr w20, [x20, #0]
cmp w19, w20
cset w19, lt
cmp w19, #0
beq _FOR_END_1
.data
_INT_CONST_12: .word 0
_INT_CONST_13: .word 0
.align 3
.text
ldr x19, _INT_CONST_12
.data
_INT_CONST_14: .word 8
_INT_CONST_15: .word 0
.align 3
.text
ldr x20, _INT_CONST_14
sub x20, x29, x20
str w19, [x20, #0]
_FOR_2:
.data
_INT_CONST_16: .word 8
_INT_CONST_17: .word 0
.align 3
.text
ldr x19, _INT_CONST_16
sub x19, x29, x19
ldr w19, [x19, #0]
ldr x20, =_g_dim
ldr w20, [x20, #0]
cmp w19, w20
cset w19, lt
cmp w19, #0
beq _FOR_END_2
ldr x19, =_g_c
mov x20, #0
.data
_INT_CONST_18: .word 2
_INT_CONST_19: .word 0
.align 3
.text
ldr x21, _INT_CONST_18
mul x20, x20, x21
.data
_INT_CONST_20: .word 0
_INT_CONST_21: .word 0
.align 3
.text
ldr x21, _INT_CONST_20
sub x21, x29, x21
ldr w21, [x21, #0]
lsl x21, x21, #2
add x20, x20, x21
.data
_INT_CONST_22: .word 2
_INT_CONST_23: .word 0
.align 3
.text
ldr x21, _INT_CONST_22
mul x20, x20, x21
.data
_INT_CONST_24: .word 4
_INT_CONST_25: .word 0
.align 3
.text
ldr x21, _INT_CONST_24
sub x21, x29, x21
ldr w21, [x21, #0]
lsl x21, x21, #2
add x20, x20, x21
.data
_INT_CONST_26: .word 2
_INT_CONST_27: .word 0
.align 3
.text
ldr x21, _INT_CONST_26
mul x20, x20, x21
.data
_INT_CONST_28: .word 8
_INT_CONST_29: .word 0
.align 3
.text
ldr x21, _INT_CONST_28
sub x21, x29, x21
ldr w21, [x21, #0]
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_0: .asciz " "
.align 3
.text
ldr x19, =_STR_CONST_0
mov x0, x19
bl _write_str
.data
_INT_CONST_30: .word 8
_INT_CONST_31: .word 0
.align 3
.text
ldr x19, _INT_CONST_30
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_32: .word 1
_INT_CONST_33: .word 0
.align 3
.text
ldr x20, _INT_CONST_32
add w19, w19, w20
.data
_INT_CONST_34: .word 8
_INT_CONST_35: .word 0
.align 3
.text
ldr x20, _INT_CONST_34
sub x20, x29, x20
str w19, [x20, #0]
b _FOR_2
_FOR_END_2:
.data
_STR_CONST_1: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_1
mov x0, x19
bl _write_str
.data
_INT_CONST_36: .word 4
_INT_CONST_37: .word 0
.align 3
.text
ldr x19, _INT_CONST_36
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_38: .word 1
_INT_CONST_39: .word 0
.align 3
.text
ldr x20, _INT_CONST_38
add w19, w19, w20
.data
_INT_CONST_40: .word 4
_INT_CONST_41: .word 0
.align 3
.text
ldr x20, _INT_CONST_40
sub x20, x29, x20
str w19, [x20, #0]
b _FOR_1
_FOR_END_1:
.data
_STR_CONST_2: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_2
mov x0, x19
bl _write_str
.data
_INT_CONST_42: .word 0
_INT_CONST_43: .word 0
.align 3
.text
ldr x19, _INT_CONST_42
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_44: .word 1
_INT_CONST_45: .word 0
.align 3
.text
ldr x20, _INT_CONST_44
add w19, w19, w20
.data
_INT_CONST_46: .word 0
_INT_CONST_47: .word 0
.align 3
.text
ldr x20, _INT_CONST_46
sub x20, x29, x20
str w19, [x20, #0]
b _FOR_0
_FOR_END_0:
_epilogue_print:
add sp, x29, #176
ldr s28, [x29, #0]
ldr s27, [x29, #8]
ldr s26, [x29, #16]
ldr s25, [x29, #24]
ldr s24, [x29, #32]
ldr s23, [x29, #40]
ldr s22, [x29, #48]
ldr s21, [x29, #56]
ldr s20, [x29, #64]
ldr s19, [x29, #72]
ldr x28, [x29, #80]
ldr x27, [x29, #88]
ldr x26, [x29, #96]
ldr x25, [x29, #104]
ldr x24, [x29, #112]
ldr x23, [x29, #120]
ldr x22, [x29, #128]
ldr x21, [x29, #136]
ldr x20, [x29, #144]
ldr x19, [x29, #152]
ldr x30, [sp, #-8]
ldr x29, [sp, #-16]
ret x30
.text
_start_arraymult:
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
str s19, [sp, #-104]
str s20, [sp, #-112]
str s21, [sp, #-120]
str s22, [sp, #-128]
str s23, [sp, #-136]
str s24, [sp, #-144]
str s25, [sp, #-152]
str s26, [sp, #-160]
str s27, [sp, #-168]
str s28, [sp, #-176]
add x29, sp, #-176
.data
_AR_SIZE_1: .word 16
.align 3
.text
ldr w19, _AR_SIZE_1
sub sp, x29, w19
.data
_INT_CONST_48: .word 0
_INT_CONST_49: .word 0
.align 3
.text
ldr x19, _INT_CONST_48
.data
_INT_CONST_50: .word 0
_INT_CONST_51: .word 0
.align 3
.text
ldr x20, _INT_CONST_50
sub x20, x29, x20
str w19, [x20, #0]
_FOR_3:
.data
_INT_CONST_52: .word 0
_INT_CONST_53: .word 0
.align 3
.text
ldr x19, _INT_CONST_52
sub x19, x29, x19
ldr w19, [x19, #0]
ldr x20, =_g_dim
ldr w20, [x20, #0]
cmp w19, w20
cset w19, lt
cmp w19, #0
beq _FOR_END_3
.data
_INT_CONST_54: .word 0
_INT_CONST_55: .word 0
.align 3
.text
ldr x19, _INT_CONST_54
.data
_INT_CONST_56: .word 4
_INT_CONST_57: .word 0
.align 3
.text
ldr x20, _INT_CONST_56
sub x20, x29, x20
str w19, [x20, #0]
_FOR_4:
.data
_INT_CONST_58: .word 4
_INT_CONST_59: .word 0
.align 3
.text
ldr x19, _INT_CONST_58
sub x19, x29, x19
ldr w19, [x19, #0]
ldr x20, =_g_dim
ldr w20, [x20, #0]
cmp w19, w20
cset w19, lt
cmp w19, #0
beq _FOR_END_4
.data
_INT_CONST_60: .word 0
_INT_CONST_61: .word 0
.align 3
.text
ldr x19, _INT_CONST_60
.data
_INT_CONST_62: .word 8
_INT_CONST_63: .word 0
.align 3
.text
ldr x20, _INT_CONST_62
sub x20, x29, x20
str w19, [x20, #0]
_FOR_5:
.data
_INT_CONST_64: .word 8
_INT_CONST_65: .word 0
.align 3
.text
ldr x19, _INT_CONST_64
sub x19, x29, x19
ldr w19, [x19, #0]
ldr x20, =_g_dim
ldr w20, [x20, #0]
cmp w19, w20
cset w19, lt
cmp w19, #0
beq _FOR_END_5
ldr x19, =_g_a
mov x20, #0
.data
_INT_CONST_66: .word 2
_INT_CONST_67: .word 0
.align 3
.text
ldr x21, _INT_CONST_66
mul x20, x20, x21
.data
_INT_CONST_68: .word 0
_INT_CONST_69: .word 0
.align 3
.text
ldr x21, _INT_CONST_68
sub x21, x29, x21
ldr w21, [x21, #0]
lsl x21, x21, #2
add x20, x20, x21
.data
_INT_CONST_70: .word 2
_INT_CONST_71: .word 0
.align 3
.text
ldr x21, _INT_CONST_70
mul x20, x20, x21
.data
_INT_CONST_72: .word 4
_INT_CONST_73: .word 0
.align 3
.text
ldr x21, _INT_CONST_72
sub x21, x29, x21
ldr w21, [x21, #0]
lsl x21, x21, #2
add x20, x20, x21
.data
_INT_CONST_74: .word 2
_INT_CONST_75: .word 0
.align 3
.text
ldr x21, _INT_CONST_74
mul x20, x20, x21
.data
_INT_CONST_76: .word 8
_INT_CONST_77: .word 0
.align 3
.text
ldr x21, _INT_CONST_76
sub x21, x29, x21
ldr w21, [x21, #0]
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
ldr x20, =_g_b
mov x21, #0
.data
_INT_CONST_78: .word 2
_INT_CONST_79: .word 0
.align 3
.text
ldr x22, _INT_CONST_78
mul x21, x21, x22
.data
_INT_CONST_80: .word 0
_INT_CONST_81: .word 0
.align 3
.text
ldr x22, _INT_CONST_80
sub x22, x29, x22
ldr w22, [x22, #0]
lsl x22, x22, #2
add x21, x21, x22
.data
_INT_CONST_82: .word 2
_INT_CONST_83: .word 0
.align 3
.text
ldr x22, _INT_CONST_82
mul x21, x21, x22
.data
_INT_CONST_84: .word 4
_INT_CONST_85: .word 0
.align 3
.text
ldr x22, _INT_CONST_84
sub x22, x29, x22
ldr w22, [x22, #0]
lsl x22, x22, #2
add x21, x21, x22
.data
_INT_CONST_86: .word 2
_INT_CONST_87: .word 0
.align 3
.text
ldr x22, _INT_CONST_86
mul x21, x21, x22
.data
_INT_CONST_88: .word 8
_INT_CONST_89: .word 0
.align 3
.text
ldr x22, _INT_CONST_88
sub x22, x29, x22
ldr w22, [x22, #0]
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
ldr w20, [x20, #0]
mul w19, w19, w20
ldr x20, =_g_c
mov x21, #0
.data
_INT_CONST_90: .word 2
_INT_CONST_91: .word 0
.align 3
.text
ldr x22, _INT_CONST_90
mul x21, x21, x22
.data
_INT_CONST_92: .word 0
_INT_CONST_93: .word 0
.align 3
.text
ldr x22, _INT_CONST_92
sub x22, x29, x22
ldr w22, [x22, #0]
lsl x22, x22, #2
add x21, x21, x22
.data
_INT_CONST_94: .word 2
_INT_CONST_95: .word 0
.align 3
.text
ldr x22, _INT_CONST_94
mul x21, x21, x22
.data
_INT_CONST_96: .word 4
_INT_CONST_97: .word 0
.align 3
.text
ldr x22, _INT_CONST_96
sub x22, x29, x22
ldr w22, [x22, #0]
lsl x22, x22, #2
add x21, x21, x22
.data
_INT_CONST_98: .word 2
_INT_CONST_99: .word 0
.align 3
.text
ldr x22, _INT_CONST_98
mul x21, x21, x22
.data
_INT_CONST_100: .word 8
_INT_CONST_101: .word 0
.align 3
.text
ldr x22, _INT_CONST_100
sub x22, x29, x22
ldr w22, [x22, #0]
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_INT_CONST_102: .word 8
_INT_CONST_103: .word 0
.align 3
.text
ldr x19, _INT_CONST_102
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_104: .word 1
_INT_CONST_105: .word 0
.align 3
.text
ldr x20, _INT_CONST_104
add w19, w19, w20
.data
_INT_CONST_106: .word 8
_INT_CONST_107: .word 0
.align 3
.text
ldr x20, _INT_CONST_106
sub x20, x29, x20
str w19, [x20, #0]
b _FOR_5
_FOR_END_5:
.data
_INT_CONST_108: .word 4
_INT_CONST_109: .word 0
.align 3
.text
ldr x19, _INT_CONST_108
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_110: .word 1
_INT_CONST_111: .word 0
.align 3
.text
ldr x20, _INT_CONST_110
add w19, w19, w20
.data
_INT_CONST_112: .word 4
_INT_CONST_113: .word 0
.align 3
.text
ldr x20, _INT_CONST_112
sub x20, x29, x20
str w19, [x20, #0]
b _FOR_4
_FOR_END_4:
.data
_INT_CONST_114: .word 0
_INT_CONST_115: .word 0
.align 3
.text
ldr x19, _INT_CONST_114
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_116: .word 1
_INT_CONST_117: .word 0
.align 3
.text
ldr x20, _INT_CONST_116
add w19, w19, w20
.data
_INT_CONST_118: .word 0
_INT_CONST_119: .word 0
.align 3
.text
ldr x20, _INT_CONST_118
sub x20, x29, x20
str w19, [x20, #0]
b _FOR_3
_FOR_END_3:
add sp, sp, #-0
bl _start_print
add sp, sp, #0
_epilogue_arraymult:
add sp, x29, #176
ldr s28, [x29, #0]
ldr s27, [x29, #8]
ldr s26, [x29, #16]
ldr s25, [x29, #24]
ldr s24, [x29, #32]
ldr s23, [x29, #40]
ldr s22, [x29, #48]
ldr s21, [x29, #56]
ldr s20, [x29, #64]
ldr s19, [x29, #72]
ldr x28, [x29, #80]
ldr x27, [x29, #88]
ldr x26, [x29, #96]
ldr x25, [x29, #104]
ldr x24, [x29, #112]
ldr x23, [x29, #120]
ldr x22, [x29, #128]
ldr x21, [x29, #136]
ldr x20, [x29, #144]
ldr x19, [x29, #152]
ldr x30, [sp, #-8]
ldr x29, [sp, #-16]
ret x30
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
str s19, [sp, #-104]
str s20, [sp, #-112]
str s21, [sp, #-120]
str s22, [sp, #-128]
str s23, [sp, #-136]
str s24, [sp, #-144]
str s25, [sp, #-152]
str s26, [sp, #-160]
str s27, [sp, #-168]
str s28, [sp, #-176]
add x29, sp, #-176
.data
_AR_SIZE_2: .word 16
.align 3
.text
ldr w19, _AR_SIZE_2
sub sp, x29, w19
.data
_STR_CONST_3: .asciz "Enter matrix 1 of dim 2 x 2 x 2: \n"
.align 3
.text
ldr x19, =_STR_CONST_3
mov x0, x19
bl _write_str
.data
_INT_CONST_120: .word 0
_INT_CONST_121: .word 0
.align 3
.text
ldr x19, _INT_CONST_120
.data
_INT_CONST_122: .word 0
_INT_CONST_123: .word 0
.align 3
.text
ldr x20, _INT_CONST_122
sub x20, x29, x20
str w19, [x20, #0]
_FOR_6:
.data
_INT_CONST_124: .word 0
_INT_CONST_125: .word 0
.align 3
.text
ldr x19, _INT_CONST_124
sub x19, x29, x19
ldr w19, [x19, #0]
ldr x20, =_g_dim
ldr w20, [x20, #0]
cmp w19, w20
cset w19, lt
cmp w19, #0
beq _FOR_END_6
.data
_INT_CONST_126: .word 0
_INT_CONST_127: .word 0
.align 3
.text
ldr x19, _INT_CONST_126
.data
_INT_CONST_128: .word 4
_INT_CONST_129: .word 0
.align 3
.text
ldr x20, _INT_CONST_128
sub x20, x29, x20
str w19, [x20, #0]
_FOR_7:
.data
_INT_CONST_130: .word 4
_INT_CONST_131: .word 0
.align 3
.text
ldr x19, _INT_CONST_130
sub x19, x29, x19
ldr w19, [x19, #0]
ldr x20, =_g_dim
ldr w20, [x20, #0]
cmp w19, w20
cset w19, lt
cmp w19, #0
beq _FOR_END_7
.data
_INT_CONST_132: .word 0
_INT_CONST_133: .word 0
.align 3
.text
ldr x19, _INT_CONST_132
.data
_INT_CONST_134: .word 8
_INT_CONST_135: .word 0
.align 3
.text
ldr x20, _INT_CONST_134
sub x20, x29, x20
str w19, [x20, #0]
_FOR_8:
.data
_INT_CONST_136: .word 8
_INT_CONST_137: .word 0
.align 3
.text
ldr x19, _INT_CONST_136
sub x19, x29, x19
ldr w19, [x19, #0]
ldr x20, =_g_dim
ldr w20, [x20, #0]
cmp w19, w20
cset w19, lt
cmp w19, #0
beq _FOR_END_8
bl _read_int
mov w19, w0
ldr x20, =_g_a
mov x21, #0
.data
_INT_CONST_138: .word 2
_INT_CONST_139: .word 0
.align 3
.text
ldr x22, _INT_CONST_138
mul x21, x21, x22
.data
_INT_CONST_140: .word 0
_INT_CONST_141: .word 0
.align 3
.text
ldr x22, _INT_CONST_140
sub x22, x29, x22
ldr w22, [x22, #0]
lsl x22, x22, #2
add x21, x21, x22
.data
_INT_CONST_142: .word 2
_INT_CONST_143: .word 0
.align 3
.text
ldr x22, _INT_CONST_142
mul x21, x21, x22
.data
_INT_CONST_144: .word 4
_INT_CONST_145: .word 0
.align 3
.text
ldr x22, _INT_CONST_144
sub x22, x29, x22
ldr w22, [x22, #0]
lsl x22, x22, #2
add x21, x21, x22
.data
_INT_CONST_146: .word 2
_INT_CONST_147: .word 0
.align 3
.text
ldr x22, _INT_CONST_146
mul x21, x21, x22
.data
_INT_CONST_148: .word 8
_INT_CONST_149: .word 0
.align 3
.text
ldr x22, _INT_CONST_148
sub x22, x29, x22
ldr w22, [x22, #0]
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_INT_CONST_150: .word 8
_INT_CONST_151: .word 0
.align 3
.text
ldr x19, _INT_CONST_150
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_152: .word 1
_INT_CONST_153: .word 0
.align 3
.text
ldr x20, _INT_CONST_152
add w19, w19, w20
.data
_INT_CONST_154: .word 8
_INT_CONST_155: .word 0
.align 3
.text
ldr x20, _INT_CONST_154
sub x20, x29, x20
str w19, [x20, #0]
b _FOR_8
_FOR_END_8:
.data
_INT_CONST_156: .word 4
_INT_CONST_157: .word 0
.align 3
.text
ldr x19, _INT_CONST_156
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_158: .word 1
_INT_CONST_159: .word 0
.align 3
.text
ldr x20, _INT_CONST_158
add w19, w19, w20
.data
_INT_CONST_160: .word 4
_INT_CONST_161: .word 0
.align 3
.text
ldr x20, _INT_CONST_160
sub x20, x29, x20
str w19, [x20, #0]
b _FOR_7
_FOR_END_7:
.data
_INT_CONST_162: .word 0
_INT_CONST_163: .word 0
.align 3
.text
ldr x19, _INT_CONST_162
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_164: .word 1
_INT_CONST_165: .word 0
.align 3
.text
ldr x20, _INT_CONST_164
add w19, w19, w20
.data
_INT_CONST_166: .word 0
_INT_CONST_167: .word 0
.align 3
.text
ldr x20, _INT_CONST_166
sub x20, x29, x20
str w19, [x20, #0]
b _FOR_6
_FOR_END_6:
.data
_STR_CONST_4: .asciz "Enter matrix 2 of dim 2 x 2 x 2 : \n"
.align 3
.text
ldr x19, =_STR_CONST_4
mov x0, x19
bl _write_str
.data
_INT_CONST_168: .word 0
_INT_CONST_169: .word 0
.align 3
.text
ldr x19, _INT_CONST_168
.data
_INT_CONST_170: .word 0
_INT_CONST_171: .word 0
.align 3
.text
ldr x20, _INT_CONST_170
sub x20, x29, x20
str w19, [x20, #0]
_FOR_9:
.data
_INT_CONST_172: .word 0
_INT_CONST_173: .word 0
.align 3
.text
ldr x19, _INT_CONST_172
sub x19, x29, x19
ldr w19, [x19, #0]
ldr x20, =_g_dim
ldr w20, [x20, #0]
cmp w19, w20
cset w19, lt
cmp w19, #0
beq _FOR_END_9
.data
_INT_CONST_174: .word 0
_INT_CONST_175: .word 0
.align 3
.text
ldr x19, _INT_CONST_174
.data
_INT_CONST_176: .word 4
_INT_CONST_177: .word 0
.align 3
.text
ldr x20, _INT_CONST_176
sub x20, x29, x20
str w19, [x20, #0]
_FOR_10:
.data
_INT_CONST_178: .word 4
_INT_CONST_179: .word 0
.align 3
.text
ldr x19, _INT_CONST_178
sub x19, x29, x19
ldr w19, [x19, #0]
ldr x20, =_g_dim
ldr w20, [x20, #0]
cmp w19, w20
cset w19, lt
cmp w19, #0
beq _FOR_END_10
.data
_INT_CONST_180: .word 0
_INT_CONST_181: .word 0
.align 3
.text
ldr x19, _INT_CONST_180
.data
_INT_CONST_182: .word 8
_INT_CONST_183: .word 0
.align 3
.text
ldr x20, _INT_CONST_182
sub x20, x29, x20
str w19, [x20, #0]
_FOR_11:
.data
_INT_CONST_184: .word 8
_INT_CONST_185: .word 0
.align 3
.text
ldr x19, _INT_CONST_184
sub x19, x29, x19
ldr w19, [x19, #0]
ldr x20, =_g_dim
ldr w20, [x20, #0]
cmp w19, w20
cset w19, lt
cmp w19, #0
beq _FOR_END_11
bl _read_int
mov w19, w0
ldr x20, =_g_b
mov x21, #0
.data
_INT_CONST_186: .word 2
_INT_CONST_187: .word 0
.align 3
.text
ldr x22, _INT_CONST_186
mul x21, x21, x22
.data
_INT_CONST_188: .word 0
_INT_CONST_189: .word 0
.align 3
.text
ldr x22, _INT_CONST_188
sub x22, x29, x22
ldr w22, [x22, #0]
lsl x22, x22, #2
add x21, x21, x22
.data
_INT_CONST_190: .word 2
_INT_CONST_191: .word 0
.align 3
.text
ldr x22, _INT_CONST_190
mul x21, x21, x22
.data
_INT_CONST_192: .word 4
_INT_CONST_193: .word 0
.align 3
.text
ldr x22, _INT_CONST_192
sub x22, x29, x22
ldr w22, [x22, #0]
lsl x22, x22, #2
add x21, x21, x22
.data
_INT_CONST_194: .word 2
_INT_CONST_195: .word 0
.align 3
.text
ldr x22, _INT_CONST_194
mul x21, x21, x22
.data
_INT_CONST_196: .word 8
_INT_CONST_197: .word 0
.align 3
.text
ldr x22, _INT_CONST_196
sub x22, x29, x22
ldr w22, [x22, #0]
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_INT_CONST_198: .word 8
_INT_CONST_199: .word 0
.align 3
.text
ldr x19, _INT_CONST_198
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_200: .word 1
_INT_CONST_201: .word 0
.align 3
.text
ldr x20, _INT_CONST_200
add w19, w19, w20
.data
_INT_CONST_202: .word 8
_INT_CONST_203: .word 0
.align 3
.text
ldr x20, _INT_CONST_202
sub x20, x29, x20
str w19, [x20, #0]
b _FOR_11
_FOR_END_11:
.data
_INT_CONST_204: .word 4
_INT_CONST_205: .word 0
.align 3
.text
ldr x19, _INT_CONST_204
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_206: .word 1
_INT_CONST_207: .word 0
.align 3
.text
ldr x20, _INT_CONST_206
add w19, w19, w20
.data
_INT_CONST_208: .word 4
_INT_CONST_209: .word 0
.align 3
.text
ldr x20, _INT_CONST_208
sub x20, x29, x20
str w19, [x20, #0]
b _FOR_10
_FOR_END_10:
.data
_INT_CONST_210: .word 0
_INT_CONST_211: .word 0
.align 3
.text
ldr x19, _INT_CONST_210
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_212: .word 1
_INT_CONST_213: .word 0
.align 3
.text
ldr x20, _INT_CONST_212
add w19, w19, w20
.data
_INT_CONST_214: .word 0
_INT_CONST_215: .word 0
.align 3
.text
ldr x20, _INT_CONST_214
sub x20, x29, x20
str w19, [x20, #0]
b _FOR_9
_FOR_END_9:
add sp, sp, #-0
bl _start_arraymult
add sp, sp, #0
.data
_INT_CONST_216: .word 0
_INT_CONST_217: .word 0
.align 3
.text
ldr x19, _INT_CONST_216
mov w0, w19
b _epilogue_MAIN
_epilogue_MAIN:
add sp, x29, #176
ldr s28, [x29, #0]
ldr s27, [x29, #8]
ldr s26, [x29, #16]
ldr s25, [x29, #24]
ldr s24, [x29, #32]
ldr s23, [x29, #40]
ldr s22, [x29, #48]
ldr s21, [x29, #56]
ldr s20, [x29, #64]
ldr s19, [x29, #72]
ldr x28, [x29, #80]
ldr x27, [x29, #88]
ldr x26, [x29, #96]
ldr x25, [x29, #104]
ldr x24, [x29, #112]
ldr x23, [x29, #120]
ldr x22, [x29, #128]
ldr x21, [x29, #136]
ldr x20, [x29, #144]
ldr x19, [x29, #152]
ldr x30, [sp, #-8]
ldr x29, [sp, #-16]
ret x30
