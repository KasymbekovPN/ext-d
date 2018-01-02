#pragma once

#include "c_base_token.hpp"
#include "stringHandler.h"

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class cDefVar: public  cBaseToken
{
public:
	cDefVar(const string& buffer);

	void show() const;

private:

	bool m_static;
	bool m_const;
	bool m_extern;
	bool m_volatile;

	string m_dataType;
	string m_initValue;

};
