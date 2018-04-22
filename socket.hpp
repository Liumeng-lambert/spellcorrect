 ///
 /// @file    socket.hpp
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-02 10:21:45
 ///
 
#ifndef _SOCKET_H_
#define _SOCKET_H_
#include <iostream>
#include <netinet/in.h>
class InetAddress{
public:
	InetAddress(unsigned short);
	InetAddress(const std::string ip, unsigned short);
	InetAddress(const struct sockaddr_in & addr);
	std::string get_ip() const;
	unsigned short get_port() const;
	const struct sockaddr_in* get_addr_ptr()const;
private:
	sockaddr_in  _addr;
};

class SocketServer{
public:
	SocketServer();
	SocketServer(int fd);
	/*get ready to listen*/
	void ready(const InetAddress &addr);
	int accept();
	int fd();
	static InetAddress get_local_addr(int sockfd);
	static InetAddress get_peer_addr(int sockfd);
	void shutdown_write();
private:
	int create_socket_fd();
	void bind_address(const InetAddress & addr);
	void listen();
	void set_reuse_addr(bool flag);
	void set_reuse_port(bool flag);
	int _sockfd;
};

class SocketClient{
public:
	SocketClient();
	SocketClient(int fd);
	~SocketClient();
	void connect(const InetAddress & addr);
	int fd();
private:
	int create_socket_fd();
	int _sockfd;
};

class SocketIO{
public:
	SocketIO(int sockfd);
	size_t readline(char * buf, size_t max);
	size_t readn(char * buf, size_t count);
	size_t writen(const char * buf, size_t count);
private:
	size_t recvPeek(char * buf, size_t count);
	int  _connection_fd;
};

#endif
