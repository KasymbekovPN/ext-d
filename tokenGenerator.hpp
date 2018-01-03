#pragma once

#include "fileHandler.h"
#include "token.hpp"
#include "c_base_token.hpp"
#include "c_macro_token.hpp"
#include "c_enum_token.hpp"
#include "c_struct_token.hpp"
#include "c_def_var_token.hpp"
#include "c_func_decl.hpp"
#include "c_func_def.hpp"

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class TokenGenerator
{
public:
	TokenGenerator(const string& path_);
	~TokenGenerator();

	bool equal(const string& path_);
	void parse();

	void show();

private:

	string m_module_name;
	string m_path;
	bool m_was_source;
	bool m_was_header;

	const unsigned int m_flag_empty = 0;

	const unsigned int m_flag_block_comment			= 0b000000001;
	const unsigned int m_flag_line_comment			= 0b000000010;
	const unsigned int m_flag_is_comment			= 0b000000011;
	const unsigned int m_flag_prepro_except_define	= 0b000000100;
	const unsigned int m_flag_prepro_define			= 0b000001000;
	const unsigned int m_flag_general_rec			= 0b000010000;
	const unsigned int m_flag_func_definition		= 0b000100000;
	const unsigned int m_flag_struct_rec			= 0b001000000;
	const unsigned int m_flag_general_brace			= 0b010000000;
	const unsigned int m_flag_prepro_def_hold		= 0b100000000;

	const unsigned int m_flag_rec					= 0b011111100;

	unsigned int m_flags;

	int m_struct_brace_counter;
	int m_general_brace_counter;
	int m_func_brace_counter;

	vector<cBaseToken*> m_tokens;

	void parse_file(const string& file_name);
	void parse_general(const string& buffer);


};