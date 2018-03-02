 ///
 /// @file    configuration.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-02-15 09:23:21
 ///
 
#include <sstream>
#include <fstream>
#include "configuration.hpp"
namespace searchEngine{
namespace spellCorrect{
Configuration::Configuration(const std::string& filepath)
:_filepath(filepath)
{
	_config_map = get_config_map();
	std::ifstream ifs(_filepath, std::ios::binary);
	if (!ifs.is_open()) {
		std::cout << "failed to open " << _filepath << '\n';
	}
	while (!ifs.eof()) {
		/*read config file*/
		char buffer[100];
        ifs.getline (buffer,100);
        std::stringstream strm(buffer, std::ios::binary);
		char tmp1[100];
		char tmp2[100];
		sscanf(buffer, "%s:%s", tmp1, tmp2 );
		std::pair<std::string, std::string> p;
		_config_map.insert(p);
    }
	ifs.close();
}

std::map<std::string, std::string> & Configuration::get_config_map(){
	return _config_map;
}

}
}
