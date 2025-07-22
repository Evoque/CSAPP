- [x] getaddrinfo -> struct addrinfo **result: 指向`struct addrinfo`指针的指针；
> 双指针入参，是为了在函数内部修改指针的地址
- [ ] echo例子中用了MAXLINE作为server每次读取的长度，如果内容超长了，怎么办？
- [ ] 理解bit bit mask
- [ ] stdin, stdout, stderr: 是进程独立的还是进程共享的？
- [ ] HTTP如何升级，如1.0 -> 1.1 -> 2.0, proxy chain 如何升级？
- [ ] 使用MAXLINE & MAXBUF: 如果内容超过这个长度该怎么办？
- [ ] 读的时候（Rio_readlineb）使用&rio， 写的时候直接写fd（Rio_writen(connfd, buf, n)）？如下限制
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