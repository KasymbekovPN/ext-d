#pragma once

#include "stringHandler.h"
#include "c_base_token.hpp"
#include "c_def_var_token.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using std::vector;
using std::string;
using std::cout;
using std::endl;

class cStructToken: public cBaseToken
{
public:
	cStructToken(const string& buffer);
	~cStructToken();

	void show(int offset_) const;

#ifdef  TASK_0_2_5
	virtual void write(const string & dir_, const string & file_name_, const string& mode_) override;
#else
	void write(const string & dir_, const string & file_name_);
#endif	

#ifdef TASK_0_2_5__6
	virtual vector<string> parse_members(bool root_, const string& patern_name_) override;
#endif

protected:

private:

	bool m_typedef;
	bool m_array;
	string m_array_size;
	
	vector<cBaseToken*> m_value;

	void toRst(string* p_members, bool root_, const string& patern_name_);


};