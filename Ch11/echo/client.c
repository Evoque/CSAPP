/*
 * echoclient.c - An echo client
 */
/* $begin echoclientmain */
#include "csapp.h"

int main(int argc, char **argv)
{
  int clientfd;
  char *host, *port, buf[MAXLINE];
  rio_t rio;

  if (argc != 3)
  {
    fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
    exit(0);
  }
  host = argv[1];
  port = argv[2];

  clientfd = Open_clientfd(host, port);
  Rio_readinitb(&rio, clientfd);

  while (1)
  {
    char *tmp = Fgets(buf, MAXLINE, stdin);
    if (tmp == NULL)
    {
      printf("Input ended, closing connection\n");
      break;
    }

    int wn = Rio_writen(clientfd, buf, strlen(buf));
    if (wn < 0)
    {
      printf("Write error - server may have closed\n");
      break;
    }
    else
    {
      printf("Write succeed - %d bytes\n", wn);
    }

    /* @NOTE: 多个Client时，会阻塞到这里，Server能接收到请求，且接收到Writen，但是不会response，
     * 所以卡在了客户端的Read（显示为客户端无响应）
     */
    size_t n = Rio_readlineb(&rio, buf, MAXLINE);
    if (n != 0)
    {
      printf("Server Response: %s", buf);
    }
    else
    {
      printf("Server closed connection, readn - %d bytes\n", (int)n);
      break;
    }
  }
  Close(clientfd); // line:netp:echoclient:close
  exit(0);
}
/* $end echoclientmain */
