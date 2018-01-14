#pragma once

#include "stringHandler.h"
#include "fileHandler.h"
#include "dom.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <map>
#include <codecvt>
#include <locale>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::pair;
using std::array;

class TokenHandler
{
public:

	enum class cmd{
		state, version, token_type, paragraph, func_ret, code_block, func_param, struct_member, enum_member 
	};

	TokenHandler(std::experimental::filesystem::path file_name_);

	void write(const string& out_dir);

private:

	bool m_state;
	string m_version;
	string m_type;
	std::experimental::filesystem::path m_shortName;

	vector<array<string, 3>> m_chanks;

	typedef std::map<cmd, string> CMD_NAMES;
	static CMD_NAMES cmd_names;
};
