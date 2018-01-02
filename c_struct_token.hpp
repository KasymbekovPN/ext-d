#pragma once

#include "stringHandler.h"
#include "c_base_token.hpp"
#include "c_def_var_token.hpp"

#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class cStructToken: public cBaseToken
{
public:
	cStructToken(const string& buffer);

	void show() const;

private:

	string m_volatile;
	vector<cBaseToken*> m_value;

};