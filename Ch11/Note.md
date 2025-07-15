
由于历史包袱，IP地址的结构在C语言中如下,且是*big-endian*
```c
struct in_addr {
    uint32_t s_addr;
}
```

在Linux中快速查询本机IP地址:(在Mac和Windows中并不好使)
```shell
hostname -i
```

```c

#include <arpa/inet.h>
// Returns: value in network byte order
uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);

// Returns: value in host byte order
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(unit16_t netshort);

```


```c

#include <arpa/inet.h>
// Returns: 1 if OK, 0 if src is invalid dotted decimal, −1 on error
int inet_pton(AF_INET, const char *src, void *dst);

// Returns: pointer to a dotted-decimal string if OK, NULL on error
const char *inet_ntop(AF_INET, const void *src, char *dst,socklen_t size);

```


