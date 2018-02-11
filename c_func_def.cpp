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
#ifdef  TASK_0_2_5__4
			m_dataType = StringHandler::filter<string, char>(
				first[first_size - 2], StringHandler::FBE::begin_and_end, { ' ', '\t', '\n' }
			);
#else
			m_dataType = StringHandler::filter(
				first[first_size - 2], StringHandler::FBE::begin_and_end, { ' ', '\t', '\n' }
			);
#endif

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
#ifdef  TASK_0_2_5__4
			m_args += StringHandler::filter<string, char>(second[i], StringHandler::FBE::begin_and_end, { ' ', '\t', '\n' });
#else
			m_args += StringHandler::filter(second[i], StringHandler::FBE::begin_and_end, { ' ', '\t', '\n' });
#endif
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
#ifdef  TASK_0_2_5__4
	cout << "Value : " << endl << StringHandler::filter<string, char>(m_value, StringHandler::FBE::all, { ' ', '\n', '\t', '\\' }) << endl;
#else
	cout << "Value : " << endl << StringHandler::filter(m_value, StringHandler::FBE::all, { ' ', '\n', '\t', '\\' }) << endl;
#endif
}

#ifdef  TASK_0_2_5
void cFuncDef::write(const string & dir_, const string & file_name_, const string & mode_)
{

	//cout << 1 << endl;

	cBaseToken::write(dir_, file_name_, mode_);

	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

	string fill_name = dir_ + "\\" + file_name_;

	JsonObject json_object(L"root");
	json_object.set({}, L"cells", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());

	//cout << 2 << endl;

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

	//cout << 3 << endl;

	//
	// Ячейки "Аргументы"
	//

	//m_args;
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

	//cout << 4 << endl;

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

	////cout << 5 << endl;

	//
	// Ячейка "Код"
	//
	idx++;
	json_object.set({ L"cells" }, L"cell_" + std::to_wstring(idx), JsonObject::eType::object, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"cell_type", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"markdown"));
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"metadata", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx) }, L"source", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_0", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"```c\\n"));

	//cout << 6 << endl;

	//cout << endl;
	//string str = "абвгдеёжзийклмнопрстухфцчшщьыъэюя";
	//wstring wstr = L"абвгдеёжзийклмнопрстухфцчшщьыъэюя";

	//for (auto ch : str) {
	//	cout << ch << " - " << int(ch) << " - " << sizeof(ch) << endl;
	//}

	//for (auto wch : wstr) {
	//	std::wcout << wch << L" - " << int(wch) << L" - " << sizeof(wch) << endl;
	//}

	//const std::locale utf8_locale = std::locale(std::locale(),
	//	new std::codecvt_utf8<wchar_t>());

	//std::wofstream fout(path_);
	//fout.imbue(utf8_locale);
	//std::wstring s = to_string(L"", true, false);
	////std::wcout << s << std::endl;
	//fout << s;
	//fout.close();

	//setlocale(LC_ALL, "Russian");
	//std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	//std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter1;
	//auto res = converter1.from_bytes(str);
	
	//wchar_t warray[4096];
	//string tmp = getRaw();
	//size_t size = tmp.length();

	//MultiByteToWideChar(CP_ACP, 0, tmp.c_str(), size, warray, size);

	//cout << tmp << endl;

	//cout << "---" << endl;

	//std::wcout << warray << endl;

	//auto code_lines = get_raw_Lines(false);
	//for (size_t i = 0; i < code_lines.size(); ++i) {

		//const char* charArray = "Привет";
		//const size_t size = code_lines[i].length() + 1;
		//wchar_t warray[4096];
		//wchar_t* wString = new wchar_t[7];
		

		//cout << " -- " << code_lines[i] << endl;
		//std::wcout << " ++ " << warray << endl;

		//json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_" + std::to_wstring(i),
		//	JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(converter.from_bytes(code_lines[i] + "\\n")));
	//}

	//string s = "Привет";
	//wstring ws;

	//const char* charArray = "Привет";
	//wchar_t warray[7];
	////wchar_t* wString = new wchar_t[7];
	//MultiByteToWideChar(CP_ACP, 0, s.c_str(), 7, warray, 7);

	//std::wcout << warray << endl;

	//wstring AnsiToWide(const string& in_sAnsi)
	//{
	//	wstring wsWide;
	//	wsWide.resize(in_sAnsi.length(), 0);
	//	MultiByteToWideChar(
	//		CP_ACP,
	//		0,
	//		&in_sAnsi[0],
	//		(int)in_sAnsi.length(),
	//		&wsWide[0],
	//		(int)wsWide.length());

	//	return wsWide;
	//}

#ifdef  TASK_0_2_5__8
#ifdef TASK_0_2_5__9
	auto code_lines = get_raw_WLines(false);
#else
	auto code_lines = get_raw_WLines(false);
#endif // TASK_0_2_5__9	
	//cout << 1 << endl;
	for (size_t i = 0; i < code_lines.size(); ++i) {
		//std::wcout << code_lines[i] << endl;
		wstring code_line = StringHandler::escape_wchar(code_lines[i], L'"');
		//std::wcout << code_line << endl;
#ifdef  TASK_0_2_5__9
		json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_" + std::to_wstring(i),
			JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(code_line + L"\\n"));
#else
		json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_" + std::to_wstring(i),
			JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(code_line + L"\\n"));
#endif
	}
#else
	auto code_lines = get_raw_Lines(false);
	for (size_t i = 0; i < code_lines.size(); ++i) {
		json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_" + std::to_wstring(i),
			JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(converter.from_bytes(code_lines[i] + "\\n")));
	}
#endif

	//cout << 7 << endl;

	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_" + std::to_wstring(code_lines.size()), JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"}\\n"));
	json_object.set({ L"cells", L"cell_" + std::to_wstring(idx), L"source" }, L"source_" + std::to_wstring(code_lines.size() + 1), JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"```"));

	json_object.write(fill_name, "ipynb");

	//cout << 8 << endl;
}
#else
void cFuncDef::write(const string & dir_, const string & file_name_)
{
	cBaseToken::write(dir_, file_name_);

	string fill_name = dir_ + "\\\\" + file_name_;

	if (!std::experimental::filesystem::exists(fill_name)) {

		string args;
		auto spl = StringHandler::split(m_args, ',');
		for (auto arg : spl) {
			if (!arg.empty()) {
				args += ".. ext-d-func-param:: " + arg + "\n\n";
			}
		}

		std::ofstream fout(fill_name);
		fout << ".. ext-d-state:: false" << endl << endl
			<< ".. ext-d-version:: " << PROJECT_VERSION << endl << endl
			<< ".. ext-d-token-type:: " << cBaseToken::tokenTypeNames[m_type] << endl << endl
			<< ".. ext-d-paragraph:: Общее" << endl << endl << endl
			<< args
			<< ".. ext-d-func-ret:: " << m_dataType << endl << endl
			<< ".. ext-d-code-block:: c-lang" << endl << endl
			<< getRaw() << "\n}" << endl;
		fout.close();
	}
}
#endif
