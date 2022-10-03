.text

.globl _start

_start: # _start is the entry point known to the linker
    xor %ebp, %ebp            # effectively RBP := 0, mark the end of stack frames
    mov (%rsp), %edi          # get argc from the stack (implicitly zero-extended to 64-bit)
    lea 8(%rsp), %rsi         # take the address of argv from the stack
    lea 16(%rsp,%rdi,8), %rdx # take the address of envp from the stack
    xor %eax, %eax            # per ABI and compatibility with icc
    call main                 # %edi, %rsi, %rdx are the three args (of which first two are C standard) to main

    xor  %rdi, %rdi   # clean rdi
    mov  %eax, %edi   # copy eax to edi (syscall first arg)
    mov  $60, %eax    # exit
    syscall

