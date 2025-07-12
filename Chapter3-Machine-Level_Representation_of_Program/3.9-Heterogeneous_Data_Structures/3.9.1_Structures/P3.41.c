

struct test {
    short *p; 
    struct {
        short x;
        short y;
    } s;
    struct test *next;
}

// The following procedure (with some expressions omitted) operates on this structure:

void st_init (struct test *st) {
    st->s.y = st->s.x;
    st->p = &(st->s.y);
    st->next = st;
}

// A. What are the offsets (in bytes) of the following fields?
p: 0
s.x: 8
s.y: 10
next: 12

// B. How many total bytes does the structure require?
20

// C. The compiler generates the following assembly code for st_init:
void st_init(struct test *st)
st in %rdi

st_init:
    movl 8(%rdi), %eax    - st.x -> %eax
    movl %eax, 10(%rdi)   - %eax -> st.y
    leaq 10(%rdi), %rax   - &st.y -> %rax
    movq %rax, (%rdi)     - %rax -> st.p
    movq %rdi, 12(%rdi)   - %rdi -> st.next
    ret


