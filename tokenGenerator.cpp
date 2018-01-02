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

#define TG_PARSE_3
//#define TG_PARSE_2
//#define TG_PARSE_1

#ifdef  TG_PARSE_3

	//FileHandler h_file(m_path + ".h");
	//string h_string = h_file.getAsString();

	FileHandler c_file(m_path + ".c");
	string c_string = c_file.getAsString() + "\n";

	unsigned int flags = 0;
	const unsigned int flag_empty = 0;
	const unsigned int flag_block_comment			= 0b000000001;
	const unsigned int flag_line_comment			= 0b000000010;
	const unsigned int flag_is_comment				= 0b000000011;
	const unsigned int flag_prepro_except_define	= 0b000000100;
	const unsigned int flag_prepro_define			= 0b000001000;
	const unsigned int flag_general_rec				= 0b000010000;
	const unsigned int flag_func_definition			= 0b000100000;
	const unsigned int flag_struct_rec				= 0b001000000;
	const unsigned int flag_general_brace			= 0b010000000;
	const unsigned int flag_prepro_def_hold			= 0b100000000;

	const unsigned int flag_rec						= 0b011111100;

	int struct_brace_counter = 0;
	int general_brace_counter = 0;
	int func_brace_counter = 0;

	string chank;

	for (int i = 0; i < c_string.size(); ++i) {

		//
		// Начало/конец блочного комментария
		//
		if ("/*" == c_string.substr(i, 2)) {
			flags |= flag_block_comment;
		}
		if (flags & flag_block_comment) {
			if ("*/" == c_string.substr(i-2, 2)) {
				flags &= ~flag_block_comment;
			}
		}

		//
		// Начало/конец строчного  комментария
		//
		if ("//" == c_string.substr(i, 2)) {
			flags |= flag_line_comment;
		}
		if ((flag_line_comment & flags) && '\n' == c_string[i]) {
			flags &= ~flag_line_comment;
		}
		

		if (0 == (flags & flag_is_comment)) {

			if (flag_empty == (flags & flag_rec)) {

				if ('#' == c_string[i]) {

					if ("#define" == c_string.substr(i, 7)) {
						//
						// Начало куска "#define"
						//
						flags |= flag_prepro_define;
						chank.clear();
					}
					else {
						//
						// Начало куска "#?????"
						//
						flags |= flag_prepro_except_define;
						chank.clear();
					}
				}
				else if (' ' != c_string[i] && '\n' != c_string[i] && '\t' != c_string[i]){
					flags |= flag_general_rec;
					chank.clear();
				}
			}

			//
			// Переключение с general_rec на general_brace
			//
			if (flags & flag_general_rec) {
				if ('(' == c_string[i]) {
					flags &= ~flag_general_rec;
					flags |= flag_general_brace;
				}
			}

			if (flags & flag_general_brace) {

				if ('(' == c_string[i]) {
					general_brace_counter++;
				}
				if (')' == c_string[i]) {
					general_brace_counter--;
				}

				if (0 == general_brace_counter) {

					if (' ' != c_string[i] && '\t' != c_string[i] && '\n' != c_string[i] && ')' != c_string[i]) {

						if (';' == c_string[i]) {
							flags &= ~flag_general_brace;
							//---
							cout << "---Func-proto---" << endl;
							cout << chank << endl;
							cout << "---" << endl;
							//---
						}
						else if ('{' == c_string[i]) {
							flags &= ~flag_general_brace;
							flags |= flag_func_definition;
						}
						else {
							flags &= ~flag_general_brace;
							flags |= flag_general_rec;
						}
					}
				}
				
			}

			if (flags & flag_func_definition) {

				if ('{' == c_string[i]) {
					func_brace_counter++;
				}
				if ('}' == c_string[i]) {
					func_brace_counter--;
				}

				if (0 == func_brace_counter) {
					flags &= ~flag_func_definition;
					//---
					cout << "---Func-defin---" << endl;
					cout << chank + "\n}" << endl;
					cout << "---" << endl;
					//---
				}

			}

			//
			// Переключение с general_rec на struct_rec
			//
			if (flags & flag_general_rec) {
				if ("struct" == c_string.substr(i, 6)) {
					flags &= ~flag_general_rec;
					flags |= flag_struct_rec;
				}
			}

			//
			// Окончание куска "struct"
			//
			if (flags & flag_struct_rec) {
				if ('{' == c_string[i]) {
					struct_brace_counter++;
				}
				if ('}' == c_string[i]) {
					struct_brace_counter--;
				}

				if (0 == struct_brace_counter && ';' == c_string[i]) {
					flags &= ~flag_struct_rec;
					//---
					cout << "---struct---" << endl;
					cout << chank << endl;
					cout << "---" << endl;
					//---
				}

			}

			//
			// Окончание куска "#define"
			//
			if (flag_prepro_define & flags) {

				if ('\\' == c_string[i]) {
					flags |= flag_prepro_def_hold;
				}
				else {
					if ((flags & flag_prepro_def_hold) && (' ' != c_string[i] && '\t' != c_string[i] && '\n' != c_string[i])) {
						flags &= ~flag_prepro_def_hold;
					}
				}

				if (0 == (flags & flag_prepro_def_hold) && '\n' == c_string[i]) {
					flags &= ~flag_prepro_define;
					//---
					cout << "---define---" << endl;
					cout << chank << endl;
					cout << "---" << endl;
					//---
				}
			}

			//
			// Окочание куска "#??????"
			//
			if (flags & flag_prepro_except_define) {
				if ('\n' == c_string[i]) {
					flags &= ~flag_prepro_except_define;
				}
			}

			//
			// Окончание куска general_rec
			//
			if (flags & flag_general_rec) {
				if (';' == c_string[i]) {
					flags &= ~flag_general_rec;
					//---
					cout << "---general---" << endl;
					cout << chank << endl;
					cout << "---" << endl;
					//---
				}
			}

			//
			// Запись куска
			//
			if (flag_rec & flags) {
				chank += c_string[i];
			}

		}

	}

	cout << endl;

#endif//TG_PARSE_3

#ifdef  TG_PARSE_2

//
// Обработка h-файла
//
	FileHandler h_file(m_path + ".h");
	string h_string = h_file.getAsString();

	vector<cBaseToken*> h_tokens;

	string buffer;
	bool flag_macro_define = false;
	bool flag_macro_no_stop = false;
	bool flag_line_comment = false;
	bool flag_block_comment = false;
	bool flag_typedef = false;
	bool flag_enum = false;
	bool flag_struct = false;
	bool flag_struct_end = false;
	int counter_struct_brace = 0;

	for (int i = 0; i < h_string.size(); ++i) {

		if (!flag_macro_define && !flag_line_comment && !flag_block_comment && "typedef" == h_string.substr(i, 7)) {
			flag_typedef = true;
			buffer.clear();
		}
		if ("enum" == h_string.substr(i, 4) && flag_typedef) {
			flag_typedef = false;
			flag_enum = true;
		}

		if ("struct" == h_string.substr(i, 6) && flag_typedef) {
			flag_typedef = false;
			flag_struct = true;
			flag_struct_end = false;
		}

		if (flag_struct) {
			if ('{' == h_string[i]) {
				counter_struct_brace++;
			}
			if ('}' == h_string[i]) {
				counter_struct_brace--;
			}
		}

		if (';' == h_string[i] && flag_enum) {
			flag_enum = false;
			h_tokens.push_back(new cEnumToken(buffer));
		}

		if (flag_struct) {
			if ('}' == h_string[i] && 0 == counter_struct_brace) {
				flag_struct_end = true;
			}

			if (flag_struct_end && ';' == h_string[i]) {
				flag_struct = false;
				flag_struct_end = false;
				//h_tokens.push_back(new Token(buffer, Token::c_lang_token_type::typedef_struct));
				h_tokens.push_back(new cStructToken(buffer));
			}
		}

		//
		// Начало записи токена "#define"
		//
		if (!flag_line_comment && !flag_block_comment && !flag_typedef && \
			!flag_enum && !flag_struct && "#define" == h_string.substr(i, 7))
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
				h_tokens.push_back(new cMacroToken(buffer));
				flag_macro_define = false;
			}
		}

		if (!flag_line_comment && !flag_block_comment && \
			(flag_macro_define || flag_typedef || flag_enum || flag_struct))
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

#endif//TG_PARSE_2

#ifdef  TG_PARSE_1
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
	bool flag_struct = false;
	bool flag_struct_end = false;
	int counter_struct_brace = 0;

	for (int i = 0; i < h_string.size(); ++i) {

		if (!flag_macro_define && !flag_line_comment && !flag_block_comment && "typedef" == h_string.substr(i, 7)) {
			flag_typedef = true;
			buffer.clear();
		}
		if ("enum" == h_string.substr(i, 4) && flag_typedef) {
			flag_typedef = false;
			flag_enum = true;
		}

		if ("struct" == h_string.substr(i, 6) && flag_typedef) {
			flag_typedef = false;
			flag_struct = true;
			flag_struct_end = false;
		}

		if (flag_struct) {
			if ('{' == h_string[i]) {
				counter_struct_brace++;
			}
			if ('}' == h_string[i]) {
				counter_struct_brace--;
			}
		}

		if (';' == h_string[i] && flag_enum) {
			flag_enum = false;
			h_tokens.push_back(new Token(buffer, Token::c_lang_token_type::typedef_enum));
		}

		if (flag_struct) {
			if ('}' == h_string[i] && 0 == counter_struct_brace) {
				flag_struct_end = true;
			}

			if (flag_struct_end && ';' == h_string[i]) {
				flag_struct = false;
				flag_struct_end = false;
				h_tokens.push_back(new Token(buffer, Token::c_lang_token_type::typedef_struct));
			}
		}


		//if (';' == h_string[i] && flag_struct) {
		//	flag_struct = false;
		//	h_tokens.push_back(new Token(buffer, Token::c_lang_token_type::typedef_struct));
		//}

		//
		// Начало записи токена "#define"
		//
		if (!flag_line_comment && !flag_block_comment && !flag_typedef && \
			!flag_enum && !flag_struct && "#define" == h_string.substr(i, 7))
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
			(flag_macro_define || flag_typedef || flag_enum || flag_struct))
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
#endif//TG_PARSE_1

}

void TokenGenerator::show()
{
	cout << endl;
	cout << m_path << endl;
	cout << "h : " << m_was_header << endl;
	cout << "c : " << m_was_source << endl;
	cout << endl;
}

