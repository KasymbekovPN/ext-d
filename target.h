#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <memory>
#include <algorithm>
#include <chrono>
#include <locale>
#include <codecvt>
#include <set>
#include <map>
#include <functional>

#include "config.h"
#include "fileHandler.h"
#include "stringHandler.h"
#include "fileTree.h"
#include "errorStatus.h"
#include "tokenGenerator.hpp"
#include "jsonObject.hpp"
#include "wfileHandler.hpp"
#include "parted_line.hpp"
#include "token_path.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::wstring;
using std::map;

class Target
{
public:

	Target(const wstring&, const wstring&, std::shared_ptr<ErrorStatus>);
	~Target();

	wstring getWName() const;
	string getName() const;
	void toConsole() const;
	void run(const string& flag_) const;

private:
    wstring	m_name;
	string	m_path;
	string	m_source_dir;
	string	m_output_dir;
	string  m_tokens_output;
#ifdef  TASK_0_3_6__1
	string  m_relative_tokens_output;
#endif
	string  m_tokens_list_file_path;
	string  m_user_output;
	std::shared_ptr<ErrorStatus> p_error;

	FileTree* m_fileTree;	

	map < string, std::function<void()>> flag_handlers;

	void flag_d_handler();
	void flag_m_handler();
};