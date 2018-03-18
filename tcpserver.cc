 ///
 /// @file    tcpserver.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-11 16:55:56
 ///
 
#include <iostream>
#include "tcpserver.hpp"
TcpServer::TcpServer(unsigned short port)
:_inet_addr(port), _sockfd(), 
_epoller(_sockfd.fd())
{

}

TcpServer::TcpServer(const char * ip,unsigned short port)
:_inet_addr(ip, port), _sockfd(), 
_epoller(_sockfd.fd())
{

}

TcpServer::~TcpServer() {

}

void TcpServer::start() {
	_sockfd.ready(_inet_addr);
	_epoller.set_connection_callback(_on_connection_cb);
	_epoller.set_message_callback(_on_message_cb);
	_epoller.set_close_callback(_on_close_cb);
	_epoller.loop();
}

void TcpServer::stop() {
	_epoller.unloop();
}

void TcpServer::set_connection_callback(TcpServerCallback cb) {
	_on_connection_cb = cb;
}

void TcpServer::set_message_callback(TcpServerCallback cb) {
	_on_message_cb = cb;
}

void TcpServer::set_close_callback(TcpServerCallback cb) {
	_on_close_cb = cb;
}

