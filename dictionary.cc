 ///
 /// @file    dictionary.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-02-12 18:22:21
 ///
 
#include <sstream>
#include <fstream>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <cctype>
#include "dictionary.hpp"
#include "log.hpp"
namespace spellCorrect{
DictProducer::DictProducer(const std::string& dir)
:_dir(dir)
{
	struct dirent* dir_info;
	DIR * p_dir = opendir(dir.c_str());
	if(NULL == p_dir){
		LogPrinter::export_log("error to open dir", "log/log.txt");
		exit(EXIT_FAILURE);
	}
	while(dir_info = readdir(p_dir)) {
		if(strcmp(dir_info->d_name, ".") == 0 
		   || strcmp(dir_info->d_name, "..") == 0) {
			continue;
		}
		_files.push_back(dir_info->d_name);
	}

	build_dict();
	store_dict("dict/dict_en.txt");
	show_files();
}

DictProducer::DictProducer(const std::string& dir, SplitTool* splitTool)
:_dir(dir)
{
	struct dirent* dir_info;
	DIR * p_dir = opendir(dir.c_str());
	if(NULL == p_dir){
		std::cout << "error to open dir" << std::endl;
		exit(EXIT_FAILURE);
	}
	while(dir_info = readdir(p_dir)) {
		if(strcmp(dir_info->d_name, ".") == 0 
		   || strcmp(dir_info->d_name, "..") == 0) {
			continue;
		}
		_files.push_back(dir_info->d_name);
	}
	_split_tool = splitTool;
	build_cn_dict();
	store_dict("dict/dict_cn.txt");
}

void DictProducer::remove_punct(std::string &word) {
	std::string ans = "";
	for(auto c : word) {
		/*TODO:special charactor input*/
		if(isalpha(c)) {
			ans += c;
		}
	}
	word = ans;
}

void DictProducer::build_dict(){
	LogPrinter::export_log("build dictionary", "log/log.txt");
	for(auto i : _files) {
		/*open every file in /data */
		std::string path = _dir + "/" + i;
		std::cout << path << std::endl;
		std::ifstream istrm(path, std::ios::binary);
		if(!istrm.is_open())
    	{
			LogPrinter::export_log("open readfile failed", "log/log.txt");
        	return;
    	}
		while(!istrm.eof()) {
			std::string word;
			while(istrm >> word) {
				/*removal punctuations*/
				remove_punct(word);
				if(word.empty()){
					continue;
				}
				push_dict(word);
			}
		}
	}
}

/*TODO:get chinese dictionary from language source*/
void DictProducer::build_cn_dict(){

}

void DictProducer::store_dict(const char * filepath){
	LogPrinter::export_log("store dict", "log/log.txt");
	std::fstream s(filepath, s.binary | s.trunc | s.out);
	if (!s.is_open()) {
		std::string info = "failed to open ";
		info += filepath;
		LogPrinter::export_log(info, "log/log.txt");
	}else {
		for(auto i : _dict) {
			s<< i.first << " " << i.second << std::endl;
		}
	}
	s.close();
}

void DictProducer::show_files()const{
	for(auto i : _files) {
		std::cout << i << std::endl;
	}
}

void DictProducer::show_dict()const{
	for(auto i : _dict){
		std::cout << i.first << " : " << i.second << std::endl;
	}
}

void DictProducer::get_files(){
	std::cout << _dir << std::endl;
}

void DictProducer::push_dict(const std::string & word){
	if(_dict.find(word) != _dict.end()) {
		_dict[word] += 1;	
	} else {
		_dict[word] = 1;
	}	
}

}
