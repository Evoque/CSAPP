/*
 * echo - read and echo text lines until client closes connection
 */
/* $begin echo */
#include "../csapp.h"

void echo(int connfd) {
  size_t n;
  char buf[MAXLINE];
  rio_t rio;

  Rio_readinitb(&rio, connfd);
 
  char hello[5] = "hello";
  while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) { // line:netp:echo:eof
    printf("server received %d bytes\n", (int)n);
    Fputs(buf, stdout);
    Rio_writen(connfd, buf, n);
  }
}
/* $end echo */
