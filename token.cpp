#include "token.hpp"

Token::TOKEN_TYPE_NAME Token::token_type_name = {
	{Token::c_lang_token_type::macro_define, "macro_def"},
	{Token::c_lang_token_type::function, "func"},
	{Token::c_lang_token_type::static_function, "static func"},
	{Token::c_lang_token_type::extern_var, "extern var"},
	{Token::c_lang_token_type::static_var, "static var"},
	{Token::c_lang_token_type::typedef_enum, "enum"},
	{Token::c_lang_token_type::typedef_struct, "struct"}
};

Token::Token(const string& token_value_, c_lang_token_type token_type_)
	: m_token_value(token_value_), m_token_type(token_type_)
{

	switch (m_token_type) {
		case c_lang_token_type::macro_define:
			macro_define_handler(m_token_value.substr(7));
			break;
		case c_lang_token_type::typedef_enum:
			enum_handler(m_token_value);
			break;
		case c_lang_token_type::typedef_struct:
			struct_handler(m_token_value);
			break;
		default:
			break;
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

void Token::enum_handler(const string & buffer)
{

	size_t start = buffer.find('{');
	size_t stop = buffer.find('}');

	if (string::npos != start && string::npos != stop && start < stop) {
		m_value = buffer.substr(start + 1, stop - start - 1);
		m_name = buffer.substr(stop + 1);
	}

	m_name = StringHandler::filter(m_name, StringHandler::FBE::begin_and_end, {' ', '\n', '\t', '\\'});
	m_value = StringHandler::filter(m_value, StringHandler::FBE::all, { ' ', '\n', '\t', '\\' });
}

void Token::struct_handler(const string & buffer)
{

//#define SH_1
#define SH_2

#ifdef  SH_2

	size_t found = buffer.find("struct");

	if (string::npos != found) {
		auto res = parse_struct(buffer.substr(found));
		m_name = res[0];
		m_value = res[1];
	}

#endif

#ifdef  SH_1
	size_t start = buffer.find('{');
	size_t stop = buffer.find('}');

	if (string::npos != start && string::npos != stop && start < stop) {
		m_value = buffer.substr(start + 1, stop - start - 1);
		m_name = buffer.substr(stop + 1);
	}

	m_name = StringHandler::filter(m_name, StringHandler::FBE::begin_and_end, { ' ', '\n', '\t', '\\' });

	auto res = StringHandler::split(m_value, ';');
	m_value.clear();
	int i = 0;

	for (auto line : res) {
		string buffer = StringHandler::filter(line, StringHandler::FBE::begin_and_end, { ' ', '\n', '\t', '\\' });
		if (!StringHandler::filter(buffer, StringHandler::FBE::all, { ' ', '\n', '\t', '\\' }).empty()) {
			m_value += buffer + ";";
		}
	}
#endif

}

vector<string> Token::parse_struct(const string & buffer)
{

	int brace_counter = 0;
	bool inner_struct = false;
	string name;
	string value;

	size_t found = buffer.find_last_of('}');
	if (string::npos != found) {
		name = StringHandler::filter(buffer.substr(found + 1), StringHandler::FBE::begin_and_end, { ' ', '\t', '\n', '\\' });
	}

	size_t start = buffer.find('{');

	if (string::npos != start) {
		string chank;


		for (size_t i = start + 1; i < found; ++i) {

			if ("struct" == buffer.substr(i, 6)) {
				inner_struct = true;
			}

			if (inner_struct) {
				if ('{' == buffer[i]) {
					brace_counter++;
				}

				if ('}' == buffer[i]) {
					brace_counter--;
				}

				if (';' == buffer[i] && 0 == brace_counter) {
					inner_struct = false;
				}
			}
			else {
				chank += buffer[i];
			}
		}

		cout << chank << endl;
	}



	return vector<string>({name, "test2"});
}
