#include "jsonObject.hpp"

JsonObject::JsonObject(const wstring & content_, const wstring& name_, shared_ptr<ErrorStatus> error_)
	: JsonBase(JsonBase::eType::object, name_, error_)
{

	wstring filtred_content = StringHandler::filter<wstring, wchar_t>(content_, StringHandler::FBE::begin_and_end, { L' ', L'\t', L'\n' });

	if (L'{' != filtred_content[0] || L'}' != filtred_content[filtred_content.size() - 1]) {
		cout << "obj" << endl;
		p_error->set(ErrorStatus::error::json_objectInvalid, true);
		return;
	}

	size_t brack_counter = 0;
	size_t sqr_counter = 0;
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
			if (wstring::npos != found_dots) 
			{

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

JsonObject::JsonObject(const wstring & name_)
{
	m_type = JsonBase::eType::object;
	m_name = name_;
	m_lists.clear();
}

JsonObject::~JsonObject()
{
	for (auto p : m_lists) {
		delete p;
	}
}

void JsonObject::show(wstring offset) const
{
	JsonBase::show(offset);
	std::wcout << offset << L"{\n";
	for (auto i : m_lists) {
		i->show(offset + L'\t');
	}
	std::wcout << offset << L"}\n";
}

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

void JsonObject::reset(vector<wstring> path_, variant<wstring, double, JsonBase::eSimple> content_)
{
	if (!path_.empty()) {

		for (auto iter : m_lists) {
			vector<wstring> new_path;
			std::copy(path_.begin() + 1, path_.end(), std::inserter(new_path, new_path.begin()));
			iter->reset(new_path, content_);
		}
	}
}

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

wstring JsonObject::to_string(const wstring & offset_, bool without_name_, bool end_with_comma_) const
{
	wstring res = offset_;
	if (false == without_name_) {
		res += L"\"" + m_name + L"\" : ";
	}
	res += L"{\n";
	for (size_t i = 0; i < m_lists.size(); ++i) {
		res += m_lists[i]->to_string(offset_ + L' ', false, i < m_lists.size() - 1);
	}
	res += offset_ + (end_with_comma_ ? L"},\n" : L"}\n");

	return res;
}


void JsonObject::write(const string & path_, const string & mode_)
{
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

		size_t found = path_.find_last_of("\\");
		if (string::npos != found) {
			string dir_path = path_.substr(0, found);
			if (false == std::experimental::filesystem::exists(dir_path)) {
				std::experimental::filesystem::create_directory(dir_path);
			}
		}

		if (!std::experimental::filesystem::exists(path_)) {
			const std::locale utf8_locale = std::locale(std::locale(),
				new std::codecvt_utf8<wchar_t>());

			std::wofstream fout(path_);
			fout.imbue(utf8_locale);
			std::wstring s = to_string(L"", true, false);
			fout << s;
			fout.close();
		}

	}
}

void JsonObject::write(const string & path_, const string & mode_, bool rewrite_)
{
	//
	// Только для режима "ipynb"
	//
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
	}

	//
	// Для режимов "json" и "ipynb"
	//
	if ("ipynb" == mode_ || "json" == mode_ || "" == mode_) {

		//
		// Существует ли директория, если не существует, то создаем.
		//
		size_t found = path_.find_last_of("\\");
		if (string::npos != found) {
			string dir_path = path_.substr(0, found);
			if (false == std::experimental::filesystem::exists(dir_path)) {
				std::experimental::filesystem::create_directory(dir_path);
			}
		}

		//
		// Файл записывается, он не существует или требуется перезапись
		//
		if (!std::experimental::filesystem::exists(path_) || rewrite_) {
			const std::locale utf8_locale = std::locale(std::locale(),
				new std::codecvt_utf8<wchar_t>());

			std::wofstream fout(path_);
			fout.imbue(utf8_locale);
			std::wstring s = to_string(L"", true, false);
			fout << s;
			fout.close();
		}
	}
}
