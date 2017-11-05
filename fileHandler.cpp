#include "fileHandler.h"

FileHandler::FileHandler(const string& filePath_): m_filePath(filePath_)
{

	if (FileHandler::fileExist(m_filePath)) {
		return;
	}

	ofstream fout_(m_filePath);
	fout_.close();

}

FileHandler::~FileHandler()
{
}

void FileHandler::clearFile() const
{
	ofstream fout_(m_filePath, std::ios_base::out | std::ios_base::trunc);
	fout_.close();
}

int FileHandler::getNumLine() const
{
	return 0;
}

bool FileHandler::rewriteLine(int, const string &)
{
	return false;
}

bool FileHandler::fileExist(const string& path_)
{
	ifstream fin_(path_, std::ios::in | std::ios::_Nocreate);
	bool exist_ = !fin_.fail();
	fin_.close();

	return exist_;
}
