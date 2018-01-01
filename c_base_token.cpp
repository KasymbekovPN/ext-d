#include "c_base_token.hpp"

cBaseToken::TokenTypeNames cBaseToken::tokenTypeNames = {
	{cBaseToken::TokenType::macro, "#define"},
	{cBaseToken::TokenType::typedef_enum, "enum"},
	{cBaseToken::TokenType::def_var, "var"},
	{cBaseToken::TokenType::typedef_struct, "struct"}
};

cBaseToken::cBaseToken(TokenType type_): m_type(type_){}

void cBaseToken::show() const
{
	cout << endl;
	cout << "Token Type: " << tokenTypeNames[m_type] << endl;
	cout << "Token Name: " << m_name << endl;
}

void cBaseToken::setName(const string & name_)
{
	m_name = name_;
}

cBaseToken::TokenType cBaseToken::getType() const
{
	return m_type;
}

string cBaseToken::getName() const
{
	return m_name;
}
