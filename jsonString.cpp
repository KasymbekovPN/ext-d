#include "jsonString.h"

JsonString::JsonString(): JsonItem()
{
	cout << ".ctor JsonString()" << endl;
}

JsonString::JsonString(const string & value_): JsonItem(), m_value(value_)
{
	cout << ".ctor JsonString(string)" << endl;
}

JsonString::JsonString(const string & value_, const string & name_): JsonItem(name_), m_value(value_)
{
	cout << ".ctor JsonString(string, string)" << endl;
}

JsonString::~JsonString()
{
}

void JsonString::set(const string & value_)
{
	m_value = value_;
}

string JsonString::get() const
{
	return m_value;
}

void JsonString::test() const
{
	cout << "Class JsonString" << endl;
	cout << "Name : " << getName() << endl;
	cout << "Value : " << m_value << endl;
}
