



long rfact(long n) 
{
    /** n in %rdi */
    /**
     * pushq %rbx      - Save %rbx
     * movq %rdi, %rbx - Store n in callee-saved register 
     * movl $1, %eax   - Set return value = 1
     * cmpq $1, %rdi   - Compare n:1
     * jle .L35        - If <=, goto done
     */
    long result; 
    if (n <= 1)
        result = 1;
    else
        /**
         * leaq -1(%rdi), %rdi - Compute n-1
         * call rfact          - Call rfact(n-1)
         * imulq %rbx, %rax    - Multiply result by n
         */
        result = n * rfact(n-1);
    /**
     * .L35: 
     *    popq  %rbx      - Restore %rbx
     *    ret          
     */
    return result;
}