 ///
 /// @file    myThreadPool.hpp
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-02-16 16:47:25
 ///
 
#ifndef _SPELL_CORRECT_MYTHREADPOOL_H_
#define _SPELL_CORRECT_MYTHREADPOOL_H_
#include "threadPool.hpp"
#include "cache.hpp"
#include <iostream>
#include <vector>
#include <queue>
namespace searchEngine{
namespace spellCorrect{

class MyThreadPool : public ThreadPool {
public:
	MyThreadPool(int thread_num = 10);
	~MyThreadPool();
	void updata_cache();
private:
	Cache _cache;
};

}
}
#endif
