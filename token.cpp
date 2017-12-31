#include "token.hpp"

Token::TOKEN_TYPE_NAME Token::token_type_name = {
	{Token::c_lang_token_type::macro_define, "macro_def"},
	{Token::c_lang_token_type::function, "func"},
	{Token::c_lang_token_type::static_function, "static func"},
	{Token::c_lang_token_type::extern_var, "extern var"},
	{Token::c_lang_token_type::static_var, "static var"},
	{Token::c_lang_token_type::typedef_enum, "enum"}
};

Token::Token(const string& token_value_, c_lang_token_type token_type_)
	: m_token_value(token_value_), m_token_type(token_type_)
{

	if (c_lang_token_type::macro_define == m_token_type) {
		macro_define_handler(m_token_value.substr(7));
	}
}

string Token::getName() const
{
	return m_name;
}

string Token::getValue() const
{
	return m_value;
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
	cout << "Token Type: " << token_type_name[m_token_type] << endl;
	cout << "Token Name: " << m_name << endl;
	cout << "Token value:" << endl << m_value << endl;
	cout << endl;
}

void Token::macro_define_handler(const string & buffer)
{

	bool rec_name = true;
	bool parenthesis = false;
	bool rec_value = false;

	m_name.clear();
	m_value.clear();

	string line = StringHandler::filter(buffer, StringHandler::FBE::begin_and_end, {' ', '\t'});

	for (auto ch : line) {

		if (rec_name) {
			m_name += ch;
		}

		if (rec_name) {
			if ('(' == ch) {
				parenthesis = true;
			}

			if (parenthesis) {
				if (')' == ch) {
					parenthesis = false;
				}
			}
		}

		if (rec_name && !parenthesis) {
			if (' ' == ch || '\t' == ch) {
				rec_name = false;
				rec_value = true;
			}
		}

		if (rec_value) {
			m_value += ch;
		}

	}

	m_name = StringHandler::filter(m_name, StringHandler::FBE::begin_and_end, {' ', '\n', '\t', '\\'});
	m_value = StringHandler::filter(m_value, StringHandler::FBE::all, {'\\', '\n', ' ', '\t'});
}
