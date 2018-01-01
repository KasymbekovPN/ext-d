#pragma once

#include <iostream>
#include <string>
#include <map>

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
	};

	cBaseToken(TokenType type_);

	virtual void show() const;

	void setName(const string& name_);

	TokenType getType() const;
	string getName() const;

private:

	typedef map<TokenType, string> TokenTypeNames;
	static TokenTypeNames tokenTypeNames;

	string m_name;
	TokenType m_type;
};