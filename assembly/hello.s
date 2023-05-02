.section __DATA,__data
msg:
    .ascii "Hello, world!\n\0"

.section __TEXT,__text
.globl _main
_main:
    movq $0x2000004, %rax       # system call for write (syscall)
    movq $1, %rdi               # file descriptor (stdout)
    leaq msg(%rip), %rsi        # pointer to string to print
    movq $14, %rdx              # number of bytes to print
    syscall                     # invoke system call
    xorq %rax, %rax             # return 0
    ret                         # exit program
