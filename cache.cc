 ///
 /// @file    cache.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-02-23 16:36:29
 ///
 
#include <iostream>
#include "cache.hpp"
namespace spellCorrect{
Cache::Cache(int cache_size){
	_hash_map.reserve(cache_size);
	//build from file
}

Cache::Cache(const Cache & cache){
	_hash_map = cache._hash_map;
}

void Cache::addElement(const std::string &key, int value){
	std::pair<std::string, int>tmp(key, value);
	_hash_map.insert(tmp);
}

void Cache::readFromFile(const std::string & filename){

}

void Cache::writeToFile(const std::string & filename){

}

void Cache::update(const Cache & rhs){
	_hash_map.clear();
	_hash_map = rhs._hash_map;
}

}

