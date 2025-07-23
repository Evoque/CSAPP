- [x] getaddrinfo -> struct addrinfo **result: 指向`struct addrinfo`指针的指针；
> 双指针入参，是为了在函数内部修改指针的地址（解构赋值）
- [x] echo例子中用了MAXLINE作为server每次读取的长度，如果内容超长了，怎么办？
> 自己的demo里，内容超长可能会被截断或者其他异常，在HTTP中，因为有Content-Length, Content-Length仅包括Reponse Body的长度。
- [ ] 理解bit bit mask
- [x] stdin, stdout, stderr: 是进程独立的还是进程共享的？
> 完全独立的进程的stdin, stdout, stderr应该是独立的
- [ ] 同一个file，被连续进行输入/输出操作时的限制：
  1. 输出函数之后的输入函数：输出函数之后，要调用fflush, fseek, fsetpos, rewind; fflush清空缓冲区，后三者重新设置三者的文件位置；
  2. 输入函数之后的输出参数：在输入函数未遇到EOF时，中间要插入fseek, fsetpos或者rewind.
    2.1 The only way to work around is to open two streams on the same socket descriptor, reading & writing.
    ```c
      FILE *fpin, *fpout;
      fpin = fdopen(sockfd, "r");
      fpout = fdopen(sockfd, "w");
    ```
    但是这种方法在close的时候，后close的会报异常。This is not a problem for sequential programs, but closing an already closed descriptor in a threaded program is a recipe for disaster.
    ==> RIO解决了上述问题？？
- [ ] 如何查看一个服务器的连接池？