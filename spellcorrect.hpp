 ///
 /// @file    spellcorrect.hpp
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-11 17:24:56
 ///

#ifndef _SPELL_CORRECT_FUNCTION_H_
#define _SPELL_CORRECT_FUNCTION_H_
#include <iostream>
#include <thread>
#include "configuration.hpp"
#include "tcpserver.hpp"
#include "threadPool.hpp"
#include "index.hpp"

namespace spellCorrect{

struct MyResult{
	std::string _word;
	//appear frequency
	int _freq;
	//distance between this word and the input word
	int _dist;
	bool operator < (const MyResult & rhs) const{
		if(_dist == rhs._dist){
			return _freq < rhs._freq;
		}
		return _dist < rhs._dist;
	}
};

class WordQuery{
public:
    WordQuery(Index &index);
	~WordQuery();
	void execute(std::string query_word, Cache& cache);
private:
    std::priority_queue<MyResult, 
		          std::vector<MyResult> > _result_que;
	void query_index_table(std::string query_word);
    void statistic(std::set<int> & iset);
    int distance(const std::string & rhs);
    void response(Cache & cache);
};

class TimeThread {
public:
	TimeThread();
	~TimeThread();
	bool is_running();
	void start();
private:
	void thread_func();
	bool _is_running;
	std::thread _timer;
};

class SpellCorrectServer {
public:
	SpellCorrectServer(const std::string & config_file, Index& index);
	void start();
	void on_connection(TcpConnectionPtr conn);
	void on_message(TcpConnectionPtr conn);
	void on_close(TcpConnectionPtr conn);
private:
	Configuration _conf;
	TcpServer _tcp_server;
	ThreadPool _threadpool;
	WordQuery _query;
	TimeThread _timer;
};

}
#endif
