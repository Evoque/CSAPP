#include <stdio.h>

void proc(long a1, long *a1p, 
          int  a2, int *a2p,
          short a3, short *a3p,
          char  a4, char *a4p)
{
    *a1p += a1;
    *a2p += a2;
    *a3p += a3;
    *a4p += a4;
}

/**
 * See the assembly code for stack frame
 * |---------------------------|
 * |   Return address          |
 * |---------------------------|[32]
 * |        x1                 |
 * |---------------------------|[24]
 * |x2 [20]|x3 [18]|x4 [17]|   |     -- 16 is empty
 * |---------------------------|[16]
 * | Argument 8=&x4            |
 * |---------------------------|[8]
 * |                    | 4  0 |    - 只用了1byte(4)-Argument 7
 * |---------------------------|[0] - Stack pointer %rsp 
 */
long call_proc(){
    /** Set up arguments to proc
     * subq $32, %rsp   - Allocate 32-byte stack frame 
     * @NOTE: 32-byte的分配很有意思，local var 会按照自身的size计算，而传递给proc的arg-7,arg-8直接分8bytes(不考虑参数值的size)
     * 故上图， 四个局部变量占用4bytes(16-32),两个args占用4bytes(0-8)
     */
    long x1 = 1;    // movq $1, 24(%rsp) - Store 1 in &x1
    int x2 = 2;     // movl $2, 20(%rsp) - Store 2 in &x2   
    short x3 = 3;   // movw $3, 18(%rsp) - Store 3 in &x3
    char x4 = 4;    // movb $4, 17(%rsp) - Store 4 in &x4

    /**
     * leaq 17(%rsp), %rax - Create &x4
     * movq %rax, 8(%rsp)  - Store &x4 as argument 8
     * movl $4, (%rsp)     - Store 4 as argument 7
     * leaq 18(%rsp), %r9  - Pass &x3 as argument 6
     * movl $3, %r8d       - Pass 3 as argument 5
     * leaq 20(%rsp), %rcx - Pass &x2 as argument 4
     * movl $2, %edx       - Pass 2 as argument 3
     * leaq 24(%rsp), %rsi - Pass &x1 as argument 2
     * movl $1, %edi       - Pass 1 as argument 1
     * call proc
     */
    proc(x1, &x1, x2, &x2, x3, &x3, x4, &x4);
    /** Retrieve changes to memory
     * movslq 20(%rsp), %rdx   - Get x2 and convert to long
     * addq 24(%rsp), %rdx     - Add x1 to x2
     * movswl 18(%rsp), %eax   - Get x3 and convert to int
     * movsbl 17(%rsp), %ecx   - Get x4 and convert to int 
     * subl %ecx, %eax         - Compute x3 - x4
     * cltq                    - Convert to long 
     * imulq %rdx, %rax        - Compute (x1+x2) * (x3-x4)
     * addq $32, %rsp          - Deallocate stack frame
     * ret                     - Return
     */
    return (x1 + x2) * (x3 - x4);
}

int main(){
    long result = call_proc();
    printf("result: %ld\n", result);
    return 0;
}