#pragma once

#include <iostream>
#include <string>
#include <map>

#include "stringHandler.h"
#include "config.h"

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

	void setStatic(bool value_);
	void setConst(bool value_);
	void setVolatile(bool value_);
	void setExtern(bool value_);

	bool isStatic() const;
	bool isConst() const;
	bool isVolatile() const;
	bool isExtern() const;

	static string get_offset_string(int offset_);

private:

	typedef map<TokenType, string> TokenTypeNames;
	static TokenTypeNames tokenTypeNames;

	TokenType m_type;

	string m_name;	
	string m_raw;

	bool m_static;
	bool m_const;
	bool m_volatile;
	bool m_extern;
};