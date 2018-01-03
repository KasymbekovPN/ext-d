#pragma once

#include "stringHandler.h"
#include "c_base_token.hpp"

#include <iostream>
#include <string>

class cFuncDecl : public cBaseToken
{
public:
	cFuncDecl(const string& buffer);

	void show(int offset_) const;

private:

	string m_value;

};