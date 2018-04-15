#pragma once 

#include "tokens/c_base_token.hpp"
#include "stringHandler.h"
#include "json/jsonObject.hpp"

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
	virtual void write(const string & dir_, const string & file_name_, const string& mode_, vector<std::experimental::filesystem::path>* file_paths_) override;

private:

	vector<vector<string>> m_value;

};
