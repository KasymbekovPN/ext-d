#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <cstddef>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::size_t;
using std::map;

class FileTree
{
public:

	enum class FileTreeLang {
		unknow,
		c_lang
	};

	FileTree(const string&, int, const string&);
	~FileTree();

	void show() const;

private:

	string m_path;
	FileTreeLang m_lang;
	map<string, FileTreeLang> m_ll;
	map <FileTreeLang, vector<string>> m_lang_ext;
	int m_error_status;

	vector<string> m_files;
	vector<FileTree*> m_directory;

	static const int error_arg = 0b1;
	static const int error_unknow_lang = 0b10;

};
