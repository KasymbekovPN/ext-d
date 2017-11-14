#include "target.h"

Target::Target(const string & name_, const string & path_, bool is_exist_): m_name(name_), m_path(path_), is_exist(is_exist_)
{
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
