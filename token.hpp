#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <map>

#include "stringHandler.h"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::shared_ptr;
using std::map;

class Token
{
public:

	enum class c_lang_token_type {
		macro_define,
		function,
		static_function,
		extern_var,
		static_var,
		typedef_enum,
		typedef_struct,
	};

	explicit Token(const string& token_value_, c_lang_token_type token_type_);

	string getName() const;
	string getValue() const;
	void writeToken() const;
	void writeTokenDescription() const;
	void writeTokenAsHtml() const;

	void show() const;

private:

	string m_token_value;
	c_lang_token_type m_token_type;

	typedef map<c_lang_token_type, string> TOKEN_TYPE_NAME;
	static TOKEN_TYPE_NAME token_type_name;

	string m_name;
	string m_value;

	//
	// todo: завязать через map
	//
	void macro_define_handler(const string& buffer);
	void enum_handler(const string& buffer);
	void struct_handler(const string& buffer);

	vector<string> parse_struct(const string& buffer);
};