
#include "csapp.h"
#include <netdb.h>
#include <stdio.h>

int main(int argc, char **argv) {
    printf("================ start ================\n");
    struct addrinfo *p, *listp, hints;
    char buf[MAXLINE];
    // int rc, flags;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(0);
    }

    /* Get a list of addrinfo records */
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;         /* IPv4 only */
    hints.ai_socktype = SOCK_STREAM;   /* Connections only */
    int rc = getaddrinfo(argv[1], NULL, &hints, &listp);
    if (rc != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(1);
    }

    /* Walk the list and display each IP address */
    int flags = NI_NUMERICHOST;  /* Display address string instead of domain name */
    for (p = listp; p; p = p->ai_next) {
        getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
        printf("%s\n", buf);
    }

    /* Clean up */
    freeaddrinfo(listp);
    

    struct addrinfo *listp_f;
    rc = getaddrinfo(argv[1], NULL, &hints, &listp_f);

    exit(0);
}