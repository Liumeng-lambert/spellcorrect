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
#include <condition_variable>
#include "task.hpp"
#include "cache.hpp"
namespace spellCorrect{
class ThreadPool;

class MyThread:public std::thread{
public:
	MyThread(ThreadPool & thread_pool);
private:
	Cache _cache;
	ThreadPool & _thread_pool;
};

class ThreadPool{
public:
	ThreadPool(int thread_num = 10);
	~ThreadPool();
	void start();
	void stop();
	void thread_func();	
	void add_task(Task* task);
	Cache& get_cache();
private:
	/*capacity of _vec_thread*/
	int _thread_capacity;
	/*condition of _task_que*/
	std::condition_variable _not_empty;
	std::condition_variable _not_full;
	std::mutex _mutex_lock;
	bool _is_running;
	Task* get_task();
	Cache _cache;

	std::queue <Task*> _task_que;
	std::vector <MyThread*> _vec_thread;
};
}
#endif
