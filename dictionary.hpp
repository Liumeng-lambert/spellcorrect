///                                                                                                                 
/// @file    dictionary.hpp
/// @author  lambert(Liumeng_lambert@163.com)
/// @date    2018-02-12 18:00:01
///
#ifndef _SPELL_CORRECT_DICTIONARY_H_
#define _SPELL_CORRECT_DICTIONARY_H_
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "splitTool.hpp"
#include "log.hpp"

namespace spellCorrect{

class DictProducer{
public:
	DictProducer(const std::string& dir);
	DictProducer(const std::string& dir, SplitTool* splitTool);
	static void remove_punct(std::string &word);
	void build_dict();
	void build_cn_dict();

	void store_dict(const char * filepath);

	void show_files()const;
	void show_dict()const; 
	/*get file absolute path*/
	void get_files();
private:
	void push_dict(const std::string & word);
	/*file absolute path*/
    std::string _dir;
	/*all files' name*/
	std::vector<std::string> _files;
	std::map<std::string,int> _dict;
	/*split tool, for chinese dictionary */
	SplitTool* _split_tool;
	LogPrinter*  _log_printer;
};

}
#endif
