/*
 * server.c - Server只发送内容的例子
 */
#include "csapp.h"
#include <unistd.h>

int main(int argc, char **argv) {
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]);
    printf("Server listening on port %s\n", argv[1]);

    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
        printf("Connected to client (%s, %s)\n", client_hostname, client_port);

        // Server只发送内容，不接收
        char *messages[] = {
            "Hello from server!\n",
            "This is message 2\n", 
            "This is message 3\n",
            "Server is sending data...\n",
            "Final message from server\n"
        };

        for (int i = 0; i < 5; i++) {
            Rio_writen(connfd, messages[i], strlen(messages[i]));
            printf("Sent: %s", messages[i]);
            sleep(1); // 间隔1秒发送
        }

        printf("Finished sending to client\n");
        Close(connfd);
        break;
    }
    printf("Exit!\n");
    exit(0);
}