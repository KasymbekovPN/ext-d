#include "c_struct_token.hpp"

cStructToken::cStructToken(const string & buffer): cBaseToken(cBaseToken::TokenType::typedef_struct, buffer)
{

	m_typedef = false;
	m_array = false;

	size_t found_header = buffer.find_first_of('{');
	size_t found_footer = buffer.find_last_of('}');

	string header = StringHandler::filter(buffer.substr(0, found_header), StringHandler::FBE::begin_and_end, { ' ', '\t', '\n' });
	string inner = StringHandler::filter(buffer.substr(found_header + 1, found_footer - found_header - 1), StringHandler::FBE::begin_and_end, { ' ', '\t', '\n' });
	string footer = StringHandler::filter(buffer.substr(found_footer + 1), StringHandler::FBE::begin_and_end, { ' ', '\t', '\n' });

	setName("");

	for (auto line : { header, footer }) {

		size_t found_arr_begin = line.find_first_of('[');
		size_t found_arr_end = line.find_last_of(']');

		if (string::npos != found_arr_begin && string::npos != found_arr_end) {
			m_array = true;
			m_array_size = line.substr(found_arr_begin, found_arr_end - found_arr_begin + 1);
			line = line.substr(0, found_arr_begin);
		}

		auto spl = StringHandler::space(line);
		size_t size = spl.size();

		if (1 <= size) {
			if (getName().empty()) {
				if ("typedef" != spl[size - 1] && "const" != spl[size - 1] &&
					"static" != spl[size - 1] && "volatile" != spl[size - 1] && "struct" != spl[size - 1])
				{
					setName(spl[size - 1]);
				}
			}

			for (int i = 0; i < size - 1; ++i) {
				if ("typedef" == spl[i]) {
					m_typedef = true;
				}
				else if ("const" == spl[i]) {
					setConst(true);
				}
				else if ("static" == spl[i]) {
					setStatic(true);
				}
				else if ("volatile" == spl[i]) {
					setVolatile(true);
				}
			}
		}
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
				inner_struct = false;
				m_value.push_back(new cStructToken(chank));
				chank.clear();
				continue;
			}
		}

		if ('{' == ch) {
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
	cout << cBaseToken::get_offset_string(offset_) << "is array : " << m_array << endl;
	cout << cBaseToken::get_offset_string(offset_) << "array size : " << m_array_size << endl;

	for (auto i : m_value) {
		i->show(offset_ + 1);
	}

}
