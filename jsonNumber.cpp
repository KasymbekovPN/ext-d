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

	//cout << int(m_type) << " : " << m_name << endl;

	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> res;
	*type_ = m_type;
	res = m_content;
	return res;
}
