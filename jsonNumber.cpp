#include "jsonNumber.hpp"

JsonNumber::JsonNumber(const string & content_, const string & name_, shared_ptr<ErrorStatus> p_errro_)
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

#ifdef  TASK_0_2_5__1
JsonNumber::JsonNumber(const string & name_, double content_)
{
	m_name = name_;
	m_content = content_;
	m_type = JsonBase::eType::number;
}
#endif

JsonNumber::~JsonNumber()
{
}

void JsonNumber::show(string offset) const
{
	JsonBase::show(offset);
	cout << m_content <<  endl;
}

variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> JsonNumber::get(vector<string> path_, eType * type_) const
{
	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> res;
	*type_ = m_type;
	res = m_content;
	return res;
}

#ifdef TASK_0_2_5
string JsonNumber::to_string(const string & offset_, bool without_name_, bool end_with_comma_) const
{
	string res = offset_;
	if (false == without_name_) {
		res += "\"" + m_name + "\" : ";
	}

	string number = std::to_string(m_content);
	size_t find = number.find(',');

	if (string::npos != find) {
		if (0 == m_content - int(m_content)) {
			number = number.substr(0, find);
		}
		else {
			string::reverse_iterator it = number.rbegin();
			for (; it != number.rend() && ('0' == *it); ++it);
			number.erase(it.base(), number.end());
		}
	}

	res += StringHandler::replace_all(number, ',', '.') + (end_with_comma_ ? ",\n" : "\n");

	return res;
}
#endif
