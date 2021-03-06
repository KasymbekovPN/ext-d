#pragma once

#include "stringHandler.h"

#include <string>
#include <fstream>
#include <iostream>
#include <ios>
#include <vector>
#include <sstream>
#include <iterator>
#include <memory>
#include <codecvt>

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::stringstream;
using std::wstring;

class FileHandler
{
public:
	FileHandler(const string&);
	~FileHandler();

	const string& getAsString() const;
	bool isExist() const;

private:

	stringstream m_ss;
	string m_file;
	string m_path;
	bool m_file_exist;
	int m_error_status;

	const static int error_cmd_format = 0b1;
};
