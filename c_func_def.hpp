#pragma once

#include "stringHandler.h"
#include "c_base_token.hpp"

#include <iostream>
#include <string>

class cFuncDef: public cBaseToken
{
public:
	cFuncDef(const string& buffer);

	void show(int offset_) const;

private:

	string m_dataType;
	string m_args;
	string m_value;

};