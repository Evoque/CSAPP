
### Server
gcc server.c echo.c csapp.c -o server
./server 9991

### Client
gcc client.c csapp.c -o client
./client 127.0.0.1 9991