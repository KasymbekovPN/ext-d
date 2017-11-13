#pragma once

#include <string>
#include <sstream>
#include <iostream>

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

enum class SimpleType {Null, True, False};

template <class T>
class JsonItem
{
public:
	JsonItem(const T&);
	JsonItem(const T&, const string&);
	
	T get() const;
	string getName() const;

private:

	T m_value;
	string m_name;
};

//template <class T>
//JsonItem::JsonItem(const T& value)
//{
//}
//
//template <class T>
//JsonItem::JsonItem(const T& value, const string& name)
//{
//}

template<class T>
inline JsonItem<T>::JsonItem(const T & value_) : m_value(value_), m_name("noname")
{
}

template<class T>
inline JsonItem<T>::JsonItem(const T & value_, const string & name_): m_value(value_), m_name(name_)
{
}

template<class T>
inline T JsonItem<T>::get() const
{
	return m_value;
}

template<class T>
inline string JsonItem<T>::getName() const
{
	return m_name;
}

//class JsonItem
//{
//public:
//	JsonItem();
//	JsonItem(const string&);
//	virtual ~JsonItem();
//
//	void setName(const string&);
//	string getName() const;
//	virtual int getID() const;
//
//	virtual void test() const;
//	virtual int get() const;
//	virtual void set(int);
//
//private:
//
//	static int m_itemCounter;
//	string m_name;
//};