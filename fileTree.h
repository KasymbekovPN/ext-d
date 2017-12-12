#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <cstddef>
#include <map>
#include <memory>
#include <iterator>

#include "errorStatus.h"

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

	FileTree(const string&, std::shared_ptr<ErrorStatus>, const string&);
	~FileTree();

	void filePaths(std::shared_ptr<vector<string>>, bool);

private:

	string m_path;
	FileTreeLang m_lang;
	map<string, FileTreeLang> m_ll;
	map <FileTreeLang, vector<string>> m_lang_ext;
	std::shared_ptr<ErrorStatus> p_error;

	vector<string> m_files;
	vector<FileTree*> m_directory;

};
