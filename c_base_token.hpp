#pragma once

#include <iostream>
#include <string>
#include <map>

#include "stringHandler.h"

using std::string;
using std::cout;
using std::endl;
using std::map;

class cBaseToken
{
public:

	enum class TokenType {
		macro,
		typedef_enum,
		def_var,
		typedef_struct,
		func_decl,
		func_def,
	};

	cBaseToken(TokenType type_, const string& raw_);

	virtual void show(int offset_) const;

	void setName(const string& name_);

	TokenType getType() const;
	string getName() const;
	string getRaw() const;

	static string get_offset_string(int offset_);

private:

	typedef map<TokenType, string> TokenTypeNames;
	static TokenTypeNames tokenTypeNames;

	string m_name;
	TokenType m_type;
	string m_raw;
};