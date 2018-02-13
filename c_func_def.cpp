#include "c_func_def.hpp"

cFuncDef::cFuncDef(const string & buffer): cBaseToken(cBaseToken::TokenType::func_def, buffer)
{

	size_t brace_begin_found = buffer.find('(');
	size_t brace_end_found = buffer.find(')');

	if (string::npos != brace_begin_found && string::npos != brace_end_found && brace_begin_found < brace_end_found) {

		auto first = StringHandler::space(buffer.substr(0, brace_begin_found));
		size_t first_size = first.size();

		if (2 <= first_size) {

			setName(first[first_size - 1]);
			m_dataType = StringHandler::filter<string, char>(
				first[first_size - 2], StringHandler::FBE::begin_and_end, { ' ', '\t', '\n' }
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
			m_args += StringHandler::filter<string, char>(second[i], StringHandler::FBE::begin_and_end, { ' ', '\t', '\n' });
			if (i < second.size() - 1) {
				m_args += ',';
			}
		}
	}

	size_t value_begin_found = buffer.find_first_of('{');
	if (string::npos != value_begin_found) {
		m_value = buffer.substr(value_begin_found + 1);
	}
}

cFuncDef::~cFuncDef()
{
}

void cFuncDef::show(int offset_) const
{
	cBaseToken::show(offset_);
	cout << cBaseToken::get_offset_string(offset_) << "Data Type : " << m_dataType << endl;
	cout << cBaseToken::get_offset_string(offset_) << "Args : " << (m_args.empty() ? "<none>" : m_args) << endl;
	cout << "Value : " << endl << StringHandler::filter<string, char>(m_value, StringHandler::FBE::all, { ' ', '\n', '\t', '\\' }) << endl;
}

void cFuncDef::write(const string & dir_, const string & file_name_, const string & mode_)
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
	// Ячейки "Аргументы"
	//
	auto args = StringHandler::split(m_args, ',');
	for (auto arg : args) {
		idx++;
		json_object.set({ L"cells" }, L"cell_" + std::to_wstring(idx), JsonObject::eType::object, variant<wstring, double, JsonBase::eSimple>());
		json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"cell_type", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"markdown"));
		json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"metadata", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
		json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"source", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());
		json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_0", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"#### Аргумент:\\n"));
		json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_1",
			JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(converter.from_bytes(arg) + L"\\n"));

	}

	//
	// Ячейка "Возвращает"
	//
	if ("void" != m_dataType) {
		idx++;
			json_object.set({ L"cells" }, L"cell_" + std::to_wstring(idx), JsonObject::eType::object, variant<wstring, double, JsonBase::eSimple>());
			json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"cell_type", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"markdown"));
			json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"metadata", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
			json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"source", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());
			json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_0", 
				JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"#### Возвращает (" +converter.from_bytes(m_dataType) + L"):\\n"));
	}

	//
	// Ячейка "Код"
	//
	idx++;
	json_object.set({ L"cells" }, L"cell_" + std::to_wstring(idx), JsonObject::eType::object, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"cell_type", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"markdown"));
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"metadata", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"source", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_0", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"```c\\n"));

	auto code_lines = get_raw_WLines(false);
	for (size_t i = 0; i < code_lines.size(); ++i) {
		wstring code_line = StringHandler::escape_wchar(code_lines[i], L'"');
		json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_" + std::to_wstring(i),
			JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(code_line + L"\\n"));
	}

	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_" + std::to_wstring(code_lines.size()), JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"}\\n"));
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_" + std::to_wstring(code_lines.size() + 1), JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"```"));

#ifdef  TASK_27__1
	json_object.write(fill_name, "ipynb", false);
#else
	json_object.write(fill_name, "ipynb");
#endif
}
