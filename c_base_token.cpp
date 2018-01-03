#include "c_base_token.hpp"

cBaseToken::TokenTypeNames cBaseToken::tokenTypeNames = {
	{cBaseToken::TokenType::macro, "#define"},
	{cBaseToken::TokenType::typedef_enum, "enum"},
	{cBaseToken::TokenType::def_var, "var"},
	{cBaseToken::TokenType::typedef_struct, "struct"},
	{cBaseToken::TokenType::func_decl, "func-decl"},
	{cBaseToken::TokenType::func_def, "func-def"}
};

cBaseToken::cBaseToken(TokenType type_, const string& raw_): m_type(type_), m_raw(raw_) {}

void cBaseToken::show(int offset_) const
{
	cout << endl;
	cout << cBaseToken::get_offset_string(offset_) << "Token Type: " << tokenTypeNames[m_type] << endl;
	cout << cBaseToken::get_offset_string(offset_) << "Token Name: " << m_name << endl;
}

void cBaseToken::setName(const string & name_)
{
	m_name = StringHandler::filter(name_, StringHandler::FBE::begin_and_end, {' ', '\t', '\n'});
}

cBaseToken::TokenType cBaseToken::getType() const
{
	return m_type;
}

string cBaseToken::getName() const
{
	return m_name;
}

string cBaseToken::getRaw() const
{
	return m_raw;
}

string cBaseToken::get_offset_string(int offset_)
{

	string res;
	for (int i = 0; i < offset_; ++i) {
		res += '\t';
	}

	return res;
}
