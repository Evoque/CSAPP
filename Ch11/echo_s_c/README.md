# Server只发送，Client只接收的例子

## 编译
```bash
gcc server.c csapp.c -o server
gcc client.c csapp.c -o client
```

## 运行
### 启动Server
```bash
./server 9999
```

### 启动Client
```bash
./client 127.0.0.1 9999
```

## 功能
- Server连接建立后主动发送5条消息给Client
- Client连接后只接收Server发送的消息
- Server发送完毕后关闭连接