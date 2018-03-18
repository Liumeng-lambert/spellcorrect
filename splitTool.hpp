 ///
 /// @file    splitTool.hpp
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-02-12 18:04:07
 ///
#ifndef _SPELL_CORRECT_SPLIT_TOOL_H_
#define _SPELL_CORRECT_SPLIT_TOOL_H_
#include <iostream>
#include "configuration.hpp"
namespace spellCorrect{

class SplitTool{
public:
	SplitTool();
	virtual ~SplitTool();
	virtual std::vector<std::string> cut(const std::string & sentence)=0;
};

class SplitToolNLPIR : public SplitTool{
public:
	SplitToolNLPIR(Configuration& config);
	virtual ~SplitToolNLPIR();
	virtual std::vector<std::string> cut(const std::string & sentence)=0;
private:
	Configuration & _conf;
};

}

#endif
