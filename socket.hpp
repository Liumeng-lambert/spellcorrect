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
	InetAddress(const char * ip, unsigned short);
	InetAddress(const struct sockaddr_in & addr);
	string get_ip() const;
	unsigned short get_port() const;
private:
	sockaddr_in  _addr;
};

class Socket{
public:
	Socket();
	Socket(int sockfd);
	void ready(const InetAddress &addr);
	int accept();
	int fd();
	static InetAddress get_local_addr(int sockfd);
	static InetAddress get_peer_addr(int sockfd);
private:
	void shutdown_write();
	void bind_address(const InetAddress & addr);
	void listen();
	void set_reuse_addr(bool flag);
	int _sockfd;
};

class SocketIO{
public:

private:

};

#endif
