#pragma once

#include "config.h"
#include "configHandler.h"
#include "errorStatus.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iterator>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::inserter;

class ConsoleCmdHandler
{
public:
	ConsoleCmdHandler(const string&, vector<string>);
	~ConsoleCmdHandler();

	void showErrorStatus() const;

private:

	static const int NUMBER_OF_COMMAND = 5;
	static const string commandList[ConsoleCmdHandler::NUMBER_OF_COMMAND];

	ConfigHandler* m_config;
	ErrorStatus* m_error;

	typedef void (ConsoleCmdHandler::*ptrHandler)(vector<string>);
	map<string, ptrHandler> cmdHandlers;

	void helpHandler(vector<string>);
	void versionHandler(vector<string>);
	void targetShowAllHandler(vector<string>);
	void targetShowHandler(vector<string>);
	void targetRunHandler(vector<string>);	

};