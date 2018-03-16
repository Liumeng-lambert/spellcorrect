 ///
 /// @file    tcp.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-07 15:19:42
 ///
 
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include "tcp.hpp"

TcpConnection::TcpConnection()
:_socket(), _sockIO(_socket.fd()),
 _local_addr(Socket::get_local_addr(_socket.fd())),
 _peer_addr(Socket::get_local_addr(_socket.fd())),
 _is_shutdown_write(false)
{
	/*
	Socket _socket();
	SocketIO _sockIO(_socket.fd()); 
	*/
}

TcpConnection::TcpConnection(int sockfd)
:_socket(sockfd), _sockIO(sockfd),
_local_addr(Socket::get_local_addr(sockfd)),
_peer_addr(Socket::get_local_addr(sockfd)),
_is_shutdown_write(false)
{
	/*set callback function*/
	/*should bind to object*/
	set_connection_callback(std::bind(&TcpConnection::handle_connection_callback,
							shared_from_this()));
	set_message_callback(std::bind(&TcpConnection::handle_message_callback,
						 shared_from_this()));
	set_close_callback(std::bind(&TcpConnection::handle_close_callback,
					   shared_from_this()));
}

TcpConnection::~TcpConnection() {
	if(!_is_shutdown_write) {
		shutdown();
	}
}

std::string TcpConnection::receive() {
	char buf[65536];
	::memset(buf, 0, sizeof(buf));
	_sockIO.readline(buf, sizeof(buf));
	return std::string(buf);
}

void TcpConnection::send(const std::string & msg) {
	_sockIO.writen(msg.c_str(), msg.size());
}

void TcpConnection::shutdown() {
	if(!_is_shutdown_write) {
		_is_shutdown_write = true;
		_socket.shutdown_write();
	}
}

void TcpConnection::set_connection_callback(TcpConnectionCallback cb) {
	_on_connection_cb = cb;
}

void TcpConnection::set_message_callback(TcpConnectionCallback cb) {
	_on_message_cb = cb;
}

void TcpConnection::set_close_callback(TcpConnectionCallback cb) {
	_on_close_cb = cb;
}

void TcpConnection::handle_connection_callback() {
	if(_on_connection_cb) {
		_on_connection_cb(shared_from_this());
	}
}

void TcpConnection::handle_message_callback() {
	if(_on_message_cb) {
		_on_message_cb(shared_from_this());
	}

}

void TcpConnection::handle_close_callback() {
	if(_on_close_cb) {
		_on_close_cb(shared_from_this());
	}
}

std::string TcpConnection::to_string() {
	std::ostringstream osstrm;
	osstrm << _local_addr.get_ip() << ":" << _local_addr.get_port()
		   << " ----> " << _peer_addr.get_ip() 
		   << ":"<< _peer_addr.get_port();
	return osstrm.str();
}


