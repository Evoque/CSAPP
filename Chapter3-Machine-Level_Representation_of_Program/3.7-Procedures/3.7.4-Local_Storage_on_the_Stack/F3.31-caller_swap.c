#include <stdio.h>

long swap_add(long *xp, long *yp)
{
    long x = *xp;
    long y = *yp;
    *xp = y;
    *yp = x;
    return x + y;
}

/**
 * The run-time stack provides a simple mechanism for allocating local storage when
 * it is required and deallocating it when the function completes.
 */
long caller()
{
    /**
     * subq $16, %rsp         - Allocate 16 bytes for stack frame
     * movq $534, (%rsp)      - Store 534 in arg1
     * movq $1057, 8(%rsp)    - Store 1057 in arg2
     */
    long arg1 = 534;
    long arg2 = 1057;
    /**
     * leaq 8(%rsp), %rdi    - Compute &arg2 as second argument
     * movq %rsp, %rdi       - Compute &arg1 as first argument
     * call swap_add         - Call swap_add(&arg1, &arg2)
     */
    long sum = swap_add(&arg1, &arg2);
    /**
     * movq (%rsp), %rdx     - Get arg1
     * subq 8(%rsp), %rdx    - Compute diff = arg1 - arg2
     * imulq %rdx, %rax      - Compute sum * diff
     * addq $16, %rsp        - Deallocate stack frame
     * ret                   - Return
     */
    long diff = arg1 - arg2;
    return sum * diff;
}

int main()
{
    long result = caller();
    printf("result: %ld\n", result);
    return 0;
}