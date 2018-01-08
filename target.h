#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <memory>
#include <algorithm>
#include <chrono>

#include "fileHandler.h"
#include "stringHandler.h"
#include "fileTree.h"
#include "errorStatus.h"
#include "dom.hpp"
#include "tokenGenerator.hpp"

using std::string;
using std::cout;
using std::endl;
using std::vector;

class Target
{
public:
	Target(const string&, const string&, std::shared_ptr<ErrorStatus>);
	~Target();

	string getName() const;
	string getPath() const;
	bool isExist() const;
	void toConsole() const;
	void run(const string& flag_) const;

private:
	string	m_name;
	string	m_path;
	bool	is_exist;
	string	m_source_dir;
	string	m_output_dir;
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
};