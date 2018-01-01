#pragma once

#include "fileHandler.h"
#include "token.hpp"
#include "c_base_token.hpp"
#include "c_macro_token.hpp"
#include "c_enum_token.hpp"
#include "c_struct_token.hpp"
#include "c_def_var_token.hpp"

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class TokenGenerator
{
public:
	TokenGenerator(const string& path_);

	bool equal(const string& path_);
	void parse();

	void show();

private:

	string m_module_name;
	string m_path;
	bool m_was_source;
	bool m_was_header;
};