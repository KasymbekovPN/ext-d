#include "jsonArray.hpp"

JsonArray::JsonArray(const wstring & content_, const wstring & name_, shared_ptr<ErrorStatus> p_error_)
	:JsonBase(JsonBase::eType::array, name_, p_error_)
{

	wstring filtred_content = StringHandler::filter<wstring, wchar_t>(content_, StringHandler::FBE::begin_and_end, { L' ', L'\t', L'\n' });
	if (L'[' != filtred_content[0] || L']' != filtred_content[filtred_content.size() - 1]) {
		p_error->set(ErrorStatus::error::json_objectInvalid, true);
		return;
	}

	size_t brack_counter = 0;
	size_t sqr_counter = 0;
	wstring tmp;
	size_t item_counter = 0;
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

		if ((0 == brack_counter && 0 == sqr_counter && L',' == filtred_content[i]) ||
			i == filtred_content.size() - 2)
		{

			if (i == filtred_content.size() - 2) { tmp += filtred_content[i]; }

			wstring name = m_name + L"_" + std::to_wstring(item_counter++);
			wstring value = StringHandler::filter<wstring, wchar_t>(tmp, StringHandler::FBE::begin_and_end, { L' ', L'\t', L'\n' });

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
				//cout << 4 << endl;
			}

			tmp.clear();
		}
		else {
			tmp += filtred_content[i];
		}
	}
}


JsonArray::JsonArray(const wstring & name)
{
	m_name = name;
	m_type = JsonBase::eType::array;
	m_lists.clear();
}

JsonArray::~JsonArray()
{
	for (auto p : m_lists) {
		delete p;
	}
}

void JsonArray::show(wstring offset) const
{
	JsonBase::show(offset);
	std::wcout << offset << L"[\n";
	for (auto i : m_lists) {
		i->show(offset + L'\t');
	}
	std::wcout << offset << L"]\n";
}

void JsonArray::set(vector<wstring> path_, const wstring & name_, JsonBase::eType type_, std::variant<wstring, double, JsonBase::eSimple> arg_)
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

#ifdef  TASK_3_0__1
void JsonArray::reset(vector<wstring> path_, variant<wstring, double, JsonBase::eSimple> content_)
{
	if (!path_.empty()) {
		for (auto iter : m_lists) {
			if (path_[0] == iter->Name()) {
				vector<wstring> new_path;
				std::copy(path_.begin() + 1, path_.end(), std::inserter(new_path, new_path.begin()));
				iter->reset(new_path, content_);
			}
		}
	}
}
#endif

variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> JsonArray::get(vector<wstring> path_, eType * type_) const
{
	variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> res;

	if (0 == path_.size()) {
		*type_ = m_type;
		res = JsonBase::eGetterMsg::is_array;
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
	res = JsonBase::eGetterMsg::is_array;
	return res;
}

wstring JsonArray::to_string(const wstring & offset_, bool without_name_, bool end_with_comma_) const
{
	wstring res = offset_;
	if (false == without_name_) {
		res += L"\"" + m_name + L"\" : ";
	}
	res += L"[\n";
	for (size_t i = 0; i < m_lists.size(); ++i) {
		res += m_lists[i]->to_string(offset_ + L' ', true, i < m_lists.size() - 1);
	}

	res += offset_ + (end_with_comma_ ? L"],\n" : L"]\n");

	return res;
}
