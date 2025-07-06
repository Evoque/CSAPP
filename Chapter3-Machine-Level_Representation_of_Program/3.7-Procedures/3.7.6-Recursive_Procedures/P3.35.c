

// For a C function having the general structure: 
long rfun(unsigned long x)
{
    /** x in %rdi */
    /**
     * pushq %rbx       - 将%rbx入栈，有值无值无所谓
     * movq %rdi, %rbx  - Store x in callee-saved register
     * movl $0, %eax    - Set return value = 0
     * testq %rdi, %rdi - Compare x:0
     * je .L2           - If ==, goto done
     */
    if (x == 0)
        return 0;

    /**
     * shrq $2, %rdi
     */
    unsigned long nx = x >> 2;

    /**
     * call rfun    - Call rfun(nx);
     */
    long rv = rfun(nx);

    /**
     * addq %rbx, %rax
     */
    return x + rv;
}

// A. What value does rfun store in the callee-saved register %rbx?
// x

// B. Fill in the missing expressions in the C code shown above.
// finish, see above