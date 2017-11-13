//#include "jsonSimple.h"
//
//JsonSimple::JsonSimple(): JsonItem(), m_value(simpleNill)
//{
//	cout << ".ctor JsomSimple()" << endl;
//}
//
//JsonSimple::JsonSimple(SimpleType value_): JsonItem()
//{
//	set(value_);
//	cout << ".ctor JsonSimple(SimpleType)" << endl;
//}
//
//JsonSimple::JsonSimple(SimpleType value_, const string & name_): JsonItem(name_)
//{
//	set(value_);
//	cout << ".ctor JsonSimple(SimpleType, string)" << endl;
//}
//
//JsonSimple::~JsonSimple()
//{
//}
//
//void JsonSimple::test() const
//{
//	cout << "Class JsonSimple" << endl;
//	cout << "Name : " << getName() << endl;
//	cout << "Value : " << m_value << endl;
//}
//
//JsonSimple::SimpleType JsonSimple::get() const
//{
//	return m_value;
//}
//
//void JsonSimple::set(SimpleType value_)
//{
//	m_value = value_ >= simpleSIZE ? simpleNill : value_;
//}
