 ///
 /// @file    index.hpp
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-02-16 15:12:16
 ///

#ifndef _SPELL_CORRECT_INDEX_H_
#define _SPELL_CORRECT_INDEX_H_
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "log.hpp"

namespace spellCorrect{
/*reverse index*/
class Index{
public:
	Index(const std::string dict_path);	
	~Index();
	const std::map<std::string, std::set<int> >& get_index() const;
	const std::vector<std::pair<std::string, int> > &get_wordlist() const;
private:
	std::vector<std::pair<std::string, int> > _words_freq;
	std::map<std::string, std::set<int> > _index;
};

}
#endif
