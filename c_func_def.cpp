#include "c_func_def.hpp"

cFuncDef::cFuncDef(const string & buffer): cBaseToken(cBaseToken::TokenType::func_def, buffer)
{
	//cout << "---func-def---" << endl;
	//cout << buffer << endl;
}

void cFuncDef::show(int offset_) const
{
	cBaseToken::show(offset_);
}
