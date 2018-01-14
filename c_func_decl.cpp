#include "c_func_decl.hpp"

cFuncDecl::cFuncDecl(const string & buffer): cBaseToken(cBaseToken::TokenType::func_decl, buffer)
{

	size_t brace_begin_found = buffer.find('(');
	size_t brace_end_found = buffer.find(')');

	if (string::npos != brace_begin_found && string::npos != brace_end_found && brace_begin_found < brace_end_found) {

		auto first = StringHandler::space(buffer.substr(0, brace_begin_found));

		size_t first_size = first.size();

		if (2 <= first_size) {

			setName(first[first_size - 1]);
			m_dataType = StringHandler::filter(
				first[first_size - 2], StringHandler::FBE::begin_and_end, {' ', '\t', '\n'}
			);

			for (int i = 0; i < first_size - 2; ++i) {
				if ("static" == first[i]) {
					setStatic(true);
				}
				else if ("const" == first[i]) {
					setConst(true);
				}
				else if ("extern" == first[i]) {
					setExtern(true);
				}
			}
		}

		auto second = StringHandler::split(buffer.substr(brace_begin_found + 1, brace_end_found - brace_begin_found - 1), ',');
		m_args.clear();
		for (int i = 0; i < second.size(); ++i) {
			m_args += StringHandler::filter(second[i], StringHandler::FBE::begin_and_end, {' ', '\t', '\n'});
			if (i < second.size() - 1) {
				m_args += ',';
			}
		}
	}
}

void cFuncDecl::show(int offset_) const
{
	cBaseToken::show(offset_);
	cout << cBaseToken::get_offset_string(offset_) << "Data Type : " << m_dataType << endl;
	cout << cBaseToken::get_offset_string(offset_) << "Args : " << (m_args.empty() ? "<none>" : m_args) << endl;
}

void cFuncDecl::write(const string & dir_, const string & file_name_)
{
	cBaseToken::write(dir_, file_name_);

	string fill_name = dir_ + "\\\\" + file_name_;

	if (!std::experimental::filesystem::exists(fill_name)) {

		std::ofstream fout(fill_name);
		fout << ".. ext-d-state:: false" << endl << endl
			<< ".. ext-d-version:: " << PROJECT_VERSION << endl << endl
			<< ".. ext-d-token-type:: " << cBaseToken::tokenTypeNames[m_type] << endl << endl
			<< ".. ext-d-paragraph:: Общее" << endl << endl << endl
			<< ".. ext-d-code-block:: c-lang" << endl << endl
			<< getRaw() << ";" << endl;
		fout.close();
	}
}
