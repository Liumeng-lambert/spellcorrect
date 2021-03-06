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
	std::cout << ip.c_str() << std::endl;
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

SocketServer::SocketServer()
:_sockfd(create_socket_fd())
{
}

SocketServer::SocketServer(int fd)
: _sockfd(fd)
{
}

int SocketServer::create_socket_fd() {
	int fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if(fd == -1) {
		LogPrinter::export_log(
				"fail to create socket fd", "log/socketLog.txt");
	}
	return fd;
}

void SocketServer::ready(const InetAddress &addr) {
	LogPrinter::export_log("socket ready",
			  "log/socketLog.txt");
	
	set_reuse_addr(true);
	set_reuse_port(true);
	bind_address(addr);
	listen();
}

int SocketServer::accept() {
	/*can get remote machine info*/
	std::cout << "accept" << std::endl;
	int connection_fd = ::accept(_sockfd, NULL, NULL);
	if (connection_fd == -1) {
		LogPrinter::export_log("error to accept", "log/socketLog.txt");
		close(_sockfd);
		exit(EXIT_FAILURE);
	}
	return connection_fd;
}

int SocketServer::fd() {
	return _sockfd;
}
/*TODO:*/
InetAddress SocketServer::get_local_addr(int sockfd) {

}
/*TODO:*/
InetAddress SocketServer::get_peer_addr(int sockfd) {

}

void SocketServer::shutdown_write() {
	shutdown(_sockfd, SHUT_WR);
}

void SocketServer::bind_address(const InetAddress & addr) {
	int ret = ::bind(_sockfd, (sockaddr*)addr.get_addr_ptr(), 
				   sizeof(sockaddr));
	if(ret == -1){
		LogPrinter::export_log("error to bind", "log/socketLog.txt");
		close(_sockfd);
		exit(EXIT_FAILURE);
	}
}

void SocketServer::listen() {
	/*max connection can handle*/
	int max_connection = 10;	
	if(::listen(_sockfd, max_connection) == -1) {
		LogPrinter::export_log("error to listen", "log/socketLog.txt");
		close(_sockfd);
		exit(EXIT_FAILURE);
	}
}

/*the function should call before bind_address()*/
void SocketServer::set_reuse_addr(bool flag) {
	int reuse = flag? 1: 0;
	int ret = ::setsockopt(_sockfd,SOL_SOCKET ,SO_REUSEADDR,(const char*)&reuse,sizeof(int));
	if (ret == -1) {
		LogPrinter::export_log("error to set addr resuse",
								"log/socketLog.txt");
	}
}

/*the function should call before bind_address()*/
void SocketServer::set_reuse_port(bool flag) {
	int reuse = flag? 1: 0;
	int ret = ::setsockopt(_sockfd,SOL_SOCKET ,SO_REUSEPORT,(const char*)&reuse,sizeof(int));
	if (ret == -1) {
		LogPrinter::export_log("error to set port resuse",
								"log/socketLog.txt");
	}
	
}

SocketClient::SocketClient()
:_sockfd(create_socket_fd())
{

}

SocketClient::SocketClient(int fd)
:_sockfd(fd)
{

}

SocketClient::~SocketClient() {

}

void SocketClient::connect_socket(const InetAddress & addr) {
	int ret = connect(_sockfd, (sockaddr*)addr.get_addr_ptr(), sizeof(struct sockaddr));
	std::cout << "connect : " << ret << std::endl;
	if(ret == -1) {
		LogPrinter::export_log(
				"fail to connect", "log/socketLog.txt");	
	}else {
		LogPrinter::export_log(
				"success to connect", "log/socketLog.txt");	
	}
}

int SocketClient::fd() {
	return _sockfd;
}

int SocketClient::create_socket_fd() {
	int fd = ::socket(AF_INET, SOCK_STREAM, 0);
	if(fd == -1) {
		LogPrinter::export_log(
				"fail to create socket fd", "log/socketLog.txt");
	}
	return fd;
}

SocketIO::SocketIO(int connection_fd) 
:_connection_fd(connection_fd)
{
}

size_t SocketIO::readline(char * buf, size_t max) {
	size_t left = max - 1;
	size_t total = 0;
	char *p_tmp = buf;
	int nread;
	while(left > 0) {
		nread = recvPeek(p_tmp, left);
		if(nread <= 0) {
			return nread;
		}
		for(int i = 0; i < nread; ++i) {
			/*find /n*/
			if(p_tmp[i] == '\n') {
				size_t nsize = i + 1;
				if(readn(p_tmp, nsize) != nsize) {
					return -1;
				}
				p_tmp += nsize;
				total += nsize;
				*p_tmp = '\0';
				return total;		
			}
		}
		if(readn(p_tmp, nread) != nread) {
			return -1;
		}
		p_tmp += nread;
		total += nread;
		left -= nread;
	}	
	*p_tmp = '\0';
	return max - 1;
}

size_t SocketIO::readn(char * buf, size_t count) {
	size_t left = count;
	char * p_tmp = buf;
	while(left > 0) {
		int ret = recv(_connection_fd, p_tmp, left, 0);
		/*signal interrupt and no data read*/
		if(-1 == ret) {
			if(errno == EINTR) {
				continue;
			}
			exit(EXIT_FAILURE);
		}else if(0 == ret){	
			break;	
		}
		p_tmp += ret;
		left -= ret;
	}
	return count - left;
}

size_t SocketIO::writen(const char * buf, size_t count) {
	size_t left = count;
	const char * p_tmp = buf;
	while(left > 0) {
		int ret = send(_connection_fd, p_tmp, left, 0);
		if(ret == -1) {
			if(errno == EINTR) {
				continue;
			}
			exit(EXIT_FAILURE);
		}else if(ret == 0) {
			break;
		}
		left -= ret;
		p_tmp += ret;
	}
	return count - left;
}
/*recv: copy from buffer ,not cut, not delete from buffer*/
size_t SocketIO::recvPeek(char * buf, size_t len) {
	size_t read_msg;
	do
	{
		read_msg = recv(_connection_fd, buf, len, MSG_PEEK);
	}while(-1 == read_msg && errno == EINTR);
	return read_msg;
}


