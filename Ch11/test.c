

#include "csapp.h"
#include <stdint.h>
#include <stdio.h>

int main(){

    char * ip_str = "128.2.194.242";
    uint32_t ip_str_int;

    int ip_str_to_int = inet_pton(AF_INET, ip_str, &ip_str_int);
    // 此处证明， 按照ip_str进行转换，得到的int是与ip_int相反的
    printf("ip string to number: ip-%s ; num-0x%08x . result-%d \n", ip_str, ip_str_int, ip_str_to_int);


    uint32_t ip_int = htonl(0x8002c2f2);
    char ip_int_result[INET_ADDRSTRLEN];
    const char *ip_int_to_str = inet_ntop(AF_INET, &ip_int, ip_int_result, INET_ADDRSTRLEN);
    printf("ip number to number: num=0x%08x; ip=%s. result-%s \n", ip_int, ip_int_result, ip_int_to_str);

    return 0;
}