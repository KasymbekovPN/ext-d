#include "jsonString.hpp"

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


JsonString::~JsonString()
{
}

void JsonString::show(string offset) const
{
	JsonBase::show(offset);
	cout << "\"" << m_content << "\"" << endl;
}

variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> JsonString::get(vector<string> path_, JsonBase::eType * type_) const
{
	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> res;
	*type_ = m_type;
	res = m_content;
	return res;
}

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
