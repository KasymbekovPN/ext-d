#include "jsonBase.hpp"

#ifdef  TASK_0_2_5__4
JsonBase::JsonBase(JsonBase::eType type_, const wstring& name_, shared_ptr<ErrorStatus> error_)
	: m_type(type_), m_name(name_), p_error(error_)
{
}
#else
JsonBase::JsonBase(JsonBase::eType type_, const string& name_, shared_ptr<ErrorStatus> error_)
	: m_type(type_), m_name(name_), p_error(error_)
{
}
#endif

#ifdef TASK_0_2_5__1
JsonBase::JsonBase()
{
}
#endif

JsonBase::~JsonBase()
{
	//cout << "del base" << endl;
}

#ifdef  TASK_0_2_5__4
variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> JsonBase::get(vector<wstring> path_, eType * type_) const
{
	*type_ = JsonBase::eType::base;
	variant<eSimple, double, wstring, eGetterMsg> result;
	result = eGetterMsg::is_base;

	return result;
}
#else
variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> JsonBase::get(vector<string> path_, eType * type_) const
{
	*type_ = JsonBase::eType::base;
	variant<eSimple, double, string, eGetterMsg> result;
	result = eGetterMsg::is_base;
		
	return result;
}
#endif

#ifdef  TASK_0_2_5__4
void JsonBase::show(wstring offset) const
{
	std::wcout << offset << m_name << L" : ";
}
#else
void JsonBase::show(string offset) const
{
	cout << offset << m_name << " : ";
}
#endif

#ifdef  TASK_0_2_5__4
void JsonBase::set(vector<wstring> path_, const wstring & name_, JsonBase::eType type_, std::variant<wstring, double, JsonBase::eSimple> arg_)
{
}
#else
void JsonBase::set(vector<string> path_, const string & name_, JsonBase::eType type_, std::variant<string, double, JsonBase::eSimple> arg_)
{
}
#endif

#ifdef  TASK_0_2_5
#ifdef  TASK_0_2_5__4
wstring JsonBase::to_string(const wstring & offset_, bool without_name_, bool end_with_comma_) const
{
	return wstring();
}
#else
string JsonBase::to_string(const string & offset_, bool without_name_, bool end_with_comma_) const
{
	return string();
}
#endif
#endif

#ifdef  TASK_0_2_5__4
wstring JsonBase::Name() const
{
	return m_name;
}
#else
string JsonBase::Name() const
{
	return m_name;
}
#endif


