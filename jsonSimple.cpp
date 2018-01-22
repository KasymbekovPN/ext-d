#include "jsonSimple.hpp"

JsonSimple::JsonSimple(JsonBase::eSimple content_, const string & name_, shared_ptr<ErrorStatus> p_error_)
	:JsonBase(JsonBase::eType::simple, name_, p_error_), m_content(content_)
{
}

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
