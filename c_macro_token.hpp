#pragma once

#include <iostream>
#include <string>

#include "c_base_token.hpp"
#include "stringHandler.h"
#include "jsonObject.hpp"

class cMacroToken : public cBaseToken
{
public:
	cMacroToken(const string& buffer);
	~cMacroToken();

	void show(int offset_) const;

#ifdef  TASK_3_0__1
	virtual void write(const string & dir_, const string & file_name_, const string& mode_, vector<std::experimental::filesystem::path>* file_paths_) override;
#else
	virtual void write(const string & dir_, const string & file_name_, const string& mode_) override;
#endif

private:

	string m_value;
};