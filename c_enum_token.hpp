#pragma once 

#include "c_base_token.hpp"
#include "stringHandler.h"
#include "jsonObject.hpp"

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
#ifdef  TASK_3_0__1
	virtual void write(const string & dir_, const string & file_name_, const string& mode_, vector<std::experimental::filesystem::path>* file_paths_) override;
#else
	virtual void write(const string & dir_, const string & file_name_, const string& mode_) override;
#endif

private:

	vector<vector<string>> m_value;

};