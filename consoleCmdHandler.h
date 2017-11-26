#pragma once

#include "config.h"
#include "configHandler.h"

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

	static const int error_config_error =				0b00000001;
	static const int error_list_cmd_is_empty =			0b00000010;
	static const int error_invalid_console_cmd =		0b00000100;
	static const int error_help_hand_invalid_arg =		0b00001000;
	static const int error_ver_hand_invalid_arg =		0b00010000;
	static const int error_tar_show_all_invalid_arg =	0b00100000;
	static const int error_tar_show_invalid_arg =		0b01000000;
	static const int error_tar_run_invalid_arg =		0b10000000;

	int m_error;

	typedef void (ConsoleCmdHandler::*ptrHandler)(vector<string>);
	map<string, ptrHandler> cmdHandlers;

	void helpHandler(vector<string>);
	void versionHandler(vector<string>);
	void targetShowAllHandler(vector<string>);
	void targetShowHandler(vector<string>);
	void targetRunHandler(vector<string>);	

};