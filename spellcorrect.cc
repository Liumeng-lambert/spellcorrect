 ///
 /// @file    spellcorrect.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-16 17:01:17
 ///
 
#include <iostream>
#include <functional>
#include "spellcorrect.hpp"
namespace spellCorrect{

WordQuery::WordQuery(Index &index)
{       
}

WordQuery::~WordQuery() {

}

void WordQuery::execute(std::string query_word, Cache& cache) {
	std::cout << "success!" << std::endl;	
}

void WordQuery::query_index_table(std::string query_word) {

}
/*caculate from reverse index*/
void WordQuery::statistic(std::set<int> & iset) {

}

int WordQuery::distance(const std::string & rhs) {

}

void WordQuery::response(Cache & cache) {

}

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

SpellCorrectServer::SpellCorrectServer(const std::string & config_file, Index& index)
:_conf(std::string("config/config")), 
 _tcp_server(9009),
 _threadpool(),
 _query(index),
 _timer()
{
	_tcp_server.set_connection_callback(std::bind(&SpellCorrectServer::on_connection, this, std::placeholders::_1 ));
	_tcp_server.set_message_callback(std::bind(&SpellCorrectServer::on_message, this, std::placeholders::_1 ));
	_tcp_server.set_close_callback(std::bind(&SpellCorrectServer::on_close, this, std::placeholders::_1 ));
}

void SpellCorrectServer::start() {
	/*
	_tcp_server.set_connection_callback(on_connection);
	_tcp_server.set_message_callback(on_message);
	_tcp_server.set_close_callback(on_close);
	*/
	_threadpool.start();
	_tcp_server.start();
}

void SpellCorrectServer::on_connection(TcpConnectionPtr conn) {
	std::cout << "Ready to search!" << std::endl;
}

void SpellCorrectServer::on_message(TcpConnectionPtr conn) {
	std::string query_word = conn->receive();
	std::cout << "Start to search : " << query_word << std::endl;
	_threadpool.add_task(std::bind(&WordQuery::execute, &_query, query_word, std::placeholders::_1));
}

void SpellCorrectServer::on_close(TcpConnectionPtr conn) {
	std::cout << "Ready to close " << conn->to_string() << std::endl;
}


}
