#pragma once

#include "fileHandler.h"
#include <target.h>

#include <string>
#include <vector>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class ConfigHandler
{
public:
	ConfigHandler(const string&);
	~ConfigHandler();

	int errorStatus() const;
	void targetRun(const string&) const;
	void showAllTarget() const;
	void showTarget(const string&) const;

private:
	const string cmd_settarget = "SETTARGET";

	const static int error_cnf_file_no_exists	 = 0b01;
	const static int error_cmd_settarget_invalid = 0b10;

	vector<Target*> m_targets;
	bool isExist;
	int m_error_status;
};