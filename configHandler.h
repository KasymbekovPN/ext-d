#pragma once

#include "fileHandler.h"
#include "target.h"
#include "errorStatus.h"

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

	ErrorStatus errorStatus() const;
	ErrorStatus targetRun(const string&) const;
	ErrorStatus showAllTarget() const;
	ErrorStatus showTarget(const string&) const;

private:
	const string cmd_settarget = "SETTARGET";

	vector<Target*> m_targets;
	bool isExist;

	ErrorStatus* m_error;
};