 ///
 /// @file    log.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-02-15 13:24:22
 ///

#include <fstream>
#include "log.hpp"

std::string LogPrinter::get_current_time(){
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&t));
	std::string my_time = tmp;
	return my_time; 
}

void LogPrinter::export_log(std::string info, std::string log_path) {
	std::ofstream ostrm(log_path, std::ios::app);
	std::string cur_time = get_current_time();
	ostrm << cur_time << ":" << info << std::endl;
	ostrm.close();
}
