#pragma once

#include "config.h"
#include "configHandler.h"
#include "errorStatus.h"
#include "json/jsonObject.hpp"

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <memory>
#include <functional>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::inserter;
using std::shared_ptr;

class ConsoleCmdHandler
{
public:
	ConsoleCmdHandler(const string& config_path_json_, vector<string> command_);
	~ConsoleCmdHandler();

	void showErrorStatus() const;

private:

	static const int NUMBER_OF_COMMAND = 5;
	static const string commandList[ConsoleCmdHandler::NUMBER_OF_COMMAND];

	ConfigHandler* m_config;

	shared_ptr<ErrorStatus> p_error;

	typedef void (ConsoleCmdHandler::*ptrHandler)(vector<string>);
	map<string, ptrHandler> cmdHandlers;

	void helpHandler(vector<string>);
	void versionHandler(vector<string>);
	void targetShowAllHandler(vector<string>);
	void targetShowHandler(vector<string>);
	void targetRunHandler(vector<string>);	

};
