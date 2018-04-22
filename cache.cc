 ///
 /// @file    cache.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-02-23 16:36:29
 ///
 
#include <iostream>
#include <fstream>
#include "cache.hpp"
namespace spellCorrect{
Cache::Cache(int cache_size){
	_hash_map.reserve(cache_size);
	//build from file
	std::string file_name = "cache/cache.dat";
	read_from_file(file_name);
}

Cache::Cache(const Cache & cache){
	_hash_map = cache._hash_map;
}

void Cache::add_element(const std::string &key, std::string value){
	std::pair<std::string, std::string>tmp(key, value);
	_hash_map.insert(tmp);
}

void Cache::read_from_file(const std::string & filename){
	std::ifstream ifstrm(filename, std::ios::binary);
	if(!ifstrm){
		std::cout << "cache file: " << filename << std::endl ; 
		throw std::runtime_error("open cache file fail !");
	}
	std::string query, result;
	while(ifstrm >> query >> result) {
		_hash_map.insert(std::pair<std::string, std::string >(query, result));
	}
	ifstrm.close();

}

void Cache::write_to_file(const std::string & filename){

}

void Cache::update(const Cache & rhs){
	_hash_map.clear();
	_hash_map = rhs._hash_map;
}

}

