///                                                                                                                 
/// @file    configuration.hpp
/// @author  lambert(Liumeng_lambert@163.com)
/// @date    2018-02-15 09:20:01
///
#ifndef _SPELL_CORRECT_CONFIGURATION_H_
#define _SPELL_CORRECT_CONFIGURATION_H_
#include <iostream>
#include <vector>
#include <string>
#include <map>

namespace searchEngine{
namespace spellCorrect{

class Configuration{
public:
	Configuration(const std::string& filepath);
private:
	std::map<std::string,std::string> & get_config_map();
	std::string _filepath;
	std::map<std::string, std::string> _config_map;
};

}
}
#endif
