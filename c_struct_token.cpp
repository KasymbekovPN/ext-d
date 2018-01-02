#include "c_struct_token.hpp"

cStructToken::cStructToken(const string & buffer): cBaseToken(cBaseToken::TokenType::typedef_struct)
{
	cout << "-" << endl;
	cout << buffer << endl;
	cout << "-" << endl;
}

void cStructToken::show() const
{
}
