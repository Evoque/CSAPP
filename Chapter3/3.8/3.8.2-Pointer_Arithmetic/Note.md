

if 'p' is a pointer to data of type 'T', and the value of 'p' is 'xp'.
'p + i': xp + L*i (L is T's size)

- 'AExpr' denoting an address, '*AExpr' gives the value at the address. 
- The expressions 'Expr' and '*&Expr' are therefore equivalent.
- The array reference 'A[i]' is identical to '*(A+i)'.(Computes the address and then accesses this memory location).


    Expression   Type      Value         Assembly code
    -------------------------------------------------------------
   E            int *     xe            movl %rdx, %rax
   E[0]         int       M[xe]         movl (%rdx), %eax
   E[i]         int       M[xe+4i]      movl (%rdx,%rcx,4), %eax
   &E[2]        int *     xe+8          leaq 8(%rdx), %rax
我  E+i-1        int *     xe+4(i-1)     leaq 4(i-1)(%rdx), %rax
答  -            -         -             leaq -4(%rdx,%rcx,4), %rax
我  *(E+i-3)     int       M[xe+4(i-3)]  movl (%rdx,%rcx,4(i-3)), %eax
答  -            -         -             movl -12(%rdx,%rcx,4), %eax
我  &E[i]-E      int x     4i(xe+4i-xe)  movl $4i, %eax
答  -            long      i             movq %rcx, %rax

最后一行的解释：The final example shows that one can compute the difference of two pointers within the same data structure, with the result being data having type long and value equal to `the difference of the two addresses divided by the size of the data type.`


## Practice Problem 3.37 
Suppose xp, the address of short integer array P, and long integer index i are stored
in registers %rdx and %rcx, respectively. For each of the following expressions, give
its type, a formula for its value, and an assembly-code implementation. The result
should be stored in register %rax if it is a pointer and register element %ax if it has
data type short.

Expression    Type      Value         Assembly code
------------------------------------------------------
P[1]          short     M[xp+2]       movw 2(%rdx), %ax
P+3+i         short *   xp+6+2i       leaq 6(%rdx,%rcx,2), %rax
P[i*6-5]      short     M[xp+12i-10]  movw -10(%rdx,%rcx,12), %ax
P[2]          short     M[xp+4]       movw 4(%rdx),%ax
&P[i+2]       short *   xp+2i+4       leaq 4(%rdx,%rcx,2), %rax