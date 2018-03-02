 ///
 /// @file    log.hpp
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-03-02 11:53:28
 ///

#ifndef _LOG_H_
#define _LOG_H_
#include <iostream>

class LogPrinter{
public:
	static LogPrinter * inst(){  
        if (NULL != _instance){  
           return _instance; 
        }  
		_instance = new LogPrinter();
		return _instance;
    }	
	static void export_log(std::string info, std::string log_path);
private:
	static LogPrinter*  _instance;
	static std::string get_current_time();
};

#endif
