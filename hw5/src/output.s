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
_AR_SIZE_0: .word 16
.align 3
.text
ldr w19, _AR_SIZE_0
sub sp, x29, w19
.data
_INT_CONST_0: .word 1
.align 3
.text
ldr x19, _INT_CONST_0
.data
_INT_CONST_1: .word 4
.align 3
.text
ldr x20, _INT_CONST_1
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_2: .word 0
.align 3
.text
ldr x19, _INT_CONST_2
.data
_INT_CONST_3: .word 4
.align 3
.text
ldr x20, _INT_CONST_3
sub x20, x29, x20
str w19, [x20, #0]
_IF_1:
.data
_INT_CONST_4: .word 4
.align 3
.text
ldr x19, _INT_CONST_4
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_5: .word 4
.align 3
.text
ldr x20, _INT_CONST_5
sub x20, x29, x20
ldr w20, [x20, #0]
cmp w19, w20
cset w19, gt
cmp w19, #0
beq _ELSE_1
.data
_STR_CONST_0: .asciz "correct\n"
.align 3
.text
ldr x19, =_STR_CONST_0
mov x0, x19
bl _write_str
b _END_IF_1
_ELSE_1:
.data
_STR_CONST_1: .asciz "wrong\n"
.align 3
.text
ldr x19, =_STR_CONST_1
mov x0, x19
bl _write_str
_END_IF_1:
_IF_2:
.data
_INT_CONST_6: .word 4
.align 3
.text
ldr x19, _INT_CONST_6
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_7: .word 4
.align 3
.text
ldr x20, _INT_CONST_7
sub x20, x29, x20
ldr w20, [x20, #0]
cmp w19, w20
cset w19, lt
cmp w19, #0
beq _ELSE_2
.data
_STR_CONST_2: .asciz "wrong\n"
.align 3
.text
ldr x19, =_STR_CONST_2
mov x0, x19
bl _write_str
b _END_IF_2
_ELSE_2:
.data
_STR_CONST_3: .asciz "correct\n"
.align 3
.text
ldr x19, =_STR_CONST_3
mov x0, x19
bl _write_str
_END_IF_2:
_IF_3:
.data
_INT_CONST_8: .word 4
.align 3
.text
ldr x19, _INT_CONST_8
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_9: .word 4
.align 3
.text
ldr x20, _INT_CONST_9
sub x20, x29, x20
ldr w20, [x20, #0]
cmp w19, w20
cset w19, eq
cmp w19, #0
beq _ELSE_3
.data
_STR_CONST_4: .asciz "wrong\n"
.align 3
.text
ldr x19, =_STR_CONST_4
mov x0, x19
bl _write_str
b _END_IF_3
_ELSE_3:
.data
_STR_CONST_5: .asciz "correct\n"
.align 3
.text
ldr x19, =_STR_CONST_5
mov x0, x19
bl _write_str
_END_IF_3:
_IF_4:
.data
_INT_CONST_10: .word 4
.align 3
.text
ldr x19, _INT_CONST_10
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_11: .word 4
.align 3
.text
ldr x20, _INT_CONST_11
sub x20, x29, x20
ldr w20, [x20, #0]
cmp w19, w20
cset w19, ne
cmp w19, #0
beq _ELSE_4
.data
_STR_CONST_6: .asciz "correct\n"
.align 3
.text
ldr x19, =_STR_CONST_6
mov x0, x19
bl _write_str
b _END_IF_4
_ELSE_4:
.data
_STR_CONST_7: .asciz "wrong\n"
.align 3
.text
ldr x19, =_STR_CONST_7
mov x0, x19
bl _write_str
_END_IF_4:
.data
_FLOAT_CONST_0: .float 1.000000
.align 3
.text
ldr s19, _FLOAT_CONST_0
.data
_INT_CONST_12: .word 12
.align 3
.text
ldr x20, _INT_CONST_12
sub x20, x29, x20
str s19, [x20, #0]
.data
_FLOAT_CONST_1: .float 0.000000
.align 3
.text
ldr s19, _FLOAT_CONST_1
.data
_INT_CONST_13: .word 12
.align 3
.text
ldr x20, _INT_CONST_13
sub x20, x29, x20
str s19, [x20, #0]
_IF_5:
.data
_INT_CONST_14: .word 12
.align 3
.text
ldr x19, _INT_CONST_14
sub x19, x29, x19
ldr s19, [x19, #0]
.data
_INT_CONST_15: .word 12
.align 3
.text
ldr x20, _INT_CONST_15
sub x20, x29, x20
ldr s20, [x20, #0]
fcmp s19, s20
cset w19, gt
fcvtzs w19, s19
cmp w19, #0
beq _ELSE_5
.data
_STR_CONST_8: .asciz "correct\n"
.align 3
.text
ldr x19, =_STR_CONST_8
mov x0, x19
bl _write_str
b _END_IF_5
_ELSE_5:
.data
_STR_CONST_9: .asciz "wrong\n"
.align 3
.text
ldr x19, =_STR_CONST_9
mov x0, x19
bl _write_str
_END_IF_5:
_IF_6:
.data
_INT_CONST_16: .word 12
.align 3
.text
ldr x19, _INT_CONST_16
sub x19, x29, x19
ldr s19, [x19, #0]
.data
_INT_CONST_17: .word 12
.align 3
.text
ldr x20, _INT_CONST_17
sub x20, x29, x20
ldr s20, [x20, #0]
fcmp s19, s20
cset w19, lt
fcvtzs w19, s19
cmp w19, #0
beq _ELSE_6
.data
_STR_CONST_10: .asciz "wrong\n"
.align 3
.text
ldr x19, =_STR_CONST_10
mov x0, x19
bl _write_str
b _END_IF_6
_ELSE_6:
.data
_STR_CONST_11: .asciz "correct\n"
.align 3
.text
ldr x19, =_STR_CONST_11
mov x0, x19
bl _write_str
_END_IF_6:
_IF_7:
.data
_INT_CONST_18: .word 12
.align 3
.text
ldr x19, _INT_CONST_18
sub x19, x29, x19
ldr s19, [x19, #0]
.data
_INT_CONST_19: .word 12
.align 3
.text
ldr x20, _INT_CONST_19
sub x20, x29, x20
ldr s20, [x20, #0]
fcmp s19, s20
cset w19, ne
fcvtzs w19, s19
cmp w19, #0
beq _ELSE_7
.data
_STR_CONST_12: .asciz "correct\n"
.align 3
.text
ldr x19, =_STR_CONST_12
mov x0, x19
bl _write_str
b _END_IF_7
_ELSE_7:
.data
_STR_CONST_13: .asciz "wrong\n"
.align 3
.text
ldr x19, =_STR_CONST_13
mov x0, x19
bl _write_str
_END_IF_7:
_IF_8:
.data
_INT_CONST_20: .word 4
.align 3
.text
ldr x19, _INT_CONST_20
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_21: .word 4
.align 3
.text
ldr x20, _INT_CONST_21
sub x20, x29, x20
ldr w20, [x20, #0]
cmp w19, #0
cset w19, ne
cmp w20, #0
cset w20, ne
and w19, w19, w20
cmp w19, #0
beq _ELSE_8
.data
_STR_CONST_14: .asciz "wrong\n"
.align 3
.text
ldr x19, =_STR_CONST_14
mov x0, x19
bl _write_str
b _END_IF_8
_ELSE_8:
_END_IF_8:
_IF_9:
.data
_INT_CONST_22: .word 4
.align 3
.text
ldr x19, _INT_CONST_22
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_23: .word 4
.align 3
.text
ldr x20, _INT_CONST_23
sub x20, x29, x20
ldr w20, [x20, #0]
cmp w19, #0
cset w19, ne
cmp w20, #0
cset w20, ne
or w19, w19, w20
cmp w19, #0
beq _ELSE_9
.data
_STR_CONST_15: .asciz "correct\n"
.align 3
.text
ldr x19, =_STR_CONST_15
mov x0, x19
bl _write_str
b _END_IF_9
_ELSE_9:
_END_IF_9:
.data
_INT_CONST_24: .word 0
.align 3
.text
ldr x19, _INT_CONST_24
.data
_INT_CONST_25: .word 4
.align 3
.text
ldr x20, _INT_CONST_25
sub x20, x29, x20
str w19, [x20, #0]
_WHILE_10:
.data
_INT_CONST_26: .word 4
.align 3
.text
ldr x19, _INT_CONST_26
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_27: .word 10
.align 3
.text
ldr x20, _INT_CONST_27
cmp w19, w20
cset w19, lt
cmp w19, #0
beq _WHILE_END_10
.data
_STR_CONST_16: .asciz "correct: "
.align 3
.text
ldr x19, =_STR_CONST_16
mov x0, x19
bl _write_str
.data
_INT_CONST_28: .word 4
.align 3
.text
ldr x19, _INT_CONST_28
sub x19, x29, x19
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_17: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_17
mov x0, x19
bl _write_str
.data
_INT_CONST_29: .word 4
.align 3
.text
ldr x19, _INT_CONST_29
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_30: .word 1
.align 3
.text
ldr x20, _INT_CONST_30
add w19, w19, w20
.data
_INT_CONST_31: .word 4
.align 3
.text
ldr x20, _INT_CONST_31
sub x20, x29, x20
str w19, [x20, #0]
b _WHILE_10
_WHILE_END_10:
_IF_11:
.data
_INT_CONST_32: .word 4
.align 3
.text
ldr x19, _INT_CONST_32
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_33: .word 10
.align 3
.text
ldr x20, _INT_CONST_33
cmp w19, w20
cset w19, eq
cmp w19, #0
beq _ELSE_11
.data
_STR_CONST_18: .asciz "correct\n"
.align 3
.text
ldr x19, =_STR_CONST_18
mov x0, x19
bl _write_str
b _END_IF_11
_ELSE_11:
_END_IF_11:
.data
_INT_CONST_34: .word 0
.align 3
.text
ldr x19, _INT_CONST_34
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
