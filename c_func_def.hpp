#pragma once

#include "stringHandler.h"
#include "c_base_token.hpp"

#include <iostream>
#include <string>

class cFuncDef: public cBaseToken
{
public:
	cFuncDef(const string& buffer);
	~cFuncDef();

	void show(int offset_) const;

	void write(const string & dir_, const string & file_name_);

private:

	string m_dataType;
	string m_args;
	string m_value;

};