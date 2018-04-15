#include "jsonSimple.hpp"

JsonSimple::JsonSimple(JsonBase::eSimple content_, const wstring & name_, shared_ptr<ErrorStatus> p_error_)
	:JsonBase(JsonBase::eType::simple, name_, p_error_), m_content(content_)
{
}

JsonSimple::JsonSimple(const wstring & name_, JsonBase::eSimple content_)
{
	m_name = name_;
	m_content = content_;
	m_type = JsonBase::eType::simple;
}

JsonSimple::~JsonSimple()
{
}

void JsonSimple::show(wstring offset) const
{
	JsonBase::show(offset);
	cout << int(m_content) << endl;
}

void JsonSimple::reset(vector<wstring> path_, variant<wstring, double, JsonBase::eSimple> content_)
{
	if (path_.empty()) {
		JsonBase::eSimple tmp;
		try {
			tmp = std::get<JsonBase::eSimple>(content_);
			m_content = tmp;
		}
		catch (std::bad_variant_access&) {
			tmp = JsonBase::eSimple::simple_null;
		}
		m_content = tmp;
	}
}

variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> JsonSimple::get(vector<wstring> path, JsonBase::eType * type_) const
{
	variant<JsonBase::eSimple, double, wstring, JsonBase::eGetterMsg> res;
	*type_ = m_type;
	res = m_content;
	return res;
}

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