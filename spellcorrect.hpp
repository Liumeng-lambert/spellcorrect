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

namespace spellCorrect{
struct MyResult{
	std::string _word;
	//appear frequency
	int _freq;
	//distance between this word and the input word
	int _dist;
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
	SpellCorrectServer(const std::string & config_file);
	void start();
	void on_connection(TcpConnectionPtr conn);
	void on_message(TcpConnectionPtr conn);
	void on_close(TcpConnectionPtr conn);
private:
	Configuration _conf;
	TcpServer _tcp_server;
	ThreadPool _threadpool;
	TimeThread _timer;
};

}
#endif
