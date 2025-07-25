/**
 * Concurrent Programming with Processes
 */
#include "../code/csapp.h"
#include "echo.c"

void sigchld_handler(int sig)
{
  while (waitpid(-1, 0, WNOHANG) > 0)
    ;
  return;
}

int main(int argc, char **argv)
{
  int listenfd, connfd;
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;

  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }

  char client_hostname[MAXLINE], client_port[MAXLINE];

  Signal(SIGCHLD, sigchld_handler);
  listenfd = Open_listenfd(argv[1]);
  while (1)
  {
    clientlen = sizeof(struct sockaddr_storage);
    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE,
                client_port, MAXLINE, 0);
    printf("Server Accepted: (%s, %s)-fd[%d]\n", client_hostname, client_port, connfd);
    if (Fork() == 0)
    {
      Close(listenfd); /* Child closes its listening socket */
      echo(connfd);    /* Child services client */
      Close(connfd);   /* Child closes connection with client */
      exit(0);         /* Child exits */
    }
    Close(connfd); /* Parent closes connected socket (important) */
  }
}