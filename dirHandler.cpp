#include "dirHandler.hpp"

DirHandler::DirHandler(const string & path_, bool need_create_) : m_path(path_)
{

	vector<string> dirs_names = StringHandler::split(path_, '/');

	string path = dirs_names[0];

	for (auto iter = dirs_names.begin() + 1; iter != dirs_names.end(); iter++) {
		path += "//" + *iter;
		if (!std::experimental::filesystem::exists(path)) {
			std::experimental::filesystem::create_directory(path);
		}
	}

}

void DirHandler::create()
{
	//cout << m_path << " 123" << endl;
	//CreateDirectory(LPCTSTR(m_path.c_str()), NULL);
}

bool DirHandler::exists() const
{
	return m_dirExist;
}

void DirHandler::show() const
{
	cout << m_path << endl;
}
