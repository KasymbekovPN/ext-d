#pragma once

#include <iostream>
#include <string>

#include "c_base_token.hpp"
#include "stringHandler.h"

class cMacroToken : public cBaseToken
{
public:
	cMacroToken(const string& buffer);

	void show(int offset_) const;

	void write(const string & dir_, const string & file_name_);

private:

	string m_value;
};