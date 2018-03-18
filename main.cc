 ///
 /// @file    main.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-02-13 11:08:33
 ///
 
#include <iostream>
#include "configuration.hpp"
#include "dictionary.hpp"
#include "splitTool.hpp"
using spellCorrect::DictProducer;
int main(){
	DictProducer* dict_producer = new DictProducer("data");	
	return 0;
}

