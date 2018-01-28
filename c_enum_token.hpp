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
	~cEnumToken();

	void show(int offset_) const;

#ifdef  TASK_0_2_5
	virtual void write(const string & dir_, const string & file_name_, const string& mode_) override;
#else
	void write(const string & dir_, const string & file_name_);
#endif

private:

	vector<vector<string>> m_value;

};