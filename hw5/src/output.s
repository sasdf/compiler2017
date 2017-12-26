.data
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
_AR_SIZE_0: .word 4768
.align 3
.text
ldr w19, _AR_SIZE_0
sub sp, x29, w19
.data
_INT_CONST_0: .word 10
.align 3
.text
ldr x19, _INT_CONST_0
.data
_INT_CONST_1: .word 0
.align 3
.text
ldr x20, _INT_CONST_1
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_2: .word 1111
.align 3
.text
ldr x19, _INT_CONST_2
.data
_INT_CONST_3: .word 720
.align 3
.text
ldr x20, _INT_CONST_3
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_4: .word 7122
.align 3
.text
ldr x19, _INT_CONST_4
.data
_INT_CONST_5: .word 724
.align 3
.text
ldr x20, _INT_CONST_5
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_6: .word 0
.align 3
.text
ldr x19, _INT_CONST_6
.data
_INT_CONST_7: .word 728
.align 3
.text
ldr x20, _INT_CONST_7
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_8: .word 6
.align 3
.text
ldr x19, _INT_CONST_8
.data
_INT_CONST_9: .word 732
.align 3
.text
ldr x20, _INT_CONST_9
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_10: .word 10
.align 3
.text
ldr x19, _INT_CONST_10
.data
_INT_CONST_11: .word 756
.align 3
.text
ldr x20, _INT_CONST_11
sub x20, x29, x20
str w19, [x20, #0]
.data
_FLOAT_CONST_0: .float 2.222000
.align 3
.text
ldr s19, _FLOAT_CONST_0
.data
_INT_CONST_12: .word 760
.align 3
.text
ldr x20, _INT_CONST_12
sub x20, x29, x20
str s19, [x20, #0]
.data
_INT_CONST_13: .word 10
.align 3
.text
ldr x19, _INT_CONST_13
.data
_INT_CONST_14: .word 764
.align 3
.text
ldr x20, _INT_CONST_14
sub x20, x29, x20
str w19, [x20, #0]
_WHILE_1:
.data
_INT_CONST_15: .word 728
.align 3
.text
ldr x19, _INT_CONST_15
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_16: .word 6
.align 3
.text
ldr x20, _INT_CONST_16
cmp w19, w20
cset w19, lt
cmp w19, #0
beq _WHILE_END_1
.data
_INT_CONST_17: .word 728
.align 3
.text
ldr x19, _INT_CONST_17
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_18: .word 1000
.align 3
.text
ldr x20, _INT_CONST_18
mul w19, w19, w20
.data
_INT_CONST_19: .word 732
.align 3
.text
ldr x20, _INT_CONST_19
sub x20, x29, x20
mov x21, #0
.data
_INT_CONST_20: .word 6
.align 3
.text
ldr x22, _INT_CONST_20
mul x21, x21, x22
.data
_INT_CONST_21: .word 728
.align 3
.text
ldr x22, _INT_CONST_21
sub x22, x29, x22
ldr w22, [x22, #0]
lsl x22, x22, #2
add x21, x21, x22
add x20, x20, x21
str w19, [x20, #0]
.data
_INT_CONST_22: .word 728
.align 3
.text
ldr x19, _INT_CONST_22
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_23: .word 1
.align 3
.text
ldr x20, _INT_CONST_23
add w19, w19, w20
.data
_INT_CONST_24: .word 728
.align 3
.text
ldr x20, _INT_CONST_24
sub x20, x29, x20
str w19, [x20, #0]
b _WHILE_1
_WHILE_END_1:
.data
_INT_CONST_25: .word 0
.align 3
.text
ldr x19, _INT_CONST_25
.data
_INT_CONST_26: .word 728
.align 3
.text
ldr x20, _INT_CONST_26
sub x20, x29, x20
str w19, [x20, #0]
_WHILE_2:
.data
_INT_CONST_27: .word 728
.align 3
.text
ldr x19, _INT_CONST_27
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_28: .word 6
.align 3
.text
ldr x20, _INT_CONST_28
cmp w19, w20
cset w19, lt
cmp w19, #0
beq _WHILE_END_2
.data
_INT_CONST_29: .word 732
.align 3
.text
ldr x19, _INT_CONST_29
sub x19, x29, x19
mov x20, #0
.data
_INT_CONST_30: .word 6
.align 3
.text
ldr x21, _INT_CONST_30
mul x20, x20, x21
.data
_INT_CONST_31: .word 728
.align 3
.text
ldr x21, _INT_CONST_31
sub x21, x29, x21
ldr w21, [x21, #0]
lsl x21, x21, #2
add x20, x20, x21
add x19, x19, x20
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_0: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_0
mov x0, x19
bl _write_str
.data
_INT_CONST_32: .word 728
.align 3
.text
ldr x19, _INT_CONST_32
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_33: .word 1
.align 3
.text
ldr x20, _INT_CONST_33
add w19, w19, w20
.data
_INT_CONST_34: .word 728
.align 3
.text
ldr x20, _INT_CONST_34
sub x20, x29, x20
str w19, [x20, #0]
b _WHILE_2
_WHILE_END_2:
.data
_STR_CONST_1: .asciz "===================\n"
.align 3
.text
ldr x19, =_STR_CONST_1
mov x0, x19
bl _write_str
.data
_INT_CONST_35: .word 720
.align 3
.text
ldr x19, _INT_CONST_35
sub x19, x29, x19
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_2: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_2
mov x0, x19
bl _write_str
.data
_INT_CONST_36: .word 724
.align 3
.text
ldr x19, _INT_CONST_36
sub x19, x29, x19
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_3: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_3
mov x0, x19
bl _write_str
.data
_INT_CONST_37: .word 760
.align 3
.text
ldr x19, _INT_CONST_37
sub x19, x29, x19
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_4: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_4
mov x0, x19
bl _write_str
.data
_INT_CONST_38: .word 756
.align 3
.text
ldr x19, _INT_CONST_38
sub x19, x29, x19
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
.data
_INT_CONST_39: .word 0
.align 3
.text
ldr x19, _INT_CONST_39
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
