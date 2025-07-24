// #include "csapp.h"
#include "../code/csapp.h"

void echo(int connfd)
{
  size_t n;
  char buf[MAXLINE];
  rio_t rio;

  Rio_readinitb(&rio, connfd);

  char *resp = "Received.\n";
  while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
  { // line:netp:echo:eof
    printf("server received(from %d) [%d-bytes]->%s", connfd, (int)n, buf);
    Rio_writen(connfd, resp, strlen(resp));
  }
}