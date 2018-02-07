#include "c_enum_token.hpp"

cEnumToken::cEnumToken(const string& buffer) : cBaseToken(cBaseToken::TokenType::typedef_enum, buffer)
{
	size_t start = buffer.find('{');
	size_t stop = buffer.find('}');

	if (string::npos != start && string::npos != stop && start < stop) {		
#ifdef  TASK_0_2_5__4
		setName(StringHandler::filter<string, char>(buffer.substr(stop + 1), StringHandler::FBE::begin_and_end, { ' ', '\n', '\t', '\\' }));
#else
		setName(StringHandler::filter(buffer.substr(stop + 1), StringHandler::FBE::begin_and_end, { ' ', '\n', '\t', '\\' }));
#endif

		string tmp = buffer.substr(start + 1, stop - start - 1);
		vector<string> tmps = StringHandler::split(tmp, ',');

		int cnt = 0;

		for (auto line : tmps) {

#ifdef TASK_0_2_5__4
			if (StringHandler::filter<string, char>(line, StringHandler::FBE::all, { ' ', '\t', '\n', '\\' }).empty()) {
				continue;
		}
#else
			if (StringHandler::filter(line, StringHandler::FBE::all, { ' ', '\t', '\n', '\\' }).empty()) {
				continue;
			}
#endif

			vector<string> chank = StringHandler::split(line, '=');
			if (2 > chank.size()) {
				chank.push_back("");
			}

#ifdef  TASK_0_2_5__4
			string enumItemName = StringHandler::filter<string, char>(chank[0], StringHandler::FBE::all, { ' ', '\n', '\t', '\\' });
			string enumItemValue = StringHandler::filter<string, char>(chank[1], StringHandler::FBE::all, { ' ', '\n', '\t', '\\' });
#else
			string enumItemName  = StringHandler::filter(chank[0], StringHandler::FBE::all, { ' ', '\n', '\t', '\\' });
			string enumItemValue = StringHandler::filter(chank[1], StringHandler::FBE::all, { ' ', '\n', '\t', '\\' });
#endif

			m_value.push_back({enumItemName, enumItemValue});
		}
	}
}

cEnumToken::~cEnumToken()
{
}

void cEnumToken::show(int offset_) const
{
	cBaseToken::show(offset_);
	for (auto item : m_value) {
		cout << cBaseToken::get_offset_string(offset_ + 1) << item[0] << " = " << item[1] << endl;
	}
}

#ifdef  TASK_0_2_5
void cEnumToken::write(const string & dir_, const string & file_name_, const string & mode_)
{
	cBaseToken::write(dir_, file_name_, mode_);

	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

	string fill_name = dir_ + "\\" + file_name_;

	JsonObject json_object(L"root");
	json_object.set({}, L"cells", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());

	size_t idx = 0;

	//
	// Ячейка "Общее"
	//
	json_object.set({ L"cells" }, L"cell_" + std::to_wstring(idx), JsonObject::eType::object, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"cell_type", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"markdown"));
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"metadata", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"source", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_0", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"### Общее\\n"));
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_1", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"\\n"));

	//
	// Ячейки "Элементы перечисления"
	//
	for (auto item : m_value) {
		idx++;
		json_object.set({ L"cells" }, L"cell_" + std::to_wstring(idx), JsonObject::eType::object, variant<wstring, double, JsonBase::eSimple>());
		json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"cell_type", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"markdown"));
		json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"metadata", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
		json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"source", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());
		json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_0", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"```c\\n"));

		string code_line;
		if (1 <= item.size()) {
			code_line = item[0];
			if (2 <= item.size()) {
				if (false == item[1].empty()) {
					code_line += " = " + item[1] + "\\n";
				}				
			}
		}

		json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_1",
			JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(converter.from_bytes(code_line)));

		json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_2", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"```"));
	}

	//
	// Ячейка "Код"
	//
	idx++;
	cout << idx << endl;
	json_object.set({ L"cells" }, L"cell_" + std::to_wstring(idx), JsonObject::eType::object, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"cell_type", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"markdown"));
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"metadata", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"source", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_0", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"```c\\n"));

	auto code_lines = get_raw_Lines(false);
	for (size_t i = 0; i < code_lines.size(); ++i) {
		json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_" + std::to_wstring(i),
			JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(converter.from_bytes(code_lines[i] + "\\n")));
	}

	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_" + std::to_wstring(code_lines.size()), JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"```"));

	json_object.write(fill_name, "ipynb");

	cout << fill_name << endl;
}
#else
void cEnumToken::write(const string & dir_, const string & file_name_)
{

	cBaseToken::write(dir_, file_name_);

	string fill_name = dir_ + "\\\\" + file_name_;

	if (!std::experimental::filesystem::exists(fill_name)) {

		string members;
		for (auto item : m_value) {
			if (1 == item.size() || 2 == item.size()) {
				members += ".. ext-d-enum-member:: " + item[0];
				if (2 == item.size()) {
					if (!item[1].empty()) {
						members += " = " + item[1];
					}					
				}
				members += "\n\n\n";
			}
		}

		std::ofstream fout(fill_name);
		fout << ".. ext-d-state:: false" << endl << endl
			<< ".. ext-d-version:: " << PROJECT_VERSION << endl << endl
			<< ".. ext-d-token-type:: " << cBaseToken::tokenTypeNames[m_type] << endl << endl
			<< ".. ext-d-paragraph:: Общее" << endl << endl << endl
			<< members
			<< ".. ext-d-code-block:: c-lang" << endl << endl
			<< getRaw() << ";" << endl;
		fout.close();
	}
}
#endif
