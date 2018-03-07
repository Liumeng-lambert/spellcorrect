 ///
 /// @file    epoll.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-07 15:32:58
 ///
 
#include <iostream>
#include "epoll.hpp"
EpollPoller::EpollPoller(int listenfd) {

}

EpollPoller::~EpollPoller() {

}

void EpollPoller::loop() {

}

void EpollPoller::unloop() {

}

void EpollPoller::run_in_loop(const Functor & cb) {

}

void EpollPoller::set_connection_callback(EpollCallback cb) {

}

void EpollPoller::set_message_callback(EpollCallback cb) {

}

void EpollPoller::set_close_callback(EpollCallback cb) {

}

void EpollPoller::wait_epollfd() {

}

void EpollPoller::handle_connection() {

}

void EpollPoller::handle_message(int peerfd) {

}
