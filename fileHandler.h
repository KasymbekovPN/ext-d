#pragma once

#include <string>
#include <fstream>
#include <iostream>
//#include <io.h>
#include <ios>

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

class FileHandler
{
public:
	FileHandler(const string& path_);
	~FileHandler();

	void clearFile() const;
	int getNumLine() const;
	bool rewriteLine(int, const string&);

	static bool fileExist(const string& path_);

private:

	string m_filePath;

};
