#include "jsonString.hpp"

JsonString::JsonString(const wstring & content_, const wstring & name_, shared_ptr<ErrorStatus> p_error_)
	:JsonBase(JsonBase::eType::string, name_, p_error_), m_content(content_)
{
}

JsonString::JsonString(const wstring & name_, const wstring & content_)
{
	m_name = name_;
	m_content = content_;
	m_type = JsonBase::eType::string;
}

JsonString::~JsonString()
{
}

void JsonString::show(wstring offset) const
{
	JsonBase::show(offset);
	std::wcout << L"\"" << m_content << L"\"" << endl;
}

variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> JsonString::get(vector<wstring> path_, JsonBase::eType * type_) const
{
	variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> res;
	*type_ = m_type;
	res = m_content;
	return res;
}

wstring JsonString::to_string(const wstring & offset_, bool without_name_, bool end_with_comma_) const
{
	wstring res = offset_;
	if (false == without_name_) {
		res += L"\"" + m_name + L"\" : ";
	}
	res += L"\"" + m_content + L"\"";
	res += end_with_comma_ ? L",\n" : L"\n";

	return res;
}