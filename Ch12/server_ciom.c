/**
 * Concurrent Programming with I/O Multiplexing
 */

/**
 * #include <sys/select.h>
 *
 * // Returns: nonzero count of ready descriptors, −1 on error
 * int select(int n, fd_set *fdset, NULL, NULL, NULL);
 *
 * FD_ZERO(fd_set *fdset);           // Clear all bits in fdset
 * FD_CLR(int fd, fd_set *fdset);    // Clear bit fd in fdset
 * FD_SET(int fd, fd_set *fdset);    // Turn on bit fd in fdset
 * FD_ISSET(int fd, fd_set *fdset);  // Is bit fd in fdset on?
 */

#include "../code/csapp.h"
#include "echo.c"

// handle keyboard
// void command(void)
// {
//   char buf[MAXLINE];
//   if (!Fgets(buf, MAXLINE, stdin))
//     exit(0);         /* EOF */
//   printf("我输入了: %s\n", buf); /* Process the input command */
// }

// int main(int argc, char **argv)
// {
//   if (argc != 2)
//   {
//     fprintf(stderr, "please usage: %s <port>\n", argv[0]);
//     exit(0);
//   }

//   // socket zone
//   int listenfd, connfd;
//   socklen_t clientlen;
//   struct sockaddr_storage clientaddr;
//   listenfd = Open_listenfd(argv[1]);

//   // fd zone
//   fd_set read_set, ready_set;
//   FD_ZERO(&read_set);              /* Clear read set */
//   FD_SET(STDIN_FILENO, &read_set); /* Add stdin to read set */
//   FD_SET(listenfd, &read_set);     /* Add listenfd to read set */

//   while (1)
//   {
//     ready_set = read_set;
//     Select(listenfd + 1, &ready_set, NULL, NULL, NULL);

//     if (FD_ISSET(STDIN_FILENO, &ready_set))
//     {
//       printf("===================> STDIN \n");
//       command(); /* Read command line from stdin */
//     }
//     if (FD_ISSET(listenfd, &ready_set))
//     {
//       clientlen = sizeof(struct sockaddr_storage);
//       connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
//       echo(connfd); /* Echo client input until EOF */
//       Close(connfd);
//     }
//   }
// }
/* ==> 以上代码仍然会阻塞，如果有client socket没有被断开，就无法响应STDIN */

typedef struct
{
  /* Represents a pool of connected descriptors */
  int maxfd;        /* Largest descriptor in read_set */
  fd_set read_set;  /* Set of all active descriptors */
  fd_set ready_set; /* Subset of descriptors ready for reading */

  int nready; /* Number of ready descriptors from select */

  int maxi;                    /* High water index into client array */
  int clientfd[FD_SETSIZE];    /* Set of active descriptors */
  rio_t clientrio[FD_SETSIZE]; /* Set of active read buffers */
} pool;

int byte_cnt = 0; /* Counts total bytes received by server */

void init_pool(int listenfd, pool *p)
{
  /* Initially, there are no connected descriptors */
  p->maxi = -1;
  for (int i = 0; i < FD_SETSIZE; i++)
    p->clientfd[i] = -1;

  /* Initially, listenfd is only member of select read set */
  p->maxfd = listenfd;
  FD_ZERO(&p->read_set);
  FD_SET(listenfd, &p->read_set);
}

void add_client(int connfd, pool *p)
{
  int i;
  p->nready--;
  /* Find an available slot */
  for (i = 0; i < FD_SETSIZE; i++)
  {
    if (p->clientfd[i] < 0)
    {
      /* Add connected descriptor to the pool */
      p->clientfd[i] = connfd;
      Rio_readinitb(&p->clientrio[i], connfd);

      /* Add the descriptor to descriptor set */
      FD_SET(connfd, &p->read_set);

      /* Update max descriptor and pool high water mark */
      if (connfd > p->maxfd)
        p->maxfd = connfd;
      if (i > p->maxi)
        p->maxi = i;
      break;
    }
  }

  /* Couldn’t find an empty slot */
  if (i == FD_SETSIZE)
    app_error("add_client error: Too many clients");
}

void check_clients(pool *p)
{
  int i, connfd, n;
  char buf[MAXLINE];
  rio_t rio;

  for (i = 0; (i <= p->maxi) && (p->nready > 0); i++)
  {
    connfd = p->clientfd[i];
    rio = p->clientrio[i];

    /* If the descriptor is ready, echo a text line from it */
    if ((connfd > 0) && (FD_ISSET(connfd, &p->ready_set)))
    {
      p->nready--;
      /**
       * @todo:
       * vulnerable to a malicious client that sends only a partial text line(no \n or EOF) and then halts.
       * modifying it is a nontrivial task.
       */
      if ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
      {
        byte_cnt += n;
        printf("[fd-%d]Server received: %s\n", connfd, buf);
        Rio_writen(connfd, buf, n);
      }
      else /* EOF detected, remove descriptor from pool */
      {
        Close(connfd);
        FD_CLR(connfd, &p->read_set);
        p->clientfd[i] = -1;
      }
    }
  }
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }

  int listenfd, connfd;
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;
  listenfd = Open_listenfd(argv[1]);

  static pool pool;
  init_pool(listenfd, &pool);

  char client_hostname[MAXLINE], client_port[MAXLINE];

  while (1)
  {
    /* Wait for listening/connected descriptor(s) to become ready */
    pool.ready_set = pool.read_set;
    pool.nready = Select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);

    /* If listening descriptor ready, add new client to pool */
    if (FD_ISSET(listenfd, &pool.ready_set))
    {
      clientlen = sizeof(struct sockaddr_storage);
      connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
      Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
      printf("Server Accepted: (%s, %s)-fd[%d]\n", client_hostname, client_port, connfd);
      add_client(connfd, &pool);
    }

    /* Echo a text line from each ready connected descriptor */
    check_clients(&pool);
  }
}

/**
 * Aside: Event-driven Web servers
 * Despite the disadvantages outlined in Section 12.2.2, modern high-performance servers such as Node.js,
 * nginx, and Tornado use event-driven programming based on I/O multiplexing, mainly because of the
 * significant performance advantage compared to processes and threads.
 */