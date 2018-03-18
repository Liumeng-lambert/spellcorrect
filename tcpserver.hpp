 ///
 /// @file    tcpserver.hpp
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-11 16:51:17
 ///

#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_
#include <iostream>
#include <vector>
#include <map>
#include "tcp.hpp"
#include "epoll.hpp"
class TcpServer {
public:	
	TcpServer(unsigned short port);
	TcpServer(const char * ip,unsigned short port);
	~TcpServer();
	void start();
	void stop();
	typedef TcpConnection::TcpConnectionCallback TcpServerCallback;
	void set_connection_callback(TcpServerCallback cb);
	void set_message_callback(TcpServerCallback cb);
	void set_close_callback(TcpServerCallback cb);
private:
	InetAddress _inet_addr;
	Socket _sockfd;
	EpollPoller _epoller;
	TcpServerCallback _on_connection_cb;
	TcpServerCallback _on_message_cb;
	TcpServerCallback _on_close_cb;
};
#endif
