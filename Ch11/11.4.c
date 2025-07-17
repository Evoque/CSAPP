
#include "csapp.h"
#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
    printf("================ start ================\n");
    if (argc != 2) {
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(0);
    }

    struct addrinfo *p, *listp, hints;

    /* Get a list of addrinfo records */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;         /* IPv4 only */
    hints.ai_socktype = SOCK_STREAM;   /* Connections only */
    char *service1 = "808";
    int rc = getaddrinfo(argv[1], service1, &hints, &listp);
    if (rc != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(1);
    }
    // /* Walk the list and display each IP address */
    int flags = NI_NUMERICHOST;  /* Display address string instead of domain name */
    // int flags = NI_NUMERICSERV;
    char hosts[MAXLINE];
    char service[MAXLINE];
    for (p = listp; p; p = p->ai_next) {
        getnameinfo(p->ai_addr, p->ai_addrlen, hosts, MAXLINE, service, MAXLINE, flags);
        printf("host=%s, port=%s \n", hosts, service);
    } 
    /* Clean up */
    freeaddrinfo(listp);
     
    exit(0);
}

/**
 * QA: 为什么会有`getaddrinfo` & `getnameinfo`两个function
 * 目的： 有域名 -> 获得IP
 * 1. 域名获得addrinfo ( 地址的二进制形式 )
 * 2. addrinfo -> hostname (ip)
 */