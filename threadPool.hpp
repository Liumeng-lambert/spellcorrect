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
class ThreadPool{
public:
	ThreadPool(int thread_num);
	~ThreadPool();
	void start();
	void stop();
	void threadFunc();	
	void add_task(Task* task);
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
	std::vector <std::thread> _vec_thread;
};
#endif
