#include "jsonString.hpp"

JsonString::JsonString(const string & content_, const string & name_, shared_ptr<ErrorStatus> p_error_)
	:JsonBase(JsonBase::eType::string, name_, p_error_), m_content(content_)
{
	//cout << "-" << endl;
	//cout << "Type String" << endl;
	//cout << m_name << endl;
	//cout << m_content << endl;
	//cout << "-" << endl;
}


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
	//cout << int(m_type) << " : " << m_name << endl;
	//--
	//cout << "[";
	//for (auto i : path_) {
	//	cout << i << ", ";
	//}
	//cout << "]" << endl;
	//--

	variant<JsonBase::eSimple, double, string, JsonBase::eGetterMsg> res;
	*type_ = m_type;
	res = m_content;
	return res;
}
