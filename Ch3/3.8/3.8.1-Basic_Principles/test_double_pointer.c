

#include <stdio.h>

int main()
{
    int a = 10;
    int *p = &a;
    int **pp = &p;

    printf("a = %d\n", a);       // => 10
    printf("*p = %d\n", *p);     // => 10, 解构'*p',得到a的值
    printf("p = %p\n", p);       // => 0x16dca6f58, 即a的存储地址
    printf("*pp = %p\n", *pp);   // => 0x16dca6f58, 一次解构p,得到指针p，即与上面相等
    printf("**pp = %d\n", **pp); // => 10, 两次解构pp, 得到10， 和p的一次解构一样
    printf("pp = %p\n", pp);     // => 0x16dca6f50, pp指向的地址， 即存储指针p信息的地址

    return 0;
}