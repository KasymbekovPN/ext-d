#pragma once

#include "stringHandler.h"
#include "c_base_token.hpp"
#include "jsonObject.hpp"

#include <iostream>
#include <string>
#include <Windows.h>
#include <wchar.h>

class cFuncDef: public cBaseToken
{
public:
	cFuncDef(const string& buffer);
	~cFuncDef();

	void show(int offset_) const;
#ifdef  TASK_3_0__1
	virtual void write(const string & dir_, const string & file_name_, const string& mode_, vector<std::experimental::filesystem::path>* file_paths_) override;
#else
	virtual void write(const string & dir_, const string & file_name_, const string& mode_) override;
#endif

private:

	string m_dataType;
	string m_args;
	string m_value;

};