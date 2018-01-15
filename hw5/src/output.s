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
_AR_SIZE_0: .word 32
.align 3
.text
ldr w19, _AR_SIZE_0
sub sp, x29, w19
.data
_INT_CONST_0: .word 8
.align 3
.text
ldr x19, _INT_CONST_0
.data
_INT_CONST_1: .word 8
.align 3
.text
ldr x20, _INT_CONST_1
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_2: .word 8
.align 3
.text
ldr x19, _INT_CONST_2
sub x19, x29, x19
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
_INT_CONST_3: .word 1
.align 3
.text
ldr x19, _INT_CONST_3
.data
_INT_CONST_4: .word 0
.align 3
.text
ldr x20, _INT_CONST_4
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_5: .word 2
.align 3
.text
ldr x19, _INT_CONST_5
.data
_INT_CONST_6: .word 4
.align 3
.text
ldr x20, _INT_CONST_6
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_7: .word 3
.align 3
.text
ldr x19, _INT_CONST_7
.data
_INT_CONST_8: .word 8
.align 3
.text
ldr x20, _INT_CONST_8
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_9: .word 0
.align 3
.text
ldr x19, _INT_CONST_9
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_10: .word 4
.align 3
.text
ldr x20, _INT_CONST_10
sub x20, x29, x20
ldr w20, [x20, #0]
mul w19, w19, w20
.data
_INT_CONST_11: .word 8
.align 3
.text
ldr x20, _INT_CONST_11
sub x20, x29, x20
ldr w20, [x20, #0]
.data
_INT_CONST_12: .word 4
.align 3
.text
ldr x21, _INT_CONST_12
mul w20, w20, w21
sub w19, w19, w20
.data
_INT_CONST_13: .word 5
.align 3
.text
ldr x20, _INT_CONST_13
sub w19, w19, w20
.data
_INT_CONST_14: .word 8
.align 3
.text
ldr x20, _INT_CONST_14
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_15: .word 8
.align 3
.text
ldr x19, _INT_CONST_15
sub x19, x29, x19
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_1: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_1
mov x0, x19
bl _write_str
.data
_FLOAT_CONST_0: .float 7.200000
.align 3
.text
ldr s19, _FLOAT_CONST_0
.data
_INT_CONST_16: .word 20
.align 3
.text
ldr x20, _INT_CONST_16
sub x20, x29, x20
str s19, [x20, #0]
.data
_INT_CONST_17: .word 20
.align 3
.text
ldr x19, _INT_CONST_17
sub x19, x29, x19
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_2: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_2
mov x0, x19
bl _write_str
.data
_FLOAT_CONST_1: .float 1.000000
.align 3
.text
ldr s19, _FLOAT_CONST_1
.data
_INT_CONST_18: .word 12
.align 3
.text
ldr x20, _INT_CONST_18
sub x20, x29, x20
str s19, [x20, #0]
.data
_FLOAT_CONST_2: .float 2.000000
.align 3
.text
ldr s19, _FLOAT_CONST_2
.data
_INT_CONST_19: .word 16
.align 3
.text
ldr x20, _INT_CONST_19
sub x20, x29, x20
str s19, [x20, #0]
.data
_FLOAT_CONST_3: .float 3.000000
.align 3
.text
ldr s19, _FLOAT_CONST_3
.data
_INT_CONST_20: .word 20
.align 3
.text
ldr x20, _INT_CONST_20
sub x20, x29, x20
str s19, [x20, #0]
.data
_INT_CONST_21: .word 12
.align 3
.text
ldr x19, _INT_CONST_21
sub x19, x29, x19
ldr s19, [x19, #0]
.data
_INT_CONST_22: .word 16
.align 3
.text
ldr x20, _INT_CONST_22
sub x20, x29, x20
ldr s20, [x20, #0]
fmul s19, s19, s20
.data
_INT_CONST_23: .word 20
.align 3
.text
ldr x20, _INT_CONST_23
sub x20, x29, x20
ldr s20, [x20, #0]
.data
_FLOAT_CONST_4: .float 4.000000
.align 3
.text
ldr s21, _FLOAT_CONST_4
fmul s20, s20, s21
fsub s19, s19, s20
.data
_FLOAT_CONST_5: .float 5.000000
.align 3
.text
ldr s20, _FLOAT_CONST_5
fsub s19, s19, s20
.data
_INT_CONST_24: .word 20
.align 3
.text
ldr x20, _INT_CONST_24
sub x20, x29, x20
str s19, [x20, #0]
.data
_INT_CONST_25: .word 20
.align 3
.text
ldr x19, _INT_CONST_25
sub x19, x29, x19
ldr s19, [x19, #0]
fmov s0, s19
bl _write_float
.data
_STR_CONST_3: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_3
mov x0, x19
bl _write_str
.data
_INT_CONST_26: .word 0
.align 3
.text
ldr x19, _INT_CONST_26
.data
_INT_CONST_27: .word 8
.align 3
.text
ldr x20, _INT_CONST_27
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_28: .word 8
.align 3
.text
ldr x19, _INT_CONST_28
sub x19, x29, x19
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
.data
_INT_CONST_29: .word 1
.align 3
.text
ldr x19, _INT_CONST_29
.data
_INT_CONST_30: .word 8
.align 3
.text
ldr x20, _INT_CONST_30
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_31: .word 8
.align 3
.text
ldr x19, _INT_CONST_31
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
_INT_CONST_32: .word 1
.align 3
.text
ldr x19, _INT_CONST_32
.data
_INT_CONST_33: .word 8
.align 3
.text
ldr x20, _INT_CONST_33
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_34: .word 8
.align 3
.text
ldr x19, _INT_CONST_34
sub x19, x29, x19
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_6: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_6
mov x0, x19
bl _write_str
.data
_INT_CONST_35: .word 1
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
_INT_CONST_37: .word 8
.align 3
.text
ldr x19, _INT_CONST_37
sub x19, x29, x19
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_7: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_7
mov x0, x19
bl _write_str
.data
_INT_CONST_38: .word 1
.align 3
.text
ldr x19, _INT_CONST_38
.data
_INT_CONST_39: .word 8
.align 3
.text
ldr x20, _INT_CONST_39
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_40: .word 8
.align 3
.text
ldr x19, _INT_CONST_40
sub x19, x29, x19
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
.data
_INT_CONST_41: .word 0
.align 3
.text
ldr x19, _INT_CONST_41
.data
_INT_CONST_42: .word 8
.align 3
.text
ldr x20, _INT_CONST_42
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_43: .word 8
.align 3
.text
ldr x19, _INT_CONST_43
sub x19, x29, x19
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
.data
_INT_CONST_44: .word 0
.align 3
.text
ldr x19, _INT_CONST_44
.data
_INT_CONST_45: .word 8
.align 3
.text
ldr x20, _INT_CONST_45
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_46: .word 8
.align 3
.text
ldr x19, _INT_CONST_46
sub x19, x29, x19
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_10: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_10
mov x0, x19
bl _write_str
.data
_INT_CONST_47: .word 1
.align 3
.text
ldr x19, _INT_CONST_47
.data
_INT_CONST_48: .word 8
.align 3
.text
ldr x20, _INT_CONST_48
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_49: .word 8
.align 3
.text
ldr x19, _INT_CONST_49
sub x19, x29, x19
ldr w19, [x19, #0]
mov w0, w19
bl _write_int
.data
_STR_CONST_11: .asciz "\n"
.align 3
.text
ldr x19, =_STR_CONST_11
mov x0, x19
bl _write_str
.data
_INT_CONST_50: .word 1
.align 3
.text
ldr x19, _INT_CONST_50
.data
_INT_CONST_51: .word 8
.align 3
.text
ldr x20, _INT_CONST_51
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_52: .word 8
.align 3
.text
ldr x19, _INT_CONST_52
sub x19, x29, x19
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
.data
_INT_CONST_53: .word 0
.align 3
.text
ldr x19, _INT_CONST_53
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
