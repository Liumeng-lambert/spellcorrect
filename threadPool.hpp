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
#include <functional>
//#include "task.hpp"
#include "cache.hpp"

namespace spellCorrect{
class ThreadPool;

class MyThread{
public:
	MyThread(ThreadPool & thread_pool, Cache &cache);
	~MyThread();
	void join();
	Cache& get_cache();
private:
	Cache _cache;	
	std::thread _thread;
};

class ThreadPool{
	typedef std::function <void(Cache&)> Task;
public:
	ThreadPool(int thread_num = 10);
	~ThreadPool();
	void start();
	void stop();
	void add_task(Task task);
	void thread_func(Cache& cache);
	bool is_running();
	void update_cache();
private:
	/*capacity of _vec_thread*/
	int _thread_capacity;
	/*condition of _task_que*/
	Cache _main_cache;
	std::condition_variable _not_empty;
	std::condition_variable _not_full;
	std::mutex _mutex_lock;
	bool _is_running;
	std::queue <Task> _task_que;
	std::vector <MyThread*> _vec_thread;
	
	Task get_task();
};
}
#endif
