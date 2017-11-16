#include "fileHandler.h"

FileHandler::FileHandler(const string & path_): m_path(path_)
{

	ifstream fin(m_path, std::ios::in | std::ios::_Nocreate);
	m_file_exist = !fin.fail();

	if (!m_file_exist) {
		fin.close();
		return;
	}

	char ch = fin.get();
	while (ch != EOF) {
		m_ss << ch;
		ch = fin.get();
	}
	fin.close();

	m_file = m_ss.str();

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

char FileHandler::get()
{
	return m_ss.get();
}
