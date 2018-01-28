#include "jsonBase.hpp"


JsonBase::JsonBase(JsonBase::eType type_, const string& name_, shared_ptr<ErrorStatus> error_)
	: m_type(type_), m_name(name_), p_error(error_)
{
}

JsonBase::~JsonBase()
{
}

variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> JsonBase::get(vector<string> path_, eType * type_) const
{
	*type_ = JsonBase::eType::base;
	variant<eSimple, double, string, eGetterMsg> result;
	result = eGetterMsg::is_base;
		
	return result;
}

void JsonBase::show(string offset) const
{
	cout << offset << m_name << " : ";
}

string JsonBase::to_string(const string & offset_) const
{
	return string();
}

string JsonBase::Name() const
{
	return m_name;
}


