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
#ifdef  TASK_0_2_5__4
	/*const wstring& getAsWString() const;*/
#endif
	vector<string> getAsLineList() const;
	bool isExist() const;
	char get();

	vector<vector<string>> getCmdLists();
	vector<string> getCmdArgList(const string&);

	string getStream();

private:

	stringstream m_ss;
	string m_file;
#ifdef  TASK_0_2_5__4
	//wstring m_wfile;
#endif
	string m_path;
	bool m_file_exist;
	int m_error_status;

	const static int error_cmd_format = 0b1;
};
