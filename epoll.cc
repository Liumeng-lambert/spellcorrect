 ///
 /// @file    epoll.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-07 15:32:58
 ///
 
#include <iostream>
#include <unistd.h>
#include "epoll.hpp"
EpollPoller::EpollPoller(int listenfd)
:_epollfd(create_epollfd()), _listenfd(listenfd),
_is_looping(false), _event_list(1024)
{
	add_epollfd(_epollfd, listenfd);
}

void EpollPoller::loop() {
	_is_looping = true;
	while(_is_looping)
	{
		wait_epollfd();
	}	
}

void EpollPoller::unloop() {
	if(_is_looping) {
		_is_looping = false;
	}
}

bool EpollPoller::in_connection(int connfd) {
	char buf[1024];
	int ready;
	do{
		recv(connfd, buf, 1024, MSG_PEEK);
	} while(-1 == ready && errno == EINTR);
	return ready == 0;
}
/*
//this function can call by other thread
void EpollPoller::run_in_loop(const Functor & cb) {
	//if called by itself
	if(_is_looping)	{
		cb();
	} else {				//called by other thread
		
	}
}
*/
void EpollPoller::set_connection_callback(EpollCallback cb) {
	_on_connection_cb = cb;
}

void EpollPoller::set_message_callback(EpollCallback cb) {
	_on_message_cb = cb;
}

void EpollPoller::set_close_callback(EpollCallback cb) {
	_on_close_cb = cb;
}

int EpollPoller::create_epollfd() {
	int epfd = epoll_create(1024);
	if(epfd < 0) {  
		perror("epoll create error");  
		exit(EXIT_FAILURE);  
	}
	return epfd;
}

void EpollPoller::add_epollfd(int efd, int fd) {
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	int ret = epoll_ctl(efd, EPOLL_CTL_ADD, fd, &ev);
	if(ret < 0) {
		perror("add_epollfd error");
		exit(EXIT_FAILURE);
	}
}

void EpollPoller::del_epollfd(int efd, int fd) {
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	int ret = epoll_ctl(efd, EPOLL_CTL_DEL, fd, &ev);
	if(ret < 0) {
		perror("delete_epollfd error");
		exit(EXIT_FAILURE);
	}
}

int EpollPoller::accept_connection(int listenfd) {
	/*can get remote machine info*/
    int connection_fd = ::accept(listenfd, NULL, NULL);
    if (connection_fd == -1) {
        //LogPrinter::export_log("error to accept", "log/socketLog.txt");
        close(connection_fd);
        exit(EXIT_FAILURE);
    }
    return connection_fd;	
}

void EpollPoller::wait_epollfd() {
    int nfds = epoll_wait(_epollfd, &*_event_list.begin(), _event_list.size(), 500);
    for(int i = 0; i < nfds; ++i){
		/*receive new connection request*/
        if(_event_list[i].data.fd == _listenfd) { 
			handle_connection();
		} else if(_event_list[i].events & EPOLLIN ) { 
			/*have message to read socket*/
			handle_message(_event_list[i].data.fd);
		} else if(_event_list[i].events & EPOLLOUT)  { 
			/*have message to send，write to socket*/
		} else{   
			// other situation
        }
    }
}	

void EpollPoller::handle_connection() {
	int conn_fd = accept_connection(_listenfd);	
	add_epollfd(_epollfd, conn_fd);

	TcpConnectionPtr p_tcp_conn(new TcpConnection(conn_fd));
	p_tcp_conn-> set_connection_callback(_on_connection_cb);
	p_tcp_conn-> set_message_callback(_on_message_cb);
	p_tcp_conn-> set_close_callback(_on_close_cb);
	_conn_map.insert(std::make_pair(conn_fd, p_tcp_conn));
	p_tcp_conn->handle_connection_callback();
}

void EpollPoller::handle_message(int peerfd) {
	auto iter = _conn_map.find(peerfd);
	if(iter != _conn_map.end()) {
		bool stat = in_connection(peerfd);
		if(stat) {
			iter->second->handle_message_callback();	
		} else {
			del_epollfd(_epollfd, peerfd);
			iter->second->handle_close_callback();
			_conn_map.erase(iter);
		}
	}
}
