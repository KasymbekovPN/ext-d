#pragma once

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

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
	bool	is_valid;
};