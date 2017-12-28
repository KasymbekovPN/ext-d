#include "tokenGenerator.hpp"

TokenGenerator::TokenGenerator(const string & path_)
{
	size_t found = path_.find_last_of('.');
	m_path = string::npos != found ? path_.substr(0, found) : "";

	m_was_header = "h" == path_.substr(found + 1);
	m_was_source = "c" == path_.substr(found + 1);
}

bool TokenGenerator::equal(const string & path_)
{
	bool res = false;

	size_t found = path_.find_last_of('.');
	if (string::npos != found) {

		string path = path_.substr(0, found);
		string ext = path_.substr(found + 1);

		if (m_path == path) {

			if ("h" == ext) {
				m_was_header = true;
			}
			else if ("c" == ext) {
				m_was_source = true;
			}

			res = true;

		}		
	}

	return res;
}

void TokenGenerator::parse()
{
	//cout << "parse " << m_path << endl;

	//
	// Обработка h-файла
	//
	FileHandler h_file(m_path + ".h");
	string h_string = h_file.getAsString();

	vector<Token*> h_tokens;

	string buffer;
	bool flag_macro_define = false;
	bool flag_macro_no_stop = false;
	bool flag_line_comment = false;
	bool flag_block_comment = false;
	bool flag_typedef = false;
	bool flag_enum = false;

	for (int i = 0; i < h_string.size(); ++i) {

		if (!flag_macro_define && !flag_line_comment && !flag_block_comment && "typedef" == h_string.substr(i, 7)) {
			flag_typedef = true;
			buffer.clear();
		}
		if ("enum" == h_string.substr(i, 4) && flag_typedef) {
			flag_typedef = false;
			flag_enum = true;
		}
		if (';' == h_string[i] && flag_enum) {
			flag_enum = false;
			h_tokens.push_back(new Token(buffer, Token::c_lang_token_type::typedef_enum));
		}

		//
		// Начало записи токена "#define"
		//
		if (!flag_line_comment && !flag_block_comment && !flag_typedef && \
			!flag_enum && "#define" == h_string.substr(i, 7)) 
		{
			flag_macro_define = true;
			buffer.clear();
		}

		//
		// Определение начала и конца участка однострочного коментария
		//
		if ("//" == h_string.substr(i, 2)) {
			flag_line_comment = true;
		}
		if (flag_line_comment && '\n' == h_string[i]) {
			flag_line_comment = false;
		}

		//
		// Определение начала и конца участка блочного комментария
		//
		if ("/*" == h_string.substr(i, 2)) {
			flag_block_comment = true;
		}
		if (flag_block_comment && "*/" == h_string.substr(i, 2)) {
			flag_block_comment = false;
		}

		//
		// Конец записи токена "#define"
		//
		if (flag_macro_define) {


			if ('\\' == h_string[i]) {
				flag_macro_no_stop = true;
			}
			else if (flag_macro_no_stop && (' ' != h_string[i] && '\t' != h_string[i] && '\n' != h_string[i])) {
				flag_macro_no_stop = false;
			}
			
			if (!flag_macro_no_stop && '\n' == h_string[i]) {
				h_tokens.push_back(new Token(buffer, Token::c_lang_token_type::macro_define));
				flag_macro_define = false;
			}
		}

		if (!flag_line_comment && !flag_block_comment && \
			(flag_macro_define || flag_typedef || flag_enum))
		{
			buffer += h_string[i];
		}
	}

	for (auto p_token : h_tokens) {
		p_token->show();
	}

	for (auto p_token : h_tokens) {
		delete p_token;
	}
}

void TokenGenerator::show()
{
	cout << endl;
	cout << m_path << endl;
	cout << "h : " << m_was_header << endl;
	cout << "c : " << m_was_source << endl;
	cout << endl;
}

