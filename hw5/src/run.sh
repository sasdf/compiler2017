#!/bin/bash 
$1 $2
aarch64-linux-gnu-gcc -O0 -g -static main.S
