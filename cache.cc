 ///
 /// @file    cache.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-02-23 16:36:29
 ///
 
#include <iostream>
#include <fstream>
#include <sstream>
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
	while(!ifstrm.eof()) {
		char buffer[256];
		ifstrm.getline (buffer,256);
		std::stringstream strm(buffer, std::ios::binary);
		char query[128];
		char result[128];
		sscanf(buffer, "%s:%s", query, result);
		_hash_map.insert(std::pair<std::string, std::string >(query, result));
	}
	ifstrm.close();

}

void Cache::write_to_file(const std::string & filename){
	std::fstream fs(filename, fs.binary | fs.out);
	for(auto i : _hash_map) {
		fs << i.first << " " << i.second << std::endl;
	}
	fs.close();
}

void Cache::update(const Cache & rhs){
	//TODO:update in better way? LRU or something else?
	for(auto i : rhs._hash_map) {
		if(_hash_map.find(i.first) == _hash_map.end()) {
			_hash_map.insert(i);
		}
	}
}

std::string Cache::query_cache(std::string query_word) {
	if(_hash_map.find(query_word) != _hash_map.end()) {
		return _hash_map[query_word];
	}else{
		return std::string("");
	}
}

}

