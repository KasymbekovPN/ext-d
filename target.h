#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <Windows.h>

#include "fileHandler.h"
#include "stringHandler.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;

class Target
{
public:
	Target(const string&, const string&);

	string getName() const;
	string getPath() const;
	bool isExist() const;

private:
	string	m_name;
	string	m_path;
	bool	is_exist;
	string	m_source_dir;
	bool	m_source_dir_was_set;
	bool	m_source_dir_exists;
	string	m_output_dir;
	bool	m_output_dir_was_set;
	bool	m_output_dir_exists;

	const string cmd_set_source_dir = "SET_SOURCE_DIR";
	const string cmd_set_output_dir = "SET_OUTPUT_DIR";
	const static int number_of_cmd = 2;
	const static int cmd_size[number_of_cmd];

	const string error1 = "Target ERROR1";
	const string error2 = "Target ERROR2";
	const string error3 = "Target ERROR3";
};