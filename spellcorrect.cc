 ///
 /// @file    spellcorrect.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-16 17:01:17
 ///
 
#include <iostream>
#include <functional>
#include "spellcorrect.hpp"

namespace spellCorrect{

WordQuery::WordQuery()
:_query_word(),
 _max_query_len(100),
 _index("dict/dict_en.txt")
{
}

WordQuery::~WordQuery() {

}

std::string WordQuery::execute(std::string query_word, Cache& cache) {
	_query_word = query_word;
	//find in cache
	std::string ans = cache.query_cache(_query_word);
	//not found in cache
	if(ans.empty()) {
		ans = query_index_table();
	}
	return ans;
}

std::string WordQuery::query_index_table() {
	const std::map<std::string, std::set<int> > &m_index = _index.get_index();		
	std::set<int> i_set;
	for(auto c : _query_word) {
		//TODO:deal with input word
		if(!isalpha(c))continue;
		std::string s(1, c);
		/*const,use at instead of []*/
		for(auto i : m_index.at(s)) {
			i_set.insert(i);
		}
	}	
	statistic(i_set);
	return _result_que.top()._word;
}
/*caculate from reverse index*/
void WordQuery::statistic(std::set<int> & iset) {
	const std::vector<std::pair<std::string, int> > & v_word = _index.get_wordlist();
	while(!_result_que.empty()) {
		_result_que.pop();
	}
	for(auto i : iset) {
		struct MyResult r;
		r._word = v_word[i].first;
		r._freq = v_word[i].second;
		r._dist = distance(r._word);
		_result_que.push(r);
	}
}

int WordQuery::distance(const std::string & rhs) {
	int lr = rhs.size();
	int lq = _query_word.size();
	const size_t len = _max_query_len + 1;
	int dis[len][len];
	for(int i = 0; i < lr; ++i) {
		dis[i][0] = i;
	}
	for(int j = 0; j < lq; ++j) {
		dis[0][j] = j;
	}
	for(int i = 1; i < lr; ++i) {
		for(int j = 1; j < lq; ++j) {
			int flag = (rhs[i] == _query_word[j])? 0 : 2;
			/*insert_cost*/
			int in_cost = dis[i-1][j] + 1;
			/*delete_cost*/
			int de_cost = dis[i][j - 1] + 1;
			/*replace_cost*/
			int re_cost = dis[i - 1][j - 1] + flag;
			dis[i][j] = (in_cost < de_cost)?
				         in_cost : de_cost;
			dis[i][j] = (dis[i][j] < re_cost)? 
				         dis[i][j] : re_cost;
		}
	}
	return dis[lr - 1][lq - 1];
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

SpellCorrectServer::SpellCorrectServer(const std::string & config_file)
:_conf(std::string("config/config")), 
 _tcp_server(9009),
 _threadpool(),
 _query(),
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
	std::cout << "server start!" << std::endl;
	_threadpool.start();
	_tcp_server.start();
}

void SpellCorrectServer::on_connection(TcpConnectionPtr conn) {
	std::cout << "Ready to search!" << std::endl;
}

void SpellCorrectServer::on_message(TcpConnectionPtr conn) {
	std::string query_word = conn->receive();
	std::cout << "Start to search : " << query_word << std::endl;
	_threadpool.add_task(std::bind(&SpellCorrectServer::query_response, this, query_word, conn, std::placeholders::_1));
}

void SpellCorrectServer::on_close(TcpConnectionPtr conn) {
	std::cout << "Ready to close " << conn->to_string() << std::endl;
}

void SpellCorrectServer::query_response(std::string query_word, TcpConnectionPtr& conn, Cache &cache) {
	std::string result = _query.execute(query_word, cache);
	conn->send(result);
}

}
