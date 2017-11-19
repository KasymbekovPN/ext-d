#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "fileHandler.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;


class Target
{
public:
	Target(const string&);

	string getName() const;
	string getPath() const;
	bool isExist() const;

private:
	string	m_name;
	string	m_path;
	bool	is_exist;

	const string error1 = "Target ERROR1";
};