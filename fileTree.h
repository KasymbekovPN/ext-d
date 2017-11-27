#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class FileTree
{
public:
	 FileTree(const string&, int);
	~ FileTree();

	void show() const;

private:

	string m_path;
	int m_error_status;

	vector<string> m_files;
	vector<FileTree*> m_directory;

	static const int error_arg = 0b1;

};
