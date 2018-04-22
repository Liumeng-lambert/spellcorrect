 ///
 /// @file    main.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-02-13 11:08:33
 ///
 
#include <iostream>
#include "configuration.hpp"
#include "dictionary.hpp"
#include "splitTool.hpp"
#include "tcpserver.hpp"

int main(){
	unsigned short port = 9009;
	TcpServer* server = new TcpServer(port);
	server->start();
	return 0;
}

