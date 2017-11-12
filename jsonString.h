#pragma once

#include "jsonItem.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class JsonString: public JsonItem
{
public:
	JsonString();
	JsonString(const string&);
	JsonString(const string&, const string&);
	virtual ~JsonString();

	void set(const string&);
	string get() const;
	
	virtual void test() const;

private:

	string m_value;

};