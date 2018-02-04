#include "jsonSimple.hpp"

#ifdef  TASK_0_2_5__4
JsonSimple::JsonSimple(JsonBase::eSimple content_, const wstring & name_, shared_ptr<ErrorStatus> p_error_)
	:JsonBase(JsonBase::eType::simple, name_, p_error_), m_content(content_)
{
}
#else
JsonSimple::JsonSimple(JsonBase::eSimple content_, const string & name_, shared_ptr<ErrorStatus> p_error_)
	:JsonBase(JsonBase::eType::simple, name_, p_error_), m_content(content_)
{
}
#endif

#ifdef  TASK_0_2_5__4
JsonSimple::JsonSimple(const wstring & name_, JsonBase::eSimple content_)
{
	m_name = name_;
	m_content = content_;
	m_type = JsonBase::eType::simple;
}
#else
#ifdef  TASK_0_2_5__1
JsonSimple::JsonSimple(const string & name_, JsonBase::eSimple content_)
{
	m_name = name_;
	m_content = content_;
	m_type = JsonBase::eType::simple;
}
#endif
#endif

JsonSimple::~JsonSimple()
{
	//cout << "del simple" << endl;
}

#ifdef  TASK_0_2_5__4
void JsonSimple::show(wstring offset) const
{
	JsonBase::show(offset);
	cout << int(m_content) << endl;
}
#else
void JsonSimple::show(string offset) const
{
	JsonBase::show(offset);
	cout << int(m_content) << endl;
}
#endif

#ifdef  TASK_0_2_5__4
variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> JsonSimple::get(vector<wstring> path, JsonBase::eType * type_) const
{
	variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> res;
	*type_ = m_type;
	res = m_content;
	return res;
}
#else
variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> JsonSimple::get(vector<string> path, JsonBase::eType * type_) const
{
	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> res;
	*type_ = m_type;
	res = m_content;
	return res;
}
#endif

#ifdef  TASK_0_2_5__4
wstring JsonSimple::to_string(const wstring & offset_, bool without_name_, bool end_with_comma_) const
{
	wstring res = offset_;
	if (false == without_name_) {
		res += L"\"" + m_name + L"\" : ";
	}

	switch (m_content)
	{
	case JsonBase::eSimple::simple_false:
		res += L"false";
		break;
	case JsonBase::eSimple::simple_true:
		res += L"true";
		break;
	case JsonBase::eSimple::simple_null:
	default:
		res += L"null";
		break;
	}

	res += end_with_comma_ ? L",\n" : L"\n";

	return res;

}
#else
#ifdef  TASK_0_2_5
string JsonSimple::to_string(const string & offset_, bool without_name_, bool end_with_comma_) const
{
	string res = offset_;
	if (false == without_name_) {
		res += "\"" + m_name + "\" : ";
	}

	switch (m_content)
	{
	case JsonBase::eSimple::simple_false:
		res += "false";
		break;
	case JsonBase::eSimple::simple_true:
		res += "true";
		break;
	case JsonBase::eSimple::simple_null:
	default:
		res += "null";
		break;
	}

	res += end_with_comma_ ? ",\n" : "\n";

	return res;

}
#endif
#endif