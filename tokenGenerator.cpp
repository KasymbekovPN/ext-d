#include "tokenGenerator.hpp"

TokenGenerator::TokenGenerator(const string & path_)
{
	size_t found = path_.find_last_of('.');
	m_path = string::npos != found ? path_.substr(0, found) : "";

	m_was_header = "h" == path_.substr(found + 1);
	m_was_source = "c" == path_.substr(found + 1);
}

TokenGenerator::~TokenGenerator()
{
	for (auto item : m_tokens) {
		delete item;
	}
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

void TokenGenerator::parse(size_t offset_, const string & outdir_, vector<std::experimental::filesystem::path>* file_paths_)
{
	if (m_was_header) {
		parse_file(m_path + ".h");
	}

	if (m_was_source) {
		parse_file(m_path + ".c");
	}

	size_t token_idx = 0;

	cout << "Tokens are generated: " << StringHandler::filter<string, char>(m_path.substr(offset_), StringHandler::FBE::begin, { '\\' })
		<< ": " << token_idx << "/" << m_tokens.size();

	for (auto item : m_tokens) {
		string name;
		string pre_name = StringHandler::filter<string, char>(m_path.substr(offset_), StringHandler::FBE::begin, { '\\' });
		auto spl = StringHandler::split(pre_name, '\\');
		for (size_t i = 0; i < spl.size(); ++i) {
			name += spl[i] + "-";
		}

		name += item->getName();
		name = StringHandler::replace_all<string, char>(name, '(', '_');
		name = StringHandler::replace_all<string, char>(name, ')', '_');
		name = StringHandler::replace_all<string, char>(name, ',', '_');

		name += "-" + item->getHash() + ".ipynb";

		item->write(outdir_, name, "ipynb", file_paths_);
		
		cout << "\rTokens are generated: " << StringHandler::filter<string, char>(m_path.substr(offset_), StringHandler::FBE::begin, { '\\' })
			<< ": " << ++token_idx << "/" << m_tokens.size();
	}
	cout << endl;
}

void TokenGenerator::show()
{
	cout << endl;
	cout << m_path << endl;
	cout << "h : " << m_was_header << endl;
	cout << "c : " << m_was_source << endl;
	cout << endl;
}

void TokenGenerator::parse_file(const string & file_name)
{

	m_flags = 0;
	m_general_brace_counter = 0;
	m_struct_brace_counter = 0;
	m_func_brace_counter = 0;

	string chank;

	FileHandler file(file_name);
	string buffer = file.getAsString() + "\n";

	int block_comment_begin = 0;

	for (int i = 0; i < buffer.size(); ++i) {

		//
		// ������/����� �������� �����������
		//
		if (0 == (m_flags & m_flag_is_comment) && "/*" == buffer.substr(i, 2)) {
			m_flags |= m_flag_block_comment;
			block_comment_begin = i;
		}
		if ((m_flags & m_flag_block_comment) && i >= block_comment_begin + 2) {
			if ("*/" == buffer.substr(i - 2, 2)) {
				m_flags &= ~m_flag_block_comment;
			}
		}

		//
		// ������/����� ���������  �����������
		//
		if (0 == (m_flags & m_flag_is_comment) && "//" == buffer.substr(i, 2)) {
			m_flags |= m_flag_line_comment;
		}
		if ((m_flag_line_comment & m_flags) && '\n' == buffer[i]) {
			m_flags &= ~m_flag_line_comment;
		}


		if (0 == (m_flags & m_flag_is_comment)) {

			if (m_flag_empty == (m_flags & m_flag_rec)) {

				if ('#' == buffer[i]) {

					if ("#define" == buffer.substr(i, 7)) {
						//
						// ������ ����� "#define"
						//
						m_flags |= m_flag_prepro_define;
						chank.clear();
					}
					else {
						//
						// ������ ����� "#?????"
						//
						m_flags |= m_flag_prepro_except_define;
						chank.clear();
					}
				}
				else if (' ' != buffer[i] && '\n' != buffer[i] && '\t' != buffer[i]) {
					m_flags |= m_flag_general_rec;
					chank.clear();
				}
			}

			//
			// ������������ � general_rec �� general_brace
			//
			if (m_flags & m_flag_general_rec) {
				if ('(' == buffer[i]) {
					m_flags &= ~m_flag_general_rec;
					m_flags |= m_flag_general_brace;
				}
			}

			if (m_flags & m_flag_general_brace) {

				if ('(' == buffer[i]) {
					m_general_brace_counter++;
				}
				if (')' == buffer[i]) {
					m_general_brace_counter--;
				}

				if (0 == m_general_brace_counter) {

					if (' ' != buffer[i] && '\t' != buffer[i] && '\n' != buffer[i] && ')' != buffer[i]) {

						if (';' == buffer[i]) {
							m_flags &= ~m_flag_general_brace;
							if (string::npos == chank.find("typedef")) {
								m_tokens.push_back(new cFuncDecl(chank));
							}
							else {
								m_tokens.push_back(new cDefVar(chank));
							}	
						}
						else if ('{' == buffer[i]) {
							m_flags &= ~m_flag_general_brace;
							m_flags |= m_flag_func_definition;
						}
						else {
							m_flags &= ~m_flag_general_brace;
							m_flags |= m_flag_general_rec;
						}
					}
				}
			}

			if (m_flags & m_flag_func_definition) {

				if ('{' == buffer[i]) {
					m_func_brace_counter++;
				}
				if ('}' == buffer[i]) {
					m_func_brace_counter--;
				}

				if (0 == m_func_brace_counter) {
					m_flags &= ~m_flag_func_definition;
					m_tokens.push_back(new cFuncDef(chank));
				}

			}

			//
			// ������������ � general_rec �� struct_rec
			//
			if (m_flags & m_flag_general_rec) {
				if ("struct" == buffer.substr(i, 6)) {
					m_flags &= ~m_flag_general_rec;
					m_flags |= m_flag_struct_rec;
				}
			}

			//
			// ��������� ����� "struct"
			//
			if (m_flags & m_flag_struct_rec) {
				if ('{' == buffer[i]) {
					m_struct_brace_counter++;
				}
				if ('}' == buffer[i]) {
					m_struct_brace_counter--;
				}

				if (0 == m_struct_brace_counter && ';' == buffer[i]) {
					m_flags &= ~m_flag_struct_rec;

					size_t first_equal_sign = chank.find_first_of('=');
					size_t first_brack = chank.find_first_of('{');

					if (string::npos != first_brack && string::npos == first_equal_sign) {
						m_tokens.push_back(new cStructToken(chank));
					}
					else if ((string::npos == first_brack && string::npos == first_equal_sign) ||
						(string::npos != first_brack && string::npos != first_equal_sign && first_equal_sign < first_brack))
					{
						m_tokens.push_back(new cDefVar(chank));
					}
				}
			}

			//
			// ��������� ����� "#define"
			//
			if (m_flag_prepro_define & m_flags) {

				if ('\\' == buffer[i]) {
					m_flags |= m_flag_prepro_def_hold;
				}
				else {
					if ((m_flags & m_flag_prepro_def_hold) && (' ' != buffer[i] && '\t' != buffer[i] && '\n' != buffer[i])) {
						m_flags &= ~m_flag_prepro_def_hold;
					}
				}

				if (0 == (m_flags & m_flag_prepro_def_hold) && '\n' == buffer[i]) {
					m_flags &= ~m_flag_prepro_define;
					m_tokens.push_back(new cMacroToken(chank));
				}
			}

			//
			// �������� ����� "#??????"
			//
			if (m_flags & m_flag_prepro_except_define) {
				if ('\n' == buffer[i]) {
					m_flags &= ~m_flag_prepro_except_define;
				}
			}

			//
			// ��������� ����� general_rec
			//
			if (m_flags & m_flag_general_rec) {
				if (';' == buffer[i]) {
					m_flags &= ~m_flag_general_rec;
					parse_general(chank);
				}
			}

			//
			// ������ �����
			//
			if (m_flag_rec & m_flags) {
				chank += buffer[i];
			}

		}

	}
}

void TokenGenerator::parse_general(const string & buffer)
{

	if (string::npos != buffer.find("enum")) {
		m_tokens.push_back(new cEnumToken(buffer));
	}
	else {
		m_tokens.push_back(new cDefVar(buffer));
	}	
}

