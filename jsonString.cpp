#include "jsonString.hpp"

#ifdef  TASK_0_2_5__4
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
#else
JsonString::JsonString(const string & content_, const string & name_, shared_ptr<ErrorStatus> p_error_)
	:JsonBase(JsonBase::eType::string, name_, p_error_), m_content(content_)
{
}

#ifdef  TASK_0_2_5__1
JsonString::JsonString(const string & name_, const string & content_)
{
	m_name = name_;
	m_content = content_;
	m_type = JsonBase::eType::string;
}
#endif
#endif

JsonString::~JsonString()
{
	//cout << "del string" << endl;
}

#ifdef  TASK_0_2_5__4
void JsonString::show(wstring offset) const
{
	JsonBase::show(offset);
	std::wcout << L"\"" << m_content << L"\"" << endl;
}
#else
void JsonString::show(string offset) const
{
	JsonBase::show(offset);
	cout << "\"" << m_content << "\"" << endl;
}
#endif

#ifdef  TASK_0_2_5__4
variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> JsonString::get(vector<wstring> path_, JsonBase::eType * type_) const
{
	variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> res;
	*type_ = m_type;
	res = m_content;
	return res;
}
#else
variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> JsonString::get(vector<string> path_, JsonBase::eType * type_) const
{
	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> res;
	*type_ = m_type;
	res = m_content;
	return res;
}
#endif

#ifdef  TASK_0_2_5__4
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
#else
#ifdef  TASK_0_2_5
string JsonString::to_string(const string & offset_, bool without_name_, bool end_with_comma_) const
{
	string res = offset_;
	if (false == without_name_) {
		res += "\"" + m_name + "\" : ";
	}
	res += "\"" + m_content + "\"";
	res += end_with_comma_ ? ",\n" : "\n";

	return res;
}
#endif
#endif
