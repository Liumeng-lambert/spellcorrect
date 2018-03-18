 ///
 /// @file    spellcorrect.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-16 17:01:17
 ///
 
#include <iostream>
#include <functional>
#include "spellcorrect.hpp"
namespace spellCorrect{

TimeThread::TimeThread() 
:_is_running(false),
 _timer(std::bind(&TimeThread::thread_func, this))
{
}

TimeThread::~TimeThread() {
	_is_running = false;
	_timer.join();
}

void TimeThread::start() {
	_is_running = true;
	thread_func();
}

bool TimeThread::is_running() {
	return _is_running;
}

void TimeThread::thread_func() {
	while(_is_running) {
		sleep(60);

	}
}

SpellCorrectServer::SpellCorrectServer(const std::string & config_file)
:_conf(std::string("conf/config")), 
 _tcp_server(2000)
{
	
}

void SpellCorrectServer::start() {
	
}

void SpellCorrectServer::on_connection(TcpConnectionPtr conn) {

}

void SpellCorrectServer::on_message(TcpConnectionPtr conn) {

}

void SpellCorrectServer::on_close(TcpConnectionPtr conn) {

}

}
