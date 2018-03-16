 ///
 /// @file    tcpserver.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-11 16:55:56
 ///
 
#include <iostream>
#include "tcpserver.hpp"
TcpServer::TcpServer(unsigned short port)
:_inet_addr(port), _sockfd(), 
_epollfd(_sockfd.fd())
{

}

TcpServer::TcpServer(const char * ip,unsigned short port)
:_inet_addr(ip, port), _sockfd(), 
_epollfd(_sockfd.fd())
{

}

TcpServer::~TcpServer() {

}

void TcpServer::start() {

}

void TcpServer::stop() {

}

void TcpServer::setConnectionCallback(TcpServerCallback cb) {

}

void TcpServer::setMessageCallback(TcpServerCallback cb) {

}

void TcpServer::setCloseCallback(TcpServerCallback cb) {

}

