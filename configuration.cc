 ///
 /// @file    configuration.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-02-15 09:23:21
 ///
 
#include <sstream>
#include <fstream>
#include "configuration.hpp"
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
		char buffer[256];
        ifs.getline (buffer,256);
        std::stringstream strm(buffer, std::ios::binary);
		char tmp1[128];
		char tmp2[128];
		sscanf(buffer, "%s:%s", tmp1, tmp2 );
		std::pair<std::string, std::string> p (tmp1, tmp2);
		_config_map.insert(p);
    }
	ifs.close();
}

std::map<std::string, std::string> & Configuration::get_config_map(){
	return _config_map;
}

}
