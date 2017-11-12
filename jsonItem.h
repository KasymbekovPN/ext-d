#pragma once

#include <string>
#include <sstream>
#include <iostream>

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

class JsonItem
{
public:
	JsonItem();
	JsonItem(const string&);
	virtual ~JsonItem();

	void setName(const string&);
	string getName() const;
	virtual int getID() const;

	virtual void test() = 0;

private:

	static int m_itemCounter;
	string m_name;
};