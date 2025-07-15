
#include <arpa/inet.h>
#include <stdio.h>

/******** Practice Problem 11.1 ********/ 

/** 
 *注意需要使用`ntohl`和`htonl`
 */
void pp_11_1(){
    /**
    1. Dotted-decimal address -> Hex address
        107.212.122.205  原:0xcd7ad46b  转:0x6bd47acd
        64.12.149.13     原:0x0d950c40  转:0x400c950d
        107.212.96.29
     */
    const char *ip_str = "64.12.149.13";
    struct in_addr addr;
    
    // 1 成功，0 invalid decimal, -1 error
    // if (inet_pton(AF_INET, ip_str, &addr) == 1) {
    //     printf("十六进制: 0x%08x\n", addr.s_addr);
    //     printf("十六进制(ntohl): 0x%08x\n", ntohl(addr.s_addr));
    // }
    // printf("字符串地址: %p\n", ip_str);
    // printf("字符串: %s\n", ip_str);
 
    


    // 2. Hex address -> Dotted-decimal address
    /**
    2. Hex address -> Dotted-decimal address
        0x00000080  转: 0.0.0.128
        0xFFFFFF00
        0x0A010140 
    */
    char ip_dst[INET_ADDRSTRLEN];
    u_int32_t s_addr = htonl(0x00000080);
    if(inet_ntop(AF_INET, &s_addr, ip_dst, INET_ADDRSTRLEN) != NULL) {
        printf("ip: %s\n", ip_dst);
    }


}

#define MAXBUF   8192
/**
 * Practice Problem 11.2
 * Write a program hex2dd.c that converts its 16-bit hex argument to a 16-bit network byte order and prints the result. 
 * For example
 * > ./hex2dd 0x400
 * > 1024
 */
void hex2dd(u_int16_t hex16){
    uint16_t result = htons(hex16);
    // printf("result: %x\n", result);

    // network byte order
    struct in_addr inaddr;
    char buf[INET_ADDRSTRLEN];

    if (inet_ntop(AF_INET, &hex16, buf, MAXBUF)) {
        printf("result: %s \n", buf);
    }
}

int main(int argc, char **argv){
    // pp_11_1();

    // u_int16_t addr;
    // sscanf(argv[1], "%x", &addr);
    hex2dd(0x400);
    return 0;
}