#include "jsonObject.hpp"

#ifdef TASK_0_2_5__4
JsonObject::JsonObject(const wstring & content_, const wstring& name_, shared_ptr<ErrorStatus> error_)
	: JsonBase(JsonBase::eType::object, name_, error_)
{

	//cout << "+" << endl;

	//std::wcout << content_ << endl;

	wstring filtred_content = StringHandler::filter<wstring, wchar_t>(content_, StringHandler::FBE::begin_and_end, { L' ', L'\t', L'\n' });



	if (L'{' != filtred_content[0] || L'}' != filtred_content[filtred_content.size() - 1]) {
		cout << "obj" << endl;
		p_error->set(ErrorStatus::error::json_objectInvalid, true);
		return;
	}

	size_t brack_counter = 0;
	size_t sqr_counter = 0;
	//vector<string> v;
	wstring tmp;
	for (size_t i = 1; i < filtred_content.size() - 1; ++i) {

		switch (filtred_content[i])
		{
		case L'{': brack_counter++; break;
		case L'}': brack_counter--; break;
		case L'[': sqr_counter++; break;
		case L']': sqr_counter--; break;
		default:
			break;
		}

		if ((0 == brack_counter && 0 == sqr_counter && ',' == filtred_content[i]) ||
			i == filtred_content.size() - 2)
		{

			if (i == filtred_content.size() - 2) { tmp += filtred_content[i]; }

			size_t found_dots = tmp.find_first_of(L':');
			if (wstring::npos == found_dots) {
				p_error->set(ErrorStatus::error::json_invalidSyntax, true);
			}
			else {

				wstring name = StringHandler::filter<wstring, wchar_t>(tmp.substr(0, found_dots), StringHandler::FBE::begin_and_end, { L' ', L'\t', L'\n' });
				if (L'"' == name[0] && L'"' == name[name.size() - 1]) {
					name = name.substr(1, name.size() - 2);

					wstring value = StringHandler::filter<wstring, wchar_t>(tmp.substr(found_dots + 1), StringHandler::FBE::begin_and_end, { L' ', L'\n', L'\t' });
					bool first_is_double_quot_mark = L'"' == value[0];
					bool last_is_double_quot_mark = L'"' == value[value.size() - 1];
					bool first_is_sqr_brack = L'[' == value[0];
					bool last_is_sqr_brack = L']' == value[value.size() - 1];
					bool first_is_brace = L'{' == value[0];
					bool last_is_brace = L'}' == value[value.size() - 1];

					if (first_is_double_quot_mark && last_is_double_quot_mark) {
						m_lists.push_back(new JsonString(
							value.substr(1, value.size() - 2),
							name,
							p_error
						));
					}
					else if (first_is_brace && last_is_brace) {
						m_lists.push_back(new JsonObject(value, name, p_error));
					}
					else if (first_is_sqr_brack && last_is_sqr_brack) {
						m_lists.push_back(new JsonArray(value, name, p_error));
					}
					else if (!first_is_brace && !first_is_double_quot_mark && !first_is_sqr_brack &&
						!last_is_brace && !last_is_double_quot_mark && !last_is_sqr_brack)
					{
						if (L"null" == value) {
							m_lists.push_back(new JsonSimple(JsonBase::eSimple::simple_null, name, p_error));
						}
						else if (L"false" == value) {
							m_lists.push_back(new JsonSimple(JsonBase::eSimple::simple_false, name, p_error));
						}
						else if (L"true" == value) {
							m_lists.push_back(new JsonSimple(JsonBase::eSimple::simple_true, name, p_error));
						}
						else {
							m_lists.push_back(new JsonNumber(value, name, p_error));
						}
					}
					else {
						p_error->set(ErrorStatus::error::json_invalidSyntax, true);
					}
				}
				else {
					p_error->set(ErrorStatus::error::json_invalidSyntax, true);
				}
			}

			tmp.clear();
		}
		else {
			tmp += filtred_content[i];
		}
	}
}
#else
JsonObject::JsonObject(const string & content_, const string& name_, shared_ptr<ErrorStatus> error_) 
	: JsonBase(JsonBase::eType::object, name_, error_)
{

	string filtred_content = StringHandler::filter(content_, StringHandler::FBE::begin_and_end, {' ', '\t', '\n'});
	if ('{' != filtred_content[0] || '}' != filtred_content[filtred_content.size() - 1]) {
		p_error->set(ErrorStatus::error::json_objectInvalid, true);
		return;
	}

	size_t brack_counter = 0;
	size_t sqr_counter = 0;
	vector<string> v;
	string tmp;
	for (size_t i = 1; i < filtred_content.size() - 1; ++i) {
		
		switch (filtred_content[i])
		{
		case '{': brack_counter++; break;
		case '}': brack_counter--; break;
		case '[': sqr_counter++; break;
		case ']': sqr_counter--; break;
		default:
			break;
		}

		if ((0 == brack_counter && 0 == sqr_counter && ',' == filtred_content[i]) ||
			i == filtred_content.size() - 2)
		{

			if (i == filtred_content.size() - 2) { tmp += filtred_content[i]; }

			size_t found_dots = tmp.find_first_of(':');
			if (string::npos == found_dots) {
				p_error->set(ErrorStatus::error::json_invalidSyntax, true);
			}
			else {

				string name = StringHandler::filter(tmp.substr(0, found_dots), StringHandler::FBE::begin_and_end, { ' ', '\t', '\n' });
				if ('"' == name[0] && '"' == name[name.size() - 1]){
					name = name.substr(1, name.size() - 2);

					string value = StringHandler::filter(tmp.substr(found_dots + 1), StringHandler::FBE::begin_and_end, {' ', '\n', '\t'});
					bool first_is_double_quot_mark = '"' == value[0];
					bool last_is_double_quot_mark = '"' == value[value.size() - 1];
					bool first_is_sqr_brack = '[' == value[0];
					bool last_is_sqr_brack = ']' == value[value.size() - 1];
					bool first_is_brace = '{' == value[0];
					bool last_is_brace = '}' == value[value.size() - 1];

					if (first_is_double_quot_mark && last_is_double_quot_mark) {
						m_lists.push_back(new JsonString(
							value.substr(1, value.size() - 2),
							name,
							p_error
						));
					}
					else if (first_is_brace && last_is_brace) {
						m_lists.push_back(new JsonObject(value, name, p_error));
					}
					else if (first_is_sqr_brack && last_is_sqr_brack) {
						m_lists.push_back(new JsonArray(value, name, p_error));
					}
					else if (!first_is_brace && !first_is_double_quot_mark && !first_is_sqr_brack &&
						!last_is_brace && !last_is_double_quot_mark && !last_is_sqr_brack) 
					{
						if ("null" == value) {
							m_lists.push_back(new JsonSimple(JsonBase::eSimple::simple_null, name, p_error));
						}
						else if ("false" == value) {
							m_lists.push_back(new JsonSimple(JsonBase::eSimple::simple_false, name, p_error));
						}
						else if ("true" == value) {
							m_lists.push_back(new JsonSimple(JsonBase::eSimple::simple_true, name, p_error));
						}
						else {
							m_lists.push_back(new JsonNumber(value, name, p_error));
						}
					}
					else {
						p_error->set(ErrorStatus::error::json_invalidSyntax, true);
					}
				}
				else {
					p_error->set(ErrorStatus::error::json_invalidSyntax, true);
				}
			}

			tmp.clear();
		}
		else {
			tmp += filtred_content[i];
		}
	}
}
#endif

#ifdef  TASK_0_2_5__4
JsonObject::JsonObject(const wstring & name_)
{
	m_type = JsonBase::eType::object;
	m_name = name_;
	m_lists.clear();
}
#else
JsonObject::JsonObject(const string & name_)
{
	m_type = JsonBase::eType::object;
	m_name = name_;
	m_lists.clear();
}
#endif

JsonObject::~JsonObject()
{
	//cout << "del o 1" << endl;
	for (auto p : m_lists) {
		delete p;
	}
	//cout << "del o 2" << endl;
}

#ifdef  TASK_0_2_5__4
void JsonObject::show(wstring offset) const
{
	JsonBase::show(offset);
	std::wcout << offset << L"{\n";
	for (auto i : m_lists) {
		i->show(offset + L'\t');
	}
	std::wcout << offset << L"}\n";
}
#else
void JsonObject::show(string offset) const
{
	JsonBase::show(offset);
	cout << offset << "{\n";
	for (auto i : m_lists) {
		i->show(offset + '\t');
	}
	cout << offset << "}\n";
}
#endif

#ifdef  TASK_0_2_5__4
void JsonObject::set(vector<wstring> path_, const wstring & name_, JsonBase::eType type_, std::variant<wstring, double, JsonBase::eSimple> arg_)
{
	if (0 == path_.size()) {
		switch (type_) {
		case JsonBase::eType::array:
			m_lists.push_back(new JsonArray(name_));
			break;
		case JsonBase::eType::number: {
			double tmp;
			try {
				tmp = std::get<double>(arg_);
			}
			catch (std::bad_variant_access&) {
				tmp = 0;
			}
			m_lists.push_back(new JsonNumber(name_, tmp));
		}  break;
		case JsonBase::eType::object:
			m_lists.push_back(new JsonObject(name_));
			break;
		case JsonBase::eType::simple: {
			JsonBase::eSimple tmp;
			try {
				tmp = std::get<JsonBase::eSimple>(arg_);
			}
			catch (std::bad_variant_access&) {
				tmp = JsonBase::eSimple::simple_null;
			}
			m_lists.push_back(new JsonSimple(name_, tmp));
		}  break;
		case JsonBase::eType::string: {
			wstring tmp;
			try {
				tmp = std::get<wstring>(arg_);
			}
			catch (std::bad_variant_access&) {
				tmp = L"";
			}
			m_lists.push_back(new JsonString(name_, tmp));
		}  break;
		default:
			break;
		}
	}
	else {

		for (auto iter : m_lists) {
			if (iter->Name() == path_[0]) {
				vector<wstring> new_path;
				std::copy(path_.begin() + 1, path_.end(), std::inserter(new_path, new_path.begin()));
				iter->set(new_path, name_, type_, arg_);
			}
		}

	}
}
#else
#ifdef TASK_0_2_5__1
void JsonObject::set(vector<string> path_, const string & name_, JsonBase::eType type_, std::variant<string, double, JsonBase::eSimple> arg_)
{
	if (0 == path_.size()){
		switch (type_) {
		case JsonBase::eType::array:
			m_lists.push_back(new JsonArray(name_));
			break;
		case JsonBase::eType::number: {
			double tmp;
			try {
				tmp = std::get<double>(arg_);
			}
			catch (std::bad_variant_access&) {
				tmp = 0;
			}
			m_lists.push_back(new JsonNumber(name_, tmp));
		}  break;
		case JsonBase::eType::object:
			m_lists.push_back(new JsonObject(name_));
			break;
		case JsonBase::eType::simple: {
			JsonBase::eSimple tmp;
			try {
				tmp = std::get<JsonBase::eSimple>(arg_);
			}
			catch (std::bad_variant_access&) {
				tmp = JsonBase::eSimple::simple_null;
			}
			m_lists.push_back(new JsonSimple(name_, tmp));
		}  break;
		case JsonBase::eType::string: {
			string tmp;
			try {
				tmp = std::get<string>(arg_);
			}
			catch (std::bad_variant_access&) {
				tmp = "";
			}
			m_lists.push_back(new JsonString(name_, tmp));
		}  break;
		default:
			break;
		}
	}
	else {

		for (auto iter : m_lists) {
			if (iter->Name() == path_[0]) {
				vector<string> new_path;
				std::copy(path_.begin() + 1, path_.end(), std::inserter(new_path, new_path.begin()));
				iter->set(new_path, name_, type_, arg_);
			}
		}

	}
}
#endif
#endif


#ifdef  TASK_0_2_5__4
variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> JsonObject::get(vector<wstring> path_, eType * type_) const
{
	variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> res;

	if (0 == path_.size()) {
		*type_ = m_type;
		res = JsonBase::eGetterMsg::is_object;
		return res;
	}

	for (auto iter : m_lists) {

		if (path_[0] == iter->Name()) {
			vector<wstring> new_path;
			std::copy(path_.begin() + 1, path_.end(), std::inserter(new_path, new_path.begin()));
			res = iter->get(new_path, type_);
			return res;
		}
	}

	*type_ = m_type;
	res = JsonObject::eGetterMsg::not_exist;
	return res;
}
#else
variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> JsonObject::get(vector<string> path_, eType * type_) const
{
	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> res;

	if (0 == path_.size()) {
		*type_ = m_type;
		res = JsonBase::eGetterMsg::is_object;
		return res;
	}

	for (auto iter : m_lists) {
		
		if (path_[0] == iter->Name()) {
			vector<string> new_path;
			std::copy(path_.begin() + 1, path_.end(), std::inserter(new_path, new_path.begin()));
			res = iter->get(new_path, type_);
			return res;
		}
	}
	
	*type_ = m_type;
	res = JsonObject::eGetterMsg::not_exist;
	return res;
}
#endif

#ifdef  TASK_0_2_5
#ifdef  TASK_0_2_5__4
wstring JsonObject::to_string(const wstring & offset_, bool without_name_, bool end_with_comma_) const
{
	wstring res = offset_;
	if (false == without_name_) {
		res += L"\"" + m_name + L"\" : ";
	}
	res += L"{\n";
	for (size_t i = 0; i < m_lists.size(); ++i) {
#ifdef  TASK_0_2_5__6
		res += m_lists[i]->to_string(offset_ + L' ', false, i < m_lists.size() - 1);
#else
		res += m_lists[i]->to_string(offset_ + L'\t', false, i < m_lists.size() - 1);
#endif		
		//res += m_lists[i]->to_string(offset_ + '\t', false);
		//res += i < m_lists.size() ? ",\n" : "\n";
	}
	//res += "},\n";
	res += offset_ + (end_with_comma_ ? L"},\n" : L"}\n");

	return res;
}
#else
string JsonObject::to_string(const string & offset_, bool without_name_, bool end_with_comma_) const
{
	string res = offset_;
	if (false == without_name_) {
		res += "\"" + m_name + "\" : ";
	}
	res += "{\n";
	for (size_t i = 0; i < m_lists.size(); ++i) {
		res += m_lists[i]->to_string(offset_ + '\t', false, i < m_lists.size() - 1);
		//res += m_lists[i]->to_string(offset_ + '\t', false);
		//res += i < m_lists.size() ? ",\n" : "\n";
	}
	//res += "},\n";
	res += offset_ + (end_with_comma_ ? "},\n" : "}\n");

	return res;
}
#endif

void JsonObject::write(const string & path_, const string & mode_)
{

#ifdef  TASK_0_2_5__4
	if ("ipynb" == mode_) {

		set({}, L"metadata", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
		set({ L"metadata" }, L"kernelspec", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
		set({ L"metadata", L"kernelspec" }, L"display_name", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"Python 3"));
		set({ L"metadata", L"kernelspec" }, L"language", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"python"));
		set({ L"metadata", L"kernelspec" }, L"name", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"python3"));
		set({ L"metadata" }, L"language_info", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
		set({ L"metadata", L"language_info" }, L"codemirror_mode", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
		set({ L"metadata", L"language_info",L"codemirror_mode" }, L"name", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"ipython"));
		set({ L"metadata", L"language_info",L"codemirror_mode" }, L"version", JsonBase::eType::number, variant<wstring, double, JsonBase::eSimple>(3));
		set({ L"metadata", L"language_info" }, L"file_extension", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L".py"));
		set({ L"metadata", L"language_info" }, L"mimetype", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"text/x-python"));
		set({ L"metadata", L"language_info" }, L"name", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"python"));
		set({ L"metadata", L"language_info" }, L"nbconvert_exporter", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"python"));
		set({ L"metadata", L"language_info" }, L"pygments_lexer", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"ipython3"));
		set({ L"metadata", L"language_info" }, L"version", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"3.6.3"));
		set({}, L"nbformat", JsonBase::eType::number, variant<wstring, double, JsonBase::eSimple>(4));
		set({}, L"nbformat_minor", JsonBase::eType::number, variant<wstring, double, JsonBase::eSimple>(2));

		//std::wcout << to_string(L"", true, false) << endl;

		//cout << path_ << endl;
		size_t found = path_.find_last_of("\\");
		if (string::npos != found) {
			//cout << path_.substr(0, found) << endl;
			string dir_path = path_.substr(0, found);
			if (false == std::experimental::filesystem::exists(dir_path)) {
				std::experimental::filesystem::create_directory(dir_path);
			}
		}

		const std::locale utf8_locale = std::locale(std::locale(),
			new std::codecvt_utf8<wchar_t>());

		std::wofstream fout(path_);
		fout.imbue(utf8_locale);
		std::wstring s = to_string(L"", true, false);
		//std::wcout << s << std::endl;
		fout << s;
		fout.close();

		//std::wofstream file(path_);
		//file.imbue(utf8_locale);
		//file << tc.get();
		//file << tmp_json_object.to_string("", true, false);
		//file.close();

		//JsonObject tmp_json_object = *this;
		//tmp_json_object.set({}, L"metadata", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
		//tmp_json_object.set({ L"metadata" }, L"kernelspec", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
		//tmp_json_object.set({ L"metadata", L"kernelspec" }, L"display_name", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"Python 3"));
		//tmp_json_object.set({ L"metadata", L"kernelspec" }, L"language", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"python"));
		//tmp_json_object.set({ L"metadata", L"kernelspec" }, L"name", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"python3"));
		//tmp_json_object.set({ L"metadata" }, L"language_info", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
		//tmp_json_object.set({ L"metadata", L"language_info" }, L"codemirror_mode", JsonBase::eType::object, variant<wstring, double, JsonBase::eSimple>());
		//tmp_json_object.set({ L"metadata", L"language_info",L"codemirror_mode" }, L"name", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"ipython"));
		//tmp_json_object.set({ L"metadata", L"language_info",L"codemirror_mode" }, L"version", JsonBase::eType::number, variant<wstring, double, JsonBase::eSimple>(3));
		//tmp_json_object.set({ L"metadata", L"language_info" }, L"file_extension", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L".py"));
		//tmp_json_object.set({ L"metadata", L"language_info" }, L"mimetype", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"text/x-python"));
		//tmp_json_object.set({ L"metadata", L"language_info" }, L"name", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"python"));
		//tmp_json_object.set({ L"metadata", L"language_info" }, L"nbconvert_exporter", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"python"));
		//tmp_json_object.set({ L"metadata", L"language_info" }, L"pygments_lexer", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"ipython3"));
		//tmp_json_object.set({ L"metadata", L"language_info" }, L"version", JsonBase::eType::string, variant<wstring, double, JsonBase::eSimple>(L"3.6.3"));
		//tmp_json_object.set({}, L"nbformat", JsonBase::eType::number, variant<wstring, double, JsonBase::eSimple>(4));
		//tmp_json_object.set({}, L"nbformat_mirror", JsonBase::eType::number, variant<wstring, double, JsonBase::eSimple>(2));

		//std::wcout << tmp_json_object.to_string(L"", true, false) << endl;

		//cout << path_ << endl;

		//std::ofstream fout(path_);
		//fout << tmp_json_object.to_string("", true, false);
		//fout.close();

		//std::wofstream fout(path_);
		//std::wstring s = L"Hello Привет world";
		//std::wcout << s << std::endl;
		//fout << s;
		//fout.close();

		//#include <fstream>
		//#include <iostream>
		//#include <codecvt>
		//#include <locale>
		//#include <fcntl.h>
		//#include <io.h>
		//
		//		int main()
		//		{
		//
		//			const std::locale utf8_locale = std::locale(std::locale(),
		//				new std::codecvt_utf8<wchar_t>());
		//			{
		//				std::wofstream test_file("c:\\temp\\test.txt");
		//				test_file.imbue(utf8_locale);
		//				test_file << L"\u2122";
		//			}
		//
		//			_setmode(_fileno(stdout), _O_U8TEXT);
		//			std::wcout << L"\u2122";
		//		}

		//const std::locale utf8_locale = std::locale(std::locale(),
		//	new std::codecvt_utf8<wchar_t>());

		//test_class tc(L"Hello Привет world ###Общее\n");


		//std::wofstream file(path_);
		//file.imbue(utf8_locale);
		//file << tc.get();
		//file << tmp_json_object.to_string("", true, false);
		//file.close();

		//string tmp = tmp_json_object.to_string("", true, false);
		//std::wstring ws(tmp.begin(), tmp.end());
		//std::wcout << ws << endl;

	}
#else
	if ("ipynb" == mode_) {
		JsonObject tmp_json_object = *this;
		tmp_json_object.set({}, "metadata", JsonBase::eType::object, variant<string, double, JsonBase::eSimple>());
		tmp_json_object.set({"metadata"}, "kernelspec", JsonBase::eType::object, variant<string, double, JsonBase::eSimple>());
		tmp_json_object.set({ "metadata", "kernelspec" }, "display_name", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("Python 3"));
		tmp_json_object.set({ "metadata", "kernelspec" }, "language", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("python"));
		tmp_json_object.set({ "metadata", "kernelspec" }, "name", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("python3"));
		tmp_json_object.set({ "metadata" }, "language_info", JsonBase::eType::object, variant<string, double, JsonBase::eSimple>());
		tmp_json_object.set({ "metadata", "language_info"}, "codemirror_mode", JsonBase::eType::object, variant<string, double, JsonBase::eSimple>());
		tmp_json_object.set({ "metadata", "language_info","codemirror_mode" }, "name", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("ipython"));
		tmp_json_object.set({ "metadata", "language_info","codemirror_mode" }, "version", JsonBase::eType::number, variant<string, double, JsonBase::eSimple>(3));
		tmp_json_object.set({ "metadata", "language_info" }, "file_extension", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>(".py"));
		tmp_json_object.set({ "metadata", "language_info" }, "mimetype", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("text/x-python"));
		tmp_json_object.set({ "metadata", "language_info" }, "name", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("python"));
		tmp_json_object.set({ "metadata", "language_info" }, "nbconvert_exporter", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("python"));
		tmp_json_object.set({ "metadata", "language_info" }, "pygments_lexer", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("ipython3"));
		tmp_json_object.set({ "metadata", "language_info" }, "version", JsonBase::eType::string, variant<string, double, JsonBase::eSimple>("3.6.3"));
		tmp_json_object.set({}, "nbformat", JsonBase::eType::number, variant<string, double, JsonBase::eSimple>(4));
		tmp_json_object.set({}, "nbformat_mirror", JsonBase::eType::number, variant<string, double, JsonBase::eSimple>(2));

		cout << tmp_json_object.to_string("", true, false) << endl;

		//cout << path_ << endl;

		//std::ofstream fout(path_);
		//fout << tmp_json_object.to_string("", true, false);
		//fout.close();

		//std::wofstream fout(path_);
		//std::wstring s = L"Hello Привет world";
		//std::wcout << s << std::endl;
		//fout << s;
		//fout.close();

//#include <fstream>
//#include <iostream>
//#include <codecvt>
//#include <locale>
//#include <fcntl.h>
//#include <io.h>
//
//		int main()
//		{
//
//			const std::locale utf8_locale = std::locale(std::locale(),
//				new std::codecvt_utf8<wchar_t>());
//			{
//				std::wofstream test_file("c:\\temp\\test.txt");
//				test_file.imbue(utf8_locale);
//				test_file << L"\u2122";
//			}
//
//			_setmode(_fileno(stdout), _O_U8TEXT);
//			std::wcout << L"\u2122";
//		}

		const std::locale utf8_locale = std::locale(std::locale(), 
			new std::codecvt_utf8<wchar_t>());

		test_class tc(L"Hello Привет world ###Общее\n");


		std::wofstream file(path_);
		file.imbue(utf8_locale);
		file << tc.get();
		//file << tmp_json_object.to_string("", true, false);
		file.close();

		//string tmp = tmp_json_object.to_string("", true, false);
		//std::wstring ws(tmp.begin(), tmp.end());
		//std::wcout << ws << endl;

	}
#endif
}
#endif
