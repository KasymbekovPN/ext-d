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

class WFileHandler
{
public:
	WFileHandler(const wstring& file_name_);
	~WFileHandler();

	const wstring& wstring() const;
	bool is_exists() const;

private:
	std::wstring m_file_content;
	std::wstring m_path;
	bool m_file_exist;

};