#!/bin/bash 
./parser $1
aarch64-linux-gnu-gcc -O0 -g -static main.S
qemu-aarch64-static ./a.out
