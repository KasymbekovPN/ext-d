#include "target.h"

Target::Target(const string & str_)
{
	cout << str_ << endl;
}

string Target::getName() const
{
	return m_name;
}

string Target::getPath() const
{
	return m_path;
}

bool Target::isExist() const
{
	return is_exist;
}
