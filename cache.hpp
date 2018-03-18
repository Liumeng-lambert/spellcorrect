 ///
 /// @file    cache.hpp
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-02-23 16:36:17
 ///

#ifndef _SPELL_CORRECT_CACHE_H_
#define _SPELL_CORRECT_CACHE_H_
#include <iostream>
#include <unordered_map>
namespace spellCorrect{
class Cache{
public:
	Cache(int cache_size = 10);
	Cache(const Cache & cache);
	void addElement(const std::string &key, int value);
	void readFromFile(const std::string & filename);
	void writeToFile(const std::string & filename);
	void update(const Cache & rhs);
private:
	std::unordered_map<std::string, int> _hash_map;

};

}

#endif
