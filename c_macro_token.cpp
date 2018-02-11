#include "c_macro_token.hpp"

cMacroToken::cMacroToken(const string & buffer) : cBaseToken(cBaseToken::TokenType::macro, buffer)
{
	bool rec_name = true;
	bool parenthesis = false;
	bool rec_value = false;

	m_value.clear();

	string line = StringHandler::filter<string, char>(buffer.substr(7), StringHandler::FBE::begin_and_end, { ' ', '\t' });
	string name;

	for (auto ch : line) {

		if (rec_name) {
			name += ch;
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

	setName(StringHandler::filter<string, char>(name, StringHandler::FBE::begin_and_end, { ' ', '\n', '\t', '\\' }));
	m_value = StringHandler::filter<string, char>(m_value, StringHandler::FBE::all, { '\\', '\n', ' ', '\t' });
}

cMacroToken::~cMacroToken()
{
}

void cMacroToken::show(int offset_) const
{
	cBaseToken::show(offset_);
	cout << cBaseToken::get_offset_string(offset_) << "Token Value: " << endl << m_value << endl;
}

void cMacroToken::write(const string & dir_, const string & file_name_, const string & mode_)
{
	cBaseToken::write(dir_, file_name_, mode_);
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	string fill_name = dir_ + "\\" + file_name_;

	JsonObject json_object(L"root");
	json_object.set({}, L"cells", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());

	json_object.set({ L"cells" }, L"cell_0", JsonObject::eType::object, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_0" }, L"cell_type", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"markdown"));
	json_object.set({ L"cells", L"cell_0" }, L"metadata", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_0" }, L"source", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_0", L"source" }, L"source_0", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"### Общее\\n"));
	json_object.set({ L"cells", L"cell_0", L"source" }, L"source_1", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"\\n"));

	json_object.set({ L"cells" }, L"cell_1", JsonObject::eType::object, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_1" }, L"cell_type", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"markdown"));
	json_object.set({ L"cells", L"cell_1" }, L"metadata", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_1" }, L"source", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_1", L"source" }, L"source_0", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"```c\\n"));

	auto code_lines = get_raw_Lines(false);
	for (size_t i = 0; i < code_lines.size(); ++i) {
		json_object.set({ L"cells", L"cell_1", L"source" }, L"source_" + std::to_wstring(i), 
			JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(converter.from_bytes(code_lines[i] + "\\n")));
	}	

	json_object.set({ L"cells", L"cell_1", L"source" }, L"source_" + std::to_wstring(code_lines.size()), JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"```"));
	json_object.write(fill_name, "ipynb");
}
