#include "c_def_var_token.hpp"

cDefVar::cDefVar(const string& buffer): cBaseToken(cBaseToken::TokenType::def_var, buffer)
{
	cout << "-" << endl;

	m_static = false;
	m_const = false;
	m_extern = false;
	m_volatile = false;
	m_array = false;
	m_function_pointer = false;

	auto spl = StringHandler::split(buffer, '=');

	size_t found_brace = spl[0].find('(');
	if (string::npos == found_brace) {

		//
		// Разбор объявления переменных.
		//

		vector<string> header = StringHandler::space(spl[0]);

		size_t size = header.size();
		if (2 <= size) {

			size_t sqr_brack = header[size - 1].find('[');
			if (string::npos == sqr_brack) {
				setName(header[size - 1]);
			}
			else {
				setName(header[size - 1].substr(0, sqr_brack));
				m_array = true;
				m_array_size = header[size - 1].substr(sqr_brack + 1, header[size - 1].size() - sqr_brack - 2);
			}

			m_dataType = header[size - 2];

			for (int i = 0; i < size - 2; i++) {

				if ("static" == header[i]) {
					m_static = true;
				}
				else if ("const" == header[i]) {
					m_const = true;
				}
				else if ("extern" == header[i]) {
					m_extern = true;
				}
				else if ("volatile" == header[i]) {
					m_volatile = true;
				}
			}
		}
	}
	else {

		//
		// Разбор объявления указателей на функции
		//
		size_t first_begin_parentheses = spl[0].find_first_of('(');
		size_t first_end_parentheses = spl[0].find_first_of(')');
		size_t second_begin_parentheses = spl[0].find_last_of('(');
		size_t second_end_parentheses = spl[0].find_last_of(')');

		if (string::npos != first_begin_parentheses && string::npos != first_end_parentheses && \
			string::npos != second_begin_parentheses && string::npos != second_end_parentheses &&
			first_begin_parentheses < first_end_parentheses && first_end_parentheses < second_begin_parentheses && \
			second_begin_parentheses < second_end_parentheses)
		{
			m_dataType = StringHandler::filter(spl[0].substr(0, first_begin_parentheses), 
				StringHandler::FBE::begin_and_end, {' ', '\t', '\n'});

			string pre_name = spl[0].substr(first_begin_parentheses + 1, first_end_parentheses - first_begin_parentheses - 1);
			size_t sqr_brack_begin = pre_name.find('[');
			size_t sqr_brack_end = pre_name.find(']');
			if (string::npos != sqr_brack_begin && string::npos != sqr_brack_end && sqr_brack_begin < sqr_brack_end) {
				setName(pre_name.substr(0, sqr_brack_begin));
				m_array = true;
				m_function_pointer = true;
				m_array_size = pre_name.substr(sqr_brack_begin + 1, sqr_brack_end - sqr_brack_begin - 1);
			}
			else {
				setName(pre_name);
			}

			m_pfunc_arg = StringHandler::filter(
				spl[0].substr(second_begin_parentheses + 1, second_end_parentheses - second_begin_parentheses - 1),
				StringHandler::FBE::all, {' ', '\t', '\n', '\\'}
			);
		}
	}

	if (1 < spl.size()) {
		m_initValue = StringHandler::filter(spl[1], StringHandler::FBE::all, {' ', '\t', '\n', '\\'});
	}

	cout << "-" << endl;
}

void cDefVar::show(int offset_) const
{
	string initValue = m_initValue.empty() ? "<none>" : m_initValue;
	cBaseToken::show(offset_);
	cout << cBaseToken::get_offset_string(offset_ + 1) << "Data Type : " << m_dataType << endl;
	cout << cBaseToken::get_offset_string(offset_ + 1) << "Init value : " << initValue << endl;
	cout << cBaseToken::get_offset_string(offset_ + 1) << "is static : " << m_static << endl;
	cout << cBaseToken::get_offset_string(offset_ + 1) << "is const : " << m_const << endl;
	cout << cBaseToken::get_offset_string(offset_ + 1) << "is extern : " << m_extern << endl;
	cout << cBaseToken::get_offset_string(offset_ + 1) << "is volatile : " << m_volatile << endl;
	cout << cBaseToken::get_offset_string(offset_ + 1) << "is array : " << m_array << endl;
	cout << cBaseToken::get_offset_string(offset_ + 1) << "array size : " << m_array_size << endl;
	cout << cBaseToken::get_offset_string(offset_ + 1) << "is function pointer : " << m_function_pointer << endl;
	cout << cBaseToken::get_offset_string(offset_ + 1) << "pfunc arg : " << m_pfunc_arg << endl;
}
