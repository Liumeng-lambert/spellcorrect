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
#include "spellcorrect.hpp"
#include "index.hpp"

int main(){
	unsigned short port = 9009;
	spellCorrect::Index *index = new spellCorrect::Index();
	spellCorrect::SpellCorrectServer* server = new spellCorrect::SpellCorrectServer("config/config", *index);
	server->start();
	return 0;
}

