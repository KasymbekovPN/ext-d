#include "jsonNumber.hpp"

JsonNumber::JsonNumber(const wstring & content_, const wstring & name_, shared_ptr<ErrorStatus> p_errro_)
	:JsonBase(JsonBase::eType::number, name_, p_errro_)
{
	try
	{
		m_content = std::stod(content_);
	}
	catch (const std::invalid_argument&)
	{
		p_error->set(ErrorStatus::error::json_invalidSyntax, true);
	}
}

JsonNumber::JsonNumber(const wstring & name_, double content_)
{
	m_name = name_;
	m_content = content_;
	m_type = JsonBase::eType::number;
}

JsonNumber::~JsonNumber()
{
}

void JsonNumber::show(wstring offset) const
{
	JsonBase::show(offset);
	cout << m_content << endl;
}

#ifdef  TASK_3_0__1
void JsonNumber::reset(vector<wstring> path_, variant<wstring, double, JsonBase::eSimple> content_)
{
	if (path_.empty()) {
		double tmp = 0;
		try {
			tmp = std::get<double>(content_);
		}
		catch (std::bad_variant_access&) {
			tmp = 0;
		}
		m_content = tmp;
	}
}
#endif

variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> JsonNumber::get(vector<wstring> path_, eType * type_) const
{
	variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> res;
	*type_ = m_type;
	res = m_content;
	return res;
}

wstring JsonNumber::to_string(const wstring & offset_, bool without_name_, bool end_with_comma_) const
{
	wstring res = offset_;
	if (false == without_name_) {
		res += L"\"" + m_name + L"\" : ";
	}

	wstring number = std::to_wstring(m_content);
	size_t find = number.find(L',');

	if (wstring::npos != find) {
		if (0 == m_content - int(m_content)) {
			number = number.substr(0, find);
		}
		else {
			wstring::reverse_iterator it = number.rbegin();
			for (; it != number.rend() && ('0' == *it); ++it);
			number.erase(it.base(), number.end());
		}
	}

	res += StringHandler::replace_all<wstring, wchar_t>(number, ',', '.') + (end_with_comma_ ? L",\n" : L"\n");

	return res;
}