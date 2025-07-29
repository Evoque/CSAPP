CC = gcc
CFLAGS = -g -O1 -Wall
LDLIBS = -lpthread

# 目标文件
TARGETS = client server server_cp server_ciom server_ct pt badcnt sharing

# 默认目标
all: $(TARGETS)

# 编译client
client: client.c csapp.c
	gcc client.c csapp.c -g -o client

# 编译server (如果存在)
server: server.c echo.c csapp.c csapp.h csapp.h
	$(CC) $(CFLAGS) -o server server.c echo.c csapp.c $(LDLIBS)

# 清理生成的文件
clean:
	rm -rf $(TARGETS) *.dSYM *.o *~

# 运行client (需要先启动server)
run-client: client
	./client 127.0.0.1 9999

# 伪目标
.PHONY: all clean run-client

