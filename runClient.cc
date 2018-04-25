 ///
 /// @file    runClient.cc
 /// @author  lambert(Liumeng_lambert@163.com)
 /// @date    2018-04-22 17:07:12
 ///
 
#include <iostream>
#include "client.hpp"

int main() {
	Client* client = new Client("172.16.252.249", 9009);
	client->start();
	return 0;
}
