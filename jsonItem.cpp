//#include "jsonItem.h"
//
//int JsonItem::m_itemCounter = 0;
//
//JsonItem::JsonItem()
//{
//	cout << "----" << endl;
//	stringstream ss;
//	ss << m_itemCounter;
//	m_name = "noname_" + ss.str();
//	m_itemCounter++;
//
//	cout << ".ctor JsonItem() " << endl;
//}
//
//JsonItem::JsonItem(const string & name_): m_name(name_)
//{
//	m_itemCounter++;
//	cout << "----" << endl;
//	cout << ".ctor JsonItem(int) " << endl;
//}
//
//JsonItem::~JsonItem()
//{
//	m_itemCounter--;
//	cout << ".dtor JsonItem() " << endl;
//	cout << "----" << endl;
//}
//
//void JsonItem::setName(const string & name_)
//{
//	m_name = name_;
//}
//
//string JsonItem::getName() const
//{
//	return m_name;
//}
//
//int JsonItem::getID() const
//{
//	return m_itemCounter;
//}
//
//void JsonItem::test() const
//{
//	cout << "Class JsonItem" << endl;
//	cout << "Name : " << m_name;
//}
//
//int JsonItem::get() const
//{
//	return 0;
//}
//
//void JsonItem::set(int)
//{
//}
