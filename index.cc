 ///
 /// @file    index.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-04-25 22:45:39
 ///
 
#include "index.hpp"
#include <fstream>

namespace spellCorrect{
Index::Index(const std::string dict_path) {
	std::ifstream ifs (dict_path, ifs.binary);
	if (!ifs.is_open()) {                                
		std::string info = "failed to open ";
		info += dict_path;
		LogPrinter::export_log(info, "log/log.txt");
	}else {
		while(!ifs.eof()) {
			std::string word;
			std::string freq;
			while(ifs >> word >> freq) {
				int i_freq = atoi(freq.c_str());
				std::pair<std::string, int> tmp = {word, i_freq};
				_words_freq.push_back(tmp);
			}
		}
	}
	ifs.close();
	/*get reverse index*/
	for(int i = 0; i < _words_freq.size(); ++i) {
		for(auto c : _words_freq[i].first) {
			if(!isalpha(c))std::cout << "wrong" << std::endl;
			std::string tmp (1, c);
			
			_index[tmp].insert(i);
		}
	}
}

Index::~Index() {

}

/*use const ref return instead of friend to keep*/
/*encapsulation of class index*/
const std::map<std::string, std::set<int> >& Index::get_index() const{ 
	return _index;
}

const std::vector<std::pair<std::string, int> >& Index::get_wordlist() const{ 
	return _words_freq;
}
}
