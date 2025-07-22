/*
 * echo - read and echo text lines until client closes connection
 */
/* $begin echo */
#include "csapp.h"
#include <string.h>

void echo(int connfd)
{
  size_t n;
  char buf[MAXLINE];
  rio_t rio;

  Rio_readinitb(&rio, connfd);

  char *resp = "Received.\n";
  while (1)
  {
    n = Rio_readlineb(&rio, buf, MAXLINE);
    if (n != 0)
    {
      // printf("server received: [%dbytes]->%s", (int)n, buf);
      // Rio_writen(connfd, buf, n);
      // Custom Response
      // Rio_writen(connfd, resp, strlen(resp));
      Fputs(buf, stdout);
    }
    else
    {
      printf("=========== server received: 0!! 结束. ===========\n");
      break;
    }
  }
}
/* $end echo */

/** Learned */
// 1. 自定义的Resp必须有换行符'\n'
// 2. 服务端接收到一个请求后，必须反写客户端，客户端才能再写。

// @todo
// 1. 可以让服务端先写嘛？

