#include "c_func_decl.hpp"

cFuncDecl::cFuncDecl(const string & buffer): cBaseToken(cBaseToken::TokenType::func_decl, buffer)
{
}

void cFuncDecl::show(int offset_) const
{
	cBaseToken::show(offset_);
}
