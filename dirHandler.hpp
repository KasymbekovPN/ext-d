#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <filesystem>

#include "stringHandler.h"

using std::cout;
using std::endl;
using std::string;

class DirHandler
{
public:
	DirHandler(const string& path_, bool need_create_);

	void create();
	bool exists() const;
	void show() const;

private:

	string m_path;
	bool m_dirExist;
};