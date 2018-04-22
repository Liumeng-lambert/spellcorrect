 ///
 /// @file    client.hpp
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-04-20 16:26:26
 ///
 
#include <iostream>
#include "socket.hpp"
class Client{
public:
	Client(const char * ip,unsigned short port);
	~Client();
	void start();
	void run_service();
private:
	InetAddress _inet_addr;
	SocketClient _sockfd;
	SocketIO _socket_io;
};

