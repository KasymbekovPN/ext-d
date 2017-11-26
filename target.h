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
	void toConsole() const;
	void run() const;

private:
	string	m_name;
	string	m_path;
	bool	is_exist;
	string	m_source_dir;
	string	m_output_dir;
	int		m_error_status;

	const string cmd_set_source_dir = "SET_SOURCE_DIR";
	const string cmd_set_output_dir = "SET_OUTPUT_DIR";
	const static int number_of_cmd = 2;
	const static int cmd_size[number_of_cmd];

	const static int error_output_dir_invalid_param = 0b0001;
	const static int error_source_dir_invalid_param = 0b0010;
	const static int error_output_dir_no_exists		= 0b0100;
	const static int error_source_dir_no_exists		= 0b1000;
};