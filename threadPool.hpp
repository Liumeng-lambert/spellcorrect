 ///
 /// @file    threadPool.hpp
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-02-18 09:40:30
 ///

#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
#include <unistd.h>
#include <set>
#include <condition_variable>
#include "task.hpp"
#include "cache.hpp"

namespace spellCorrect{
class ThreadPool;

class MyThread{
public:
	MyThread(ThreadPool & thread_pool);
	~MyThread();
	void join();
	Cache& get_cache();
private:
	Cache _cache;
	ThreadPool & _thread_pool;
	std::thread _thread;
};

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

class MyTask:public Task{
public:
    MyTask(const std::string& query_word, int peerfd);
    virtual void process(Cache & cache);
	virtual void process();
private:
    std::string _query_word;
    int _peerfd;
    std::priority_queue<MyResult, 
		          std::vector<MyResult> > _result_que;
	void query_index_table();
    void statistic(std::set<int> & iset);
    int distance(const std::string & rhs);
    void response(Cache & cache);                      
};

class ThreadPool{
public:
	ThreadPool(int thread_num = 10);
	~ThreadPool();
	void start();
	void stop();
	void add_task(Task* task);
	void thread_func(Cache & cache);
	bool is_running();
private:
	/*capacity of _vec_thread*/
	int _thread_capacity;
	/*condition of _task_que*/
	std::condition_variable _not_empty;
	std::condition_variable _not_full;
	std::mutex _mutex_lock;
	bool _is_running;
	Task* get_task();

	std::queue <Task*> _task_que;
	std::vector <MyThread*> _vec_thread;
};
}
#endif
