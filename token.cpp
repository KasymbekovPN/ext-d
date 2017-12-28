#include "token.hpp"

Token::TOKEN_TYPE_NAME Token::token_type_name = {
	{Token::c_lang_token_type::macro_define, "macro_def"},
	{Token::c_lang_token_type::function, "func"},
	{Token::c_lang_token_type::static_function, "static func"},
	{Token::c_lang_token_type::extern_var, "extern var"},
	{Token::c_lang_token_type::static_var, "static var"}
};

Token::Token(const string& token_value_, c_lang_token_type token_type_)
	: m_token_value(token_value_), m_token_type(token_type_)
{
}

string Token::getValue() const
{
	return string();
}

void Token::writeToken() const
{
}

void Token::writeTokenDescription() const
{
}

void Token::writeTokenAsHtml() const
{
}

void Token::show() const
{
	cout << endl;
	cout << "Token Type: " << token_type_name[m_token_type] << endl;
	cout << m_token_value << endl;
	cout << endl;
}
