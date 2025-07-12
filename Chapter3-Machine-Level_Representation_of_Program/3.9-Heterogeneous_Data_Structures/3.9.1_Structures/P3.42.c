
struct ACE {
    short v;
    struct ACE *p;
}

short test(struct ACE *ptr);

// => assembly code

short test(struct ACE *ptr) 
ptr in %rdi

test:
    movl  $1, %eax       // result = 1
    jmp .L2
.L3:
    imulq (%rdi), %rax  // result = result * ptr->v
    movq 2(%rdi), %rdi  // ptr->v = ptr->p.v
.L2:    
    testq %rdi, %rdi  // 判断是否为0
    jne .L3           // 不等于0，则跳转
    rep; ret

// A. Use your reverse engineering skills to write C code for test
short test(struct ACE *ptr) {
    short result = 1;
    while (ptr) {
        result *= ptr->v;
        ptr = ptr->p;
    }
    return result;
}

// B. Describe the data structure that this structure implements and the operation performed by test.
// We can see that each structure is an element in a singly linked list, with field v being the value 
// of the element and p being a pointer to the next element.
// Function fun computes the sum of the element values in the list.