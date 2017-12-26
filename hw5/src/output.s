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
_AR_SIZE_0: .word 0
.align 3
.text
ldr w19, _AR_SIZE_0
sub sp, x29, w19
_WHILE_1:
.data
_INT_CONST_0: .word 0
.align 3
.text
ldr x19, _INT_CONST_0
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_1: .word 0
.align 3
.text
ldr x20, _INT_CONST_1
cmp w19, w20
cset w19, gt
cmp w19, #0
beq _WHILE_END_1
.data
_INT_CONST_2: .word 0
.align 3
.text
ldr x19, _INT_CONST_2
sub x19, x29, x19
ldr w19, [x19, #0]
.data
_INT_CONST_3: .word 1
.align 3
.text
ldr x20, _INT_CONST_3
sub w19, w19, w20
.data
_INT_CONST_4: .word 0
.align 3
.text
ldr x20, _INT_CONST_4
sub x20, x29, x20
str w19, [x20, #0]
.data
_INT_CONST_5: .word 0
.align 3
.text
ldr x20, _INT_CONST_5
sub x20, x29, x20
ldr w20, [x20, #0]
mov w0, w20
bl _write_int
b _WHILE_1
_WHILE_END_1:
.data
_INT_CONST_6: .word 0
.align 3
.text
ldr x20, _INT_CONST_6
mov w0, w20
add sp, x29, #-112
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
ldr x30, [sp, #8]
ldr x29, [sp, #16]
ret x30
