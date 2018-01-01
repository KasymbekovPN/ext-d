#pragma once 

#include "c_base_token.hpp"
#include "stringHandler.h"

#include <string>
//#include <map>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
//using std::map;
using std::string;
using std::vector;

class cEnumToken : public cBaseToken
{
public:
	cEnumToken(const string& buffer);

	void show() const;

private:

	vector<vector<string>> m_value;

};