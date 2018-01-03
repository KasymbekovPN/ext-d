#include "c_struct_token.hpp"

cStructToken::cStructToken(const string & buffer): cBaseToken(cBaseToken::TokenType::typedef_struct, buffer)
{
	size_t found_header = buffer.find_first_of('{');
	size_t found_footer = buffer.find_last_of('}');

	string header = StringHandler::filter(buffer.substr(0, found_header), StringHandler::FBE::begin_and_end, {' ', '\t', '\n'});
	string inner = StringHandler::filter(buffer.substr(found_header + 1, found_footer - found_header - 1), StringHandler::FBE::begin_and_end, { ' ', '\t', '\n' });
	string footer = StringHandler::filter(buffer.substr(found_footer + 1), StringHandler::FBE::begin_and_end, { ' ', '\t', '\n' });

	m_typedef = string::npos != header.find("typedef");
	m_volatile = string::npos != header.find("volatile");
	m_static = string::npos != header.find("static");

	size_t found_arr_begin = footer.find_first_of('[');
	size_t found_arr_end = footer.find_last_of(']');
	if (string::npos != found_arr_begin && string::npos != found_arr_end && found_arr_end > found_arr_begin) {
		m_array = true;
		setName(footer.substr(0, found_arr_begin));
		m_array_size = StringHandler::filter(
			footer.substr(found_arr_begin + 1, found_arr_end - found_arr_begin - 1), 
			StringHandler::FBE::begin_and_end,
			{' ', '\t', '\n'}
		);
	}
	else {
		m_array = false;
		setName(footer);
	}

	int inner_brace_counter = 0;
	bool inner_struct = false;
	string chank;

	for (auto ch : inner) {

		if (!inner_struct) {
			if (';' == ch) {
				m_value.push_back(new cDefVar(chank));
				chank.clear();
				continue;
			}
		}
		else {
			if (';' == ch && 0 == inner_brace_counter) {
				m_value.push_back(new cStructToken(chank));
				chank.clear();
				continue;
			}
		}

		if ('{' == ch){
			inner_struct = true;
			inner_brace_counter++;
		}

		if ('}' == ch) {
			inner_brace_counter--;
		}

		chank += ch;
	}
}

cStructToken::~cStructToken()
{
	for (auto iter : m_value) {
		delete iter;
	}
}

void cStructToken::show(int offset_) const
{
	cBaseToken::show(offset_);
	cout << cBaseToken::get_offset_string(offset_) << "is typedef : " << m_typedef << endl;
	cout << cBaseToken::get_offset_string(offset_) << "is volatile : " << m_volatile << endl;
	cout << cBaseToken::get_offset_string(offset_) << "is static : " << m_static << endl;
	cout << cBaseToken::get_offset_string(offset_) << "is array : " << m_array << endl;
	cout << cBaseToken::get_offset_string(offset_) << "array size : " << m_array_size << endl;

	for (auto i : m_value) {
		i->show(offset_ + 1);
	}

}
