/*
 * client.c - Client只接收内容的例子
 */
#include "csapp.h"

int main(int argc, char **argv) {
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
    host = argv[1];
    port = argv[2];

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);
    printf("Connected to server %s:%s\n", host, port);

    // Client只接收内容，不发送
    while (1) {
        size_t n = Rio_readlineb(&rio, buf, MAXLINE);
        if (n > 0) {
            printf("Received: %s", buf);
        } else {
            printf("Server closed connection\n");
            break;
        }
    }

    Close(clientfd);
    exit(0);
}