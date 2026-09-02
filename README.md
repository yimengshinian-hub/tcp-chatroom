# TCP Chatroom Server

基于 Qt 的 TCP 聊天室服务端，支持多客户端同时在线和消息广播。

## 技术栈

- Qt 5.13
- C++
- TCP/IP
- QTcpServer
- 多线程 QThread

## 功能

- 监听指定端口，等待客户端连接
- 每个客户端连接由独立线程处理
- 接收客户端消息
- 客户端异常断开时自动清理资源

## 使用说明

1. 运行服务端程序
2. 服务端默认监听 2025 端口
3. 启动多个客户端连接
4. 任意客户端发送消息，服务端都能收到

## 配合客户端

本服务端需要配合客户端使用，客户端仓库地址：

https://github.com/yimengshinian-hub/tcp-chatroom-client

## 编译运行

使用 Qt Creator 打开 tcpserver.pro，编译运行即可。
