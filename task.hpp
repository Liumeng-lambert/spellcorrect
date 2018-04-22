 ///
 /// @file    task.hpp
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-02-18 09:33:49
 ///

#ifndef _TASK_H_
#define _TASK_H_
#include <iostream>
#include "cache.hpp"
namespace spellCorrect{
class Task{
public:
	Task(){}
	~Task(){}
	virtual void process()=0;
	virtual void process(Cache & cache)=0;
};
}
#endif
