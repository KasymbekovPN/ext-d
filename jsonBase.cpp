#include "jsonBase.hpp"


JsonBase::JsonBase(JsonBase::eType type_, const string& name_, shared_ptr<ErrorStatus> error_)
	: m_type(type_), m_name(name_), p_error(error_)
{
}

#ifdef TASK_0_2_5__1
JsonBase::JsonBase()
{
}
#endif

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

void JsonBase::set(vector<string> path_, const string & name_, JsonBase::eType type_, std::variant<string, double, JsonBase::eSimple> arg_)
{
}

#ifdef  TASK_0_2_5
string JsonBase::to_string(const string & offset_, bool without_name_, bool end_with_comma_) const
{
	return string();
}
#endif

string JsonBase::Name() const
{
	return m_name;
}


