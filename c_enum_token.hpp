#pragma once 

#include "c_base_token.hpp"
#include "stringHandler.h"

#include <string>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class cEnumToken : public cBaseToken
{
public:
	cEnumToken(const string& buffer);

	void show(int offset_) const;

private:

	vector<vector<string>> m_value;

};