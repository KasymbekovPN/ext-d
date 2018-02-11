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

	virtual void write(const string & dir_, const string & file_name_, const string& mode_) override;

private:

	string m_value;
};