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

#include "config.h"
#include "fileHandler.h"
#include "stringHandler.h"
#include "fileTree.h"
#include "errorStatus.h"
#include "dom.hpp"
#include "tokenGenerator.hpp"
#include "tokenHandler.hpp"
#include "rstHandler.hpp"
#include "jsonObject.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::wstring;

class Target
{
public:
	Target(const wstring&, const wstring&, std::shared_ptr<ErrorStatus>);
	~Target();

	wstring getWName() const;
	string getName() const;
	string getPath() const;
	bool isExist() const;
	void toConsole() const;
	void run(const string& flag_) const;

private:
	wstring	m_name;
	string	m_path;
	bool	is_exist;
	string	m_source_dir;
	string	m_output_dir;
	string  m_tokens_output;
	std::shared_ptr<ErrorStatus> p_error;

	FileTree* m_fileTree;

	const string tgt_flg_d = "-d";
	const string tgt_flg_m = "-m";
	const string cmd_set_source_dir = "SET_SOURCE_DIR";
	const string cmd_set_output_dir = "SET_OUTPUT_DIR";
	const string cmd_set_lang = "SET_LANG";
	const static int number_of_cmd = 2;
	const static int cmd_size[number_of_cmd];

	void make_source_out(std::shared_ptr<vector<string>> res) const;
	void make_token_generators(std::shared_ptr<vector<string>> res) const;
	void make_source_token_out() const;
	void make_functional_page() const;
	void make_tokens_page() const;
	void make_sources_page() const;
	void make_main_out() const;
};