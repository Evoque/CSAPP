
- Until 1988, the mapping(domain names -> IPs) was maintained manually in a single text file call `HOSTS.TXT`.
- After, maintained by DNS(Domain Name System) - distributed world wide database.
- broadcasthost(255.255.255.255): 当你向255.255..发送数据包时，同一局域网内的所有设备都能收到这个包(如果网络设备允许广播)

### Internet Connections 
- Internet clients and servers communicate by sending and receiving streams of bytes over connections.
- A connection is `point-to-point` in the sense that it connects a pair of processes.

由于历史包袱，IP地址的结构在C语言中如下,且是*big-endian*, 注意这里是地址（如IP）并不包含端口号。
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


