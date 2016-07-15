#Usage
1. Compile
`gcc -o test test.c`
2. Run multiply times
./test

Is the adress of target the same? ==> ASLR is off
Else ==> ASLR is on

This simple test program verifies that ASLR works probably or is disabled probably

You can also check the config:

cat /proc/sys/kernel/randomize_va_space

Set this file to "0" to turn ASLR off ;)
