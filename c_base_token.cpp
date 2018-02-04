#include "c_base_token.hpp"

cBaseToken::TokenTypeNames cBaseToken::tokenTypeNames = {
	{cBaseToken::TokenType::macro, "#define"},
	{cBaseToken::TokenType::typedef_enum, "enum"},
	{cBaseToken::TokenType::def_var, "var"},
	{cBaseToken::TokenType::typedef_struct, "struct"},
	{cBaseToken::TokenType::func_decl, "func-decl"},
	{cBaseToken::TokenType::func_def, "func-def"}
};

cBaseToken::cBaseToken(TokenType type_, const string& raw_): m_type(type_), m_raw(raw_), m_static(false), 
	m_const(false), m_extern(false), m_volatile(false) 
{

	string cln_raw = StringHandler::filter<string, char>(raw_, StringHandler::FBE::all, {' ', '\t', '\n', '\\'});

	std::hash<string> str_hash_fn;
	std::stringstream stream;
	stream << "0x" << std::setfill('0') << std::setw(2 * sizeof(size_t))
		<< std::hex << str_hash_fn(cln_raw);

	m_hash = stream.str();
}

cBaseToken::~cBaseToken()
{
}

void cBaseToken::show(int offset_) const
{
	cout << endl;
	cout << cBaseToken::get_offset_string(offset_) << "Token Type: " << tokenTypeNames[m_type] << endl;
	cout << cBaseToken::get_offset_string(offset_) << "Token Name: " << m_name << endl;
	cout << cBaseToken::get_offset_string(offset_) << "Hash : " << m_hash << endl;
	cout << cBaseToken::get_offset_string(offset_) << "is static : " << (m_static ? "true" : "false") << endl;
	cout << cBaseToken::get_offset_string(offset_) << "is const : " << (m_const ? "true" : "false") << endl;
	cout << cBaseToken::get_offset_string(offset_) << "is extern : " << (m_extern ? "true" : "false") << endl;
	cout << cBaseToken::get_offset_string(offset_) << "is volatile : " << (m_volatile ? "true" : "false") << endl;
}

void cBaseToken::setName(const string & name_)
{
	m_name = StringHandler::filter<string, char>(name_, StringHandler::FBE::begin_and_end, {' ', '\t', '\n'});
}

cBaseToken::TokenType cBaseToken::getType() const
{
	return m_type;
}

string cBaseToken::getName() const
{
	return m_name;
}

string cBaseToken::getRaw() const
{
	return m_raw;
}

string cBaseToken::getHash() const
{
	return m_hash;
}

void cBaseToken::setStatic(bool value_)
{
	m_static = value_;
}

void cBaseToken::setConst(bool value_)
{
	m_const = value_;
}

void cBaseToken::setVolatile(bool value_)
{
	m_volatile = value_;
}

void cBaseToken::setExtern(bool value_)
{
	m_extern = value_;
}

bool cBaseToken::isStatic() const
{
	return m_static;
}

bool cBaseToken::isConst() const
{
	return m_const;
}

bool cBaseToken::isVolatile() const
{
	return m_volatile;
}

bool cBaseToken::isExtern() const
{
	return m_extern;
}

#ifdef  TASK_0_2_5

void cBaseToken::write(const string & dir_, const string & file_name_, const string & mode_)
{
	
}
#else
void cBaseToken::write(const string & dir_, const string & file_name_)
{
	auto dir_names = StringHandler::split(dir_, '\\');
	
	string path = dir_names[0];
	for (auto iter = dir_names.begin() + 1; iter != dir_names.end(); iter++) {
		path += "\\" + *iter;
		if (!std::experimental::filesystem::exists(path)) {
			std::experimental::filesystem::create_directory(path);
		} 
	}
}
#endif

void cBaseToken::toRst(string * p_member_, bool root_, const string& patern_name_)
{
}

string cBaseToken::get_offset_string(int offset_)
{

	string res;
	for (int i = 0; i < offset_; ++i) {
		res += '\t';
	}

	return res;
}
