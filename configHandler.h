#pragma once

#include "fileHandler.h"
#include "target.h"
#include "errorStatus.h"
#include "stringHandler.h"
#include "jsonObject.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <memory>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::shared_ptr;

class ConfigHandler
{
public:
	ConfigHandler(const string & path_, const string& path_json_, shared_ptr<ErrorStatus> p_error_);
	~ConfigHandler();

	void targetRun(const string&, const string&) const;
	void showAllTarget() const;
	void showTarget(const string&) const;

private:
	const string cmd_settarget = "SETTARGET";

	vector<Target*> m_targets;
	bool isExist;

	shared_ptr<ErrorStatus> p_error;
};