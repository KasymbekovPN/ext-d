#include "jsonBase.hpp"

JsonBase::JsonBase(JsonBase::eType type_, const wstring& name_, shared_ptr<ErrorStatus> error_)
	: m_type(type_), m_name(name_), p_error(error_)
{
}

JsonBase::JsonBase()
{
}

JsonBase::~JsonBase()
{
}

void JsonBase::reset(vector<wstring> path_, variant<wstring, double, JsonBase::eSimple> content_)
{
}

variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> JsonBase::get(vector<wstring> path_, eType * type_) const
{
	*type_ = JsonBase::eType::base;
	variant<eSimple, double, wstring, eGetterMsg> result;
	result = eGetterMsg::is_base;

	return result;
}

void JsonBase::show(wstring offset) const
{
	std::wcout << offset << m_name << L" : ";
}

void JsonBase::set(vector<wstring> path_, const wstring & name_, JsonBase::eType type_, std::variant<wstring, double, JsonBase::eSimple> arg_)
{
}

wstring JsonBase::to_string(const wstring & offset_, bool without_name_, bool end_with_comma_) const
{
	return wstring();
}

wstring JsonBase::Name() const
{
	return m_name;
}


