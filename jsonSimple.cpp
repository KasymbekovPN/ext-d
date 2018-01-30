#include "jsonSimple.hpp"

JsonSimple::JsonSimple(JsonBase::eSimple content_, const string & name_, shared_ptr<ErrorStatus> p_error_)
	:JsonBase(JsonBase::eType::simple, name_, p_error_), m_content(content_)
{
}

#ifdef  TASK_0_2_5__1
JsonSimple::JsonSimple(const string & name_, JsonBase::eSimple content_)
{
	m_name = name_;
	m_content = content_;
	m_type = JsonBase::eType::simple;
}
#endif

JsonSimple::~JsonSimple()
{
}

void JsonSimple::show(string offset) const
{
	JsonBase::show(offset);
	cout << int(m_content) << endl;
}

variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> JsonSimple::get(vector<string> path, JsonBase::eType * type_) const
{
	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> res;
	*type_ = m_type;
	res = m_content;
	return res;
}

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
