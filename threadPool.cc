 ///
 /// @file    threadPool.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-02-18 10:07:47
 ///
 
#include <iostream>
#include "threadPool.hpp"
namespace spellCorrect{
MyThread::MyThread(ThreadPool & thread_pool) 
:_thread_pool(thread_pool),
 thread(&ThreadPool::thread_func, &thread_pool),
 _cache(_thread_pool.get_cache())
{

}

ThreadPool::ThreadPool(int thread_num)
:_is_running(false)
{
	_thread_capacity = thread_num;
	_vec_thread.reserve(thread_num);
}

ThreadPool::~ThreadPool(){
	if(_is_running) {
		stop();
	}
}

void ThreadPool::start(){
	for(int i = 0; i < _thread_capacity; ++i) {
		MyThread* p_thread = new MyThread(*this);
		_vec_thread.push_back(p_thread);
	}
	_is_running = true;
}

void ThreadPool::stop(){
	if(_is_running) {
		/*wait for empty*/
		while(!_task_que.empty()) {
			sleep(1);
		}
		_is_running = false;
		/*actually,unique_lock can set free itself while destroying*/
		_not_empty.notify_all();
		_not_full.notify_all();
		for(int i = 0; i < _vec_thread.size(); ++i) {
			_vec_thread[i]->join();
		}
	}
}

void ThreadPool::thread_func(){
	while(_is_running) {
		Task *task = get_task();
		if(task){
			task->process();
		}
	}
}

void ThreadPool::add_task(Task * task){
	std::unique_lock <std::mutex> lock(_mutex_lock);
	/*can not contine if it is full
	 and if it is empty, notify one after adding*/
	if(_task_que.size() == 0){
		_task_que.push(task);
		_not_empty.notify_one();
	}else if(_task_que.size() == _thread_capacity) {
		_not_full.wait(lock);
	}else {	
		_task_que.push(task);
	}
}

Task* ThreadPool::get_task(){
	std::unique_lock <std::mutex> lock(_mutex_lock);
	/*can not contine if it is empty
	 and if it is full, notify one after poping*/
	if(_task_que.size() == 0) {
		_not_empty.wait(lock);
	}else if(_task_que.size() == _thread_capacity){
		_not_full.notify_one();
	}
	Task * tmp = _task_que.front();
	_task_que.pop();
	return tmp;
}

Cache& ThreadPool::get_cache() {
	return _cache;
}

}
