 ///
 /// @file    socket.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-02 10:36:16
 ///
 
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "socket.hpp"
#include "log.hpp"

InetAddress::InetAddress(unsigned short port) {
	memset(&_addr, 0, sizeof(struct sockaddr_in));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = INADDR_ANY;
}

InetAddress::InetAddress(const std::string ip, unsigned short port) {
	memset(&_addr, 0, sizeof(struct sockaddr_in));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = inet_addr(ip.c_str());

}

InetAddress::InetAddress(const struct sockaddr_in & addr)
:_addr(addr)
{
}

std::string InetAddress::get_ip() const {
	/*inet_ntoa : return pointer */
	return	std::string(inet_ntoa(_addr.sin_addr));
}

unsigned short InetAddress::get_port() const {
	return ntohs(_addr.sin_port);
}

const struct sockaddr_in* InetAddress::get_addr_ptr()const {
	return &_addr;
}

Socket::Socket()
:_sockfd(create_socket_fd())
{
}

int Socket::create_socket_fd() {
	int fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if(fd == -1) {
		LogPrinter::export_log(
							"fail to create socket fd", "log/socketLog.txt");
	}
	return fd;
}

void Socket::ready(const InetAddress &addr) {
	set_reuse_addr(true);
	set_reuse_port(true);
	bind_address(addr);
	listen();
}

int Socket::accept() {
	
}

int Socket::fd() {
	return _sockfd;
}

InetAddress Socket::get_local_addr(int sockfd) {

}

InetAddress Socket::get_peer_addr(int sockfd) {

}

void Socket::shutdown_write() {

}

void Socket::bind_address(const InetAddress & addr) {
	int ret = bind(_sockfd, (sockaddr*)addr.get_addr_ptr(), 
				   sizeof(sockaddr));
	if(ret == -1){
		LogPrinter::export_log("error to bind", "log/socketLog.txt");
		close(_sockfd);
		exit(EXIT_FAILURE);
	}
}

void Socket::listen() {
	
}

void Socket::set_reuse_addr(bool flag) {

}

void Socket::set_reuse_port(bool flag) {

}


