 ///
 /// @file    socket.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-02 10:36:16
 ///
 
#include <iostream>
#include "socket.hpp"

InetAddress::InetAddress(unsigned short port) {
	memset(&_addr, 0, sizeof(struct sockaddr_in));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = INADDR_ANY;
}

InetAddress::InetAddress(const char * ip, unsigned short port) {
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
	return	string(inet_ntoa(_addr.sin_addr));
}

unsigned short InetAddress::get_port() const {
	return ntohs(_addr.sin_port);
}

Socket::Socket() {

}

Socket::Socket(int sockfd) {

}

void Socket::ready(const InetAddress &addr) {

}

int Socket::accept() {

}

int Socket::fd() {

}

InetAddress Socket::get_local_addr(int sockfd) {

}

InetAddress Socket::get_peer_addr(int sockfd) {

}

void Socket::shutdown_write() {

}

void Socket::bind_address(const InetAddress & addr) {

}

void Socket::listen() {

}

void Socket::set_reuse_addr(bool flag) {

}

void Socket::set_reuse_port(bool flag) {

}


