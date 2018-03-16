 ///
 /// @file    epoll.hpp
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-07 15:31:05
 ///
 
#ifndef _EPOLL_H_
#define _EPOLL_H_
#include <iostream>
#include <vector>
#include <map>
#include <sys/epoll.h> 
#include "tcp.hpp"

class EpollPoller{
public:
	typedef TcpConnection::TcpConnectionCallback EpollCallback;
	//typedef std::function<void()> Functor;
	EpollPoller(int listenfd);
	void loop();
	void unloop();
	bool in_connection(int connfd);
	//void run_in_loop(const Functor & cb);
	void set_connection_callback(EpollCallback cb);
	void set_message_callback(EpollCallback cb);
	void set_close_callback(EpollCallback cb);
private:
	int _epollfd;
	int _listenfd; 
	bool _is_looping;
	std::vector<struct epoll_event> _event_list;
	std::map<int, TcpConnectionPtr> _conn_map;
	EpollCallback _on_connection_cb;
	EpollCallback _on_message_cb;
	EpollCallback _on_close_cb;
	int create_epollfd();
	void add_epollfd(int efd, int fd);
	void del_epollfd(int efd, int fd);
	int accept_connection(int listenfd);
	void wait_epollfd();
	void handle_connection();
	void handle_message(int peerfd);
};
#endif
