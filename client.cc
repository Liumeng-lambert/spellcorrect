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
	scanf("%s", buf);
	int ret = _socket_io.writen(buf, sizeof(buf));
	if(-1 == ret){
        std::cout << "write error" << std::endl; 
	}
	char tmp[512];
	::memset(tmp, 0, sizeof(tmp));
	//while(_socket_io.readn(tmp, 512)) {
	while(strlen(tmp) == 0){
		_socket_io.readn(tmp, sizeof(tmp));
	}
	//}
	std::cout << tmp << std::endl;
}
