 ///
 /// @file    tcp.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-07 15:19:42
 ///
 
#include <iostream>
#include "tcp.hpp"
TcpConnection::TcpConnection()
:_socket(), _sockIO(_socket.fd()),
 _localAddr(Socket::get_local_addr(_socket.fd())),
 _peerAddr(Socket::get_local_addr(_socket.fd()))
{
	/*
	Socket _socket();
	SocketIO _sockIO(_socket.fd()); 
	*/
}

TcpConnection::~TcpConnection() {

}

std::string TcpConnection::receive() {

}

void TcpConnection::send(const std::string & msg) {

}

void TcpConnection::shutdown() {

}

void TcpConnection::set_connection_callback(TcpConnectionCallback cb) {

}

void TcpConnection::set_message_callback(TcpConnectionCallback cb) {

}

void TcpConnection::set_close_callback(TcpConnectionCallback cb) {

}

void TcpConnection::handle_connection_callback() {

}

void TcpConnection::handle_message_callback() {

}

void TcpConnection::handle_close_callback() {

}

std::string TcpConnection::to_string() {

}

