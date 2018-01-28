#pragma once

#include <iostream>
#include <string>

#include "c_base_token.hpp"
#include "stringHandler.h"
#ifdef  TASK_0_2_5
#include "jsonObject.hpp"
#endif

class cMacroToken : public cBaseToken
{
public:
	cMacroToken(const string& buffer);
	~cMacroToken();

	void show(int offset_) const;

#ifdef  TASK_0_2_5
	virtual void write(const string & dir_, const string & file_name_, const string& mode_) override;
#else
	void write(const string & dir_, const string & file_name_);
#endif

private:

	string m_value;
};