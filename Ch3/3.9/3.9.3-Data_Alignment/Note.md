


If we can guarantee that any `double` will be aligned to have its address be a multiple of 8,
then the value can be read or written with a single memory operation.

Alignment rule: any primitive object of *K* bytes must have an address that is *a multiple of K*.


**P3.44**
For each of the following structure declarations, determine the *offset* of each field, the total size of 
the structure, and its alignment requirement for x86-64:
A. *struct P1 {short i;int c;int *j; short *d;}*
i 后面插入2byte，保证c的地址是4的倍数，P1的size是: 2 + 2 + 4 + 8 + 8 = 24
B. *struct P2 { int i[2]; char c[8]; short s[4]; long *j;}*
整体的Size是32，size正好， 不需要alignment
D. *struct P4 { char w[16]; char *c[2] }*
==>  答案A竟然有错误，其他题不想写了。

**P3.45**
```c
struct {
    int *a;
    float b;
    char c;
    short d;
    long e;
    double f;
    int g;
    char *h;
} rec;
```
A. What are the byte offsets of all the fields in the structure?
a-[0,8] b-[8,12] c-[12.13] off-[13,14] d-[14,16] e-[16,24] f-[24,32] g-[32,36] off-[36,40] h-[40-48]
===》👹， 答案给出d的offset时16， 即c后面的off是[13,16]3个字节
B. What is the total size of the structure?
48 bytes
C. Rearrange the fields of the structure to minimize wasted space, and then show the byte offsets 
and total size for the rearranged structure
把 h移动到前面，前面用g补成8的倍数；然后放其他的8， 再放其他的4， 再放其他的2， 将c放到最后
