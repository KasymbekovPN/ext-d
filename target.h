#pragma once

#include <string>

using std::string;

class Target
{
public:
	Target(const string&, const string&, bool);

	string getName() const;
	string getPath() const;
	bool isExist() const;

private:
	string	m_name;
	string	m_path;
	bool	is_exist;
};