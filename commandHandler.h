#pragma once

#include "config.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::string;

class CommandHandler
{
public:
	CommandHandler(const vector<string>& );
	~CommandHandler();

	void run();

private:

	static const int NUMBER_OF_COMMAND = 3;
	static const string validCommandName[CommandHandler::NUMBER_OF_COMMAND];

	string command;	

	typedef void (CommandHandler::*ptr2Handler)();
	map<string, ptr2Handler> handlers;

	void helpHandler();
	void versionHandler();
	void runHandler();
};