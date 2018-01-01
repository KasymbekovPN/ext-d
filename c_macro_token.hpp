#pragma once

#include <iostream>
#include <string>

#include "c_base_token.hpp"
#include "stringHandler.h"

class cMacroToken : public cBaseToken
{
public:
	cMacroToken(const string& buffer);

	void show() const;

private:

	string m_value;
};