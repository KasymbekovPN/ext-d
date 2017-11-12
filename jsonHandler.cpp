#include "jsonHandler.h"

JsonHandler::JsonHandler(const string & path_): m_path(path_)
{
}

JsonHandler::~JsonHandler()
{
}

bool JsonHandler::exist()
{
	ifstream fin(m_path, std::ios::in | std::ios::_Nocreate);
	bool exist = !fin.fail();
	fin.close();

	return exist;
}
