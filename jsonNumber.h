#pragma once

#include "jsonItem.h"

#include <iostream>

using std::cout;
using std::endl;

class JsonNumber : public JsonItem
{
public:
	JsonNumber();
	JsonNumber(int);
	JsonNumber(int, const string&);
	virtual ~JsonNumber();

	virtual void test() const;

	int get() const;
	void set(int);

private:

	int m_value;

};