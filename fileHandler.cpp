#include "fileHandler.h"

FileHandler::FileHandler(const string & path_): m_path(path_)
{

	ifstream fin(m_path, std::ios::in | std::ios::_Nocreate);
	m_file_exist = !fin.fail();

	if (!m_file_exist) {
		fin.close();
		return;
	}

	char ch;
	while (fin.get(ch)) {
		m_ss << ch;
	}

	m_file = m_ss.str();

	fin.close();
}

FileHandler::~FileHandler()
{
}

const string & FileHandler::getAsString() const
{
	return m_file;
}

bool FileHandler::isExist() const
{
	return m_file_exist;
}
