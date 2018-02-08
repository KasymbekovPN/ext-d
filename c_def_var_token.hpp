#pragma once

#include "c_base_token.hpp"
#include "stringHandler.h"
#include "jsonObject.hpp"

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class cDefVar: public  cBaseToken
{
public:
	cDefVar(const string& buffer);
	~cDefVar();

	void show(int offset_) const;

#ifdef TASK_0_2_5
	virtual void write(const string & dir_, const string & file_name_, const string& mode_) override;
#else
	void write(const string & dir_, const string & file_name_);
#endif // TASK_0_2_5	

private:

	bool m_struct;
	bool m_typedef;
	bool m_array;
	bool m_function_pointer;
	string m_pfunc_arg;
	string m_array_size;

	string m_dataType;
	string m_initValue;

};
