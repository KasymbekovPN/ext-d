#include "c_def_var_token.hpp"

cDefVar::cDefVar(const string& buffer): cBaseToken(cBaseToken::TokenType::def_var, buffer)
{

	bool var_is_pointer = false;
	bool ret_is_pointer = false;

	m_array = false;
	m_function_pointer = false;
	m_typedef = false;
	m_struct = false;

	//
	// Определяем инициализатор
	// 
	auto spl = StringHandler::split(buffer, '=');
	if (1 < spl.size()) {
		m_initValue = StringHandler::filter(spl[1], StringHandler::FBE::all, {' ', '\t', '\n', '\\'});
	}

	size_t first_begin_round_brack = spl[0].find_first_of('(');
	size_t first_end_round_brack = spl[0].find_first_of(')');
	size_t second_begin_round_brack = spl[0].find_last_of('(');
	size_t second_end_round_brack = spl[0].find_last_of(')');

	//
	// Не является указателем на функцию.
	//
	if (string::npos == first_begin_round_brack && string::npos == first_end_round_brack &&
		string::npos == second_begin_round_brack && string::npos == second_end_round_brack)
	{

		//
		// Является ли массивом?
		//
		size_t begin_sqr_brack = spl[0].find_first_of('[');
		size_t end_sqr_brack = spl[0].find_last_of(']');

		string header = spl[0];

		if (string::npos != begin_sqr_brack && string::npos != end_sqr_brack && end_sqr_brack > begin_sqr_brack) {
			m_array = true;
			m_array_size = spl[0].substr(begin_sqr_brack/*, end_sqr_brack - begin_sqr_brack*/);
			header = spl[0].substr(0, begin_sqr_brack);
		}

		var_is_pointer = string::npos != header.find('*');
		header = StringHandler::filter(header, StringHandler::FBE::all, {'*'});

		auto head_spl = StringHandler::space(header);

		size_t size = head_spl.size();
		if (2 <= size) {

			setName(head_spl[size - 1]);
			m_dataType = head_spl[size - 2];

			for (int i = 0; i < size - 2; ++i) {
				if ("unsigned" == head_spl[i]) {
					m_dataType = "unsigned " + m_dataType;
				}
				else if ("static" == head_spl[i]) {
					setStatic(true);
				}
				else if ("const" == head_spl[i]) {
					setConst(true);
				}
				else if ("extern" == head_spl[i]) {
					setExtern(true);
				}
				else if ("volatile" == head_spl[i]) {
					setVolatile(true);
				}
				else if ("struct" == head_spl[i]) {
					m_struct = true;
				}
			}

			if (var_is_pointer) {
				m_dataType += "*";
			}
		}
	}

	//
	// Является указателем на функцию
	//
	if (string::npos != first_begin_round_brack && string::npos != first_end_round_brack &&
		string::npos != second_begin_round_brack && string::npos != second_end_round_brack &&
		first_begin_round_brack != second_begin_round_brack &&
		first_end_round_brack != second_end_round_brack)
	{

		m_function_pointer = true;

		string header = buffer.substr(0, first_begin_round_brack);
		string pre_name = buffer.substr(first_begin_round_brack + 1, first_end_round_brack - first_begin_round_brack - 1);
		m_pfunc_arg = buffer.substr(second_begin_round_brack +1, second_end_round_brack - second_begin_round_brack - 1);

		//
		// Получение имени
		//
		size_t sqr_found = pre_name.find('[');
		if (string::npos != sqr_found) {
			setName(StringHandler::filter(pre_name.substr(0, sqr_found), StringHandler::FBE::all, {'*', ' ', '\t', '\n', '\\'}));
			m_array = true;
			m_array_size = StringHandler::filter(
				pre_name.substr(sqr_found), StringHandler::FBE::begin_and_end, {' ', '\t', '\n', '\\'}
			);
		}
		else {
			setName(StringHandler::filter(pre_name, StringHandler::FBE::all, { '*', ' ', '\t', '\n', '\\' }));
		}

		if (string::npos != header.find('*')) {
			ret_is_pointer = true;
			header = StringHandler::filter(header, StringHandler::FBE::all, {'*'});
		}

		auto head_spl = StringHandler::space(header);
		size_t size = head_spl.size();
		if (1 <= size) {

			m_dataType = head_spl[size - 1];

			for (int i = 0; i < size - 1; ++i) {

				if ("typedef" == head_spl[i]) {
					m_typedef = true;
				}
				else if ("unsigned" == head_spl[i]) {
					m_dataType = "unsigned " + m_dataType;
				}
				else if ("static" == head_spl[i]) {
					setStatic(true);
				}
				else if ("volatile" == head_spl[i]) {
					setVolatile(true);
				}
				else if ("extern" == head_spl[i]) {
					setExtern(true);
				}
				else if ("const" == head_spl[i]) {
					setConst(true);
				}
				else if ("struct" == head_spl[i]) {
					m_struct = true;
				}
			}

			if (ret_is_pointer) {
				m_dataType += "*";
			}

		}
	}
}

void cDefVar::show(int offset_) const
{
	string initValue = m_initValue.empty() ? "<none>" : m_initValue;
	cBaseToken::show(offset_);
	cout << cBaseToken::get_offset_string(offset_) << "Data Type : " << m_dataType << endl;
	cout << cBaseToken::get_offset_string(offset_) << "is typedef: " << m_typedef << endl;
	cout << cBaseToken::get_offset_string(offset_) << "Init value : " << initValue << endl;
	cout << cBaseToken::get_offset_string(offset_) << "is array : " << m_array << endl;
	cout << cBaseToken::get_offset_string(offset_) << "array size : " << m_array_size << endl;
	cout << cBaseToken::get_offset_string(offset_) << "is function pointer : " << m_function_pointer << endl;
	cout << cBaseToken::get_offset_string(offset_) << "pfunc arg : " << m_pfunc_arg << endl;
	cout << cBaseToken::get_offset_string(offset_) << "is struct: " << m_struct << endl;
}

void cDefVar::write(const string & dir_, const string & file_name_)
{

	cBaseToken::write(dir_, file_name_);

	string fill_name = dir_ + "\\\\" + file_name_;

	if (!std::experimental::filesystem::exists(fill_name)) {
		std::ofstream fout(fill_name);
		fout << ".. ext-d-state:: false" << endl << endl			
			<< ".. ext-d-version:: " << PROJECT_VERSION << endl << endl			
			<< ".. ext-d-token-type:: " << cBaseToken::tokenTypeNames[m_type] << endl << endl			
			<< ".. ext-d-paragraph:: Общее" << endl << endl
			<< ".. ext-d-code-block:: c-lang" << endl << endl
			<< getRaw() << ";" << endl;
		fout.close();
	}
}
