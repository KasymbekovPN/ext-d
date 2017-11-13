//#include "jsonNumber.h"
//
//JsonNumber::JsonNumber(): JsonItem(), m_value(0) {
//	cout << ".ctor JsonNumber()" << endl;
//}
//
//JsonNumber::JsonNumber(int value_): JsonItem(), m_value(value_){
//	cout << ".ctor JsonNumber(int)" << endl;
//}
//
//JsonNumber::JsonNumber(int value, const string & name_): JsonItem(name_), m_value(value)
//{
//	cout << ".ctor JsonNumber(int, string)" << endl;
//}
//
//JsonNumber::~JsonNumber() {
//	cout << ".dtor JsonNumber()" << endl;
//}
//
//void JsonNumber::test() const
//{
//	cout << "Class JsonNumber" << endl;
//	cout << "Name : " << getName() << endl;
//	cout << "Value : " << m_value << endl;
//}
//
//int JsonNumber::get() const
//{
//	return m_value;
//}
//
//void JsonNumber::set(int value_)
//{
//	m_value = value_;
//}
