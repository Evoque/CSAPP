#include <stdio.h>

long Q(long t){
    return t + 2;
}

long P(long x, long y) 
{
    /** x in %rdi, y in %rsi */
    /**
     * pushq  %rbp    - Save %rbp
     * pushq  %rbx    - Save %rbx
     * subq $8, %rsp  - Align stack frame   @TODO: Align? $8?
     * @note: x86-64有16字节对齐(16-byte alignment-SIMD处理16/32/64字节数据)要求， 两个pushq 16字节，一个push return address 8字节，所以还差8字节。
     * movq %rdi, %rbp  - Save x
     * movq %rsi, %rdi  - Move y to first argument 
     * call Q           - Call Q(y)
     */
    long u = Q(y);
    /**
     * movq %rax, %rbx  - Save result
     * movq %rbp, %rdi  - Move x to first argument
     * call Q           - Call Q(x)
     */
    long v = Q(x);

    /**
     * addq %rbx, %rax  - Add saved Q(y) to Q(x)
     * addq $8, %rsp    - Deallocate last part of stack 
     * popq %rbx        - Restore %rbx
     * popq %rbp        - Restore %rbp
     * ret
     */
    return u + v;
}