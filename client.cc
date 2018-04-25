 ///
 /// @file    client.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-04-20 16:36:20
 ///
 
#include <iostream>
#include <string.h>
#include <stdio.h>
#include  <unistd.h>
#include "client.hpp"
Client::Client(const char * ip,unsigned short port)
:_inet_addr(ip, port),
 _sockfd(),
 _socket_io(_sockfd.fd())
{
}

Client::~Client() {
	
}

void Client::start() {
	std::cout << "client start" << std::endl;
	_sockfd.connect_socket(_inet_addr);
	
	while(1){
		run_service();
	}
}

void Client::run_service() {
	char buf[512];
	int ret = read(0, buf, 512);
	if(-1 == ret){
        std::cout << "read error" << std::endl; 
	}
	ret = _socket_io.writen(buf, 512);
	if(-1 == ret){
        std::cout << "write error" << std::endl; 
	}
	//while(1){
		char tmp[512];
		_socket_io.readline(tmp, 512);
		std::cout << tmp << std::endl;
	//}
}

