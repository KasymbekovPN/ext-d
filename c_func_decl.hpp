#pragma once

#include "stringHandler.h"
#include "c_base_token.hpp"

#include <iostream>
#include <string>

class cFuncDecl : public cBaseToken
{
public:
	cFuncDecl(const string& buffer);
	~cFuncDecl();

	void show(int offset_) const;

	void write(const string & dir_, const string & file_name_);

private:

	string m_dataType;
	string m_args;
};