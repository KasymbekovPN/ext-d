#pragma once

#include <iostream>
#include <string>

#include "tokens/c_base_token.hpp"
#include "stringHandler.h"
#include "json/jsonObject.hpp"

class cMacroToken : public cBaseToken
{
public:
	cMacroToken(const string& buffer);
	~cMacroToken();

	void show(int offset_) const;

	virtual void write(const string & dir_, const string & file_name_, const string& mode_, vector<std::experimental::filesystem::path>* file_paths_) override;

private:

	string m_value;
};
