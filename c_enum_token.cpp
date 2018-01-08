#include "c_enum_token.hpp"

cEnumToken::cEnumToken(const string& buffer) : cBaseToken(cBaseToken::TokenType::typedef_enum, buffer)
{
	size_t start = buffer.find('{');
	size_t stop = buffer.find('}');

	if (string::npos != start && string::npos != stop && start < stop) {		
		setName(StringHandler::filter(buffer.substr(stop + 1), StringHandler::FBE::begin_and_end, { ' ', '\n', '\t', '\\' }));

		string tmp = buffer.substr(start + 1, stop - start - 1);
		vector<string> tmps = StringHandler::split(tmp, ',');

		int cnt = 0;

		for (auto line : tmps) {

			if (StringHandler::filter(line, StringHandler::FBE::all, { ' ', '\t', '\n', '\\' }).empty()) {
				continue;
			}

			vector<string> chank = StringHandler::split(line, '=');
			if (2 > chank.size()) {
				chank.push_back("");
			}

			string enumItemName  = StringHandler::filter(chank[0], StringHandler::FBE::all, { ' ', '\n', '\t', '\\' });
			string enumItemValue = StringHandler::filter(chank[1], StringHandler::FBE::all, { ' ', '\n', '\t', '\\' });

			m_value.push_back({enumItemName, enumItemValue});
		}
	}
}

void cEnumToken::show(int offset_) const
{
	cBaseToken::show(offset_);
	for (auto item : m_value) {
		cout << cBaseToken::get_offset_string(offset_ + 1) << item[0] << " = " << item[1] << endl;
	}
}

void cEnumToken::write(const string & dir_, const string & file_name_)
{

	cBaseToken::write(dir_, file_name_);

	string fill_name = dir_ + "\\\\" + file_name_;

	if (!std::experimental::filesystem::exists(fill_name)) {

		string members;
		for (auto item : m_value) {
			if (1 == item.size() || 2 == item.size()) {
				members += ".. ext-d-enum-member:: " + item[0] + "\n";
				if (2 == item.size()) {
					if (!item[1].empty()) {
						members += "\t:value: " + item[1];
					}					
				}
				members += "\n\n";
			}
		}

		std::ofstream fout(fill_name);
		fout << ".. ext-d-state:: false" << endl << endl
			<< ".. ext-d-version:: " << PROJECT_VERSION << endl << endl
			<< ".. ext-d-token-type:: " << cBaseToken::tokenTypeNames[m_type] << endl << endl
			<< ".. ext-d-paragraph::" << endl << endl << endl
			<< members
			<< ".. ext-d-code-block:: c-lang" << endl << endl
			<< getRaw() << ";" << endl;
		fout.close();
	}
}
