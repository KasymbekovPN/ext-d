#include "c_def_var_token.hpp"

cDefVar::cDefVar(const string& buffer): cBaseToken(cBaseToken::TokenType::def_var)
{
	cout << buffer << endl;
}

void cDefVar::show() const
{
	cBaseToken::show();
}
