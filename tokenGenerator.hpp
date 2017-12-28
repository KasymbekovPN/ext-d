#pragma once

#include "fileHandler.h"
#include "token.hpp"

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class TokenGenerator
{
public:
	TokenGenerator(const string& path_);

	bool equal(const string& path_);
	void parse();

	void show();

private:

	string m_module_name;
	string m_path;
	bool m_was_source;
	bool m_was_header;
};