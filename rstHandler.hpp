#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <array>
#include <filesystem>

#include "fileHandler.h"
#include "dom.hpp"

using std::string;
using std::vector;
using std::map;
using std::cout;
using std::endl;
using std::array;

class RstHandler
{
public:

	enum class cmd {
		state, version, token_type, paragraph, func_ret, code_block, func_param, struct_member, enum_member, nav
	};

	RstHandler(const string& file_name_, const string& out_);
	RstHandler(const string& short_file_name_, const string& out_, const string& content_);

	void write2html() const;

private:

	typedef std::map<cmd, string> CMD_NAMES;
	static CMD_NAMES cmd_names;

	string m_file;
	string m_out_dir;
	string m_short_file_name;

	std::experimental::filesystem::path m_file_path;

	bool m_state;
	string m_type;
	string m_version;

	vector<array<string, 3>> m_chanks;

	void handler();

};