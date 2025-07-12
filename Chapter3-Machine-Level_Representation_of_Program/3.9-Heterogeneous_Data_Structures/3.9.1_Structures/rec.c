

struct rect {
    int i;
    int j;
    int a[2];
    int *p;
}

r->p = &r->a[r->i + r->j];

/**
 * Registers: r in %rdi
1 movl 4(%rdi), %eax Get r->j
2 addl (%rdi), %eax Add r->i
3 cltq Extend to 8 bytes
4 leaq 8(%rdi,%rax,4), %rax Compute &r->a[r->i + r->j]
5 movq %rax, 16(%rdi) Store in r->p
 * 
 */

/**
 * Registers: r in %rdi
 * movl 4(%rdi), %eax   -- Get r->j
 * addl (%rdi),  %eas   -- Add r->i
 * cltq                 -- Extend to 8 bytes
 * leaq 8(%rdi, %rax, 4), %rax  -- Compute &r->a[r->i + r->j]
 * movq %rax, 16(%rdi)  -- Store in r->p
 */