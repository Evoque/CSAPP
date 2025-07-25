/**
 * Practice Problem 3.34
 * 
 * Consider a funciton P, which generates local values, named a0-a8. 
 * It then calls function Q using these generated values as arguments. 
 * GCC produces the following code for the first part of P:
 */

 /**
  * long P(long x)
  * x in %rdi
  *1 P:
  *2     pushq %r15
  *3     pushq %r14
  *4     pushq %r13
  *5     pushq %r12
  *6     pushq %rbp
  *7     pushq %rbx
  *8     subq %24, %rsp
  *9     movq %rdi, %rbx
  *10    leaq 1(%rdi), %r15
  *11    leaq 2(%rdi), %r14
  *12    leaq 3(%rdi), %r13
  *13    leaq 4(%rdi), %r12
  *14    leaq 5(%rdi), %rbp
  *15    leaq 6(%rdi), %rbx
  *16    movq %rax, (%rsp)
  *17    leaq 7(%rdi), %rdx
  *18    movq %rdx, 8(%rsp)
  *19    movl $0, %eax
  *20    call Q
  */

// A. Identify which local values get stored in callee-saved registers.
// We can see that lines 9-14 save local values a0-a5 into callee-saved registers %rbx - %rbp respectively.

// B. Identify which local values get stored on the stack.
// a6 - line16, a7 - line18

// C. Explain why the program could not store all of the local values in callee-saved registers.
// After storing six local variables, the program has used up the supply of callee-saved registers. It stores
// the remaining two local values on the stack.