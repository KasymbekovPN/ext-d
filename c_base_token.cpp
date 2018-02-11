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

vector<string> cBaseToken::get_raw_Lines(bool line_feed_) const
{

	auto tmp = StringHandler::split(StringHandler::tab2space<string, char>(m_raw, 4), '\n');
	if (false == line_feed_) {
		return tmp;
	}

	vector<string> res;
	for (auto item : tmp) {
		res.push_back(item + '\n');
	}

	return res;
}

#ifdef  TASK_0_2_5__8
vector<wstring> cBaseToken::get_raw_WLines(bool line_feed_) const
{

#ifdef TASK_0_2_5__9

	vector<wstring> res;
	vector<string> raw_lines = get_raw_Lines(line_feed_);
	for (auto raw_line : raw_lines) {

		//cout << "+++ " << raw_line << endl;

		wchar_t warray[4096];
		MultiByteToWideChar(CP_ACP, 0, raw_line.c_str(), raw_line.size(), warray, raw_line.size());
		//cout << "~~~ ";
		//for (size_t i = 0; i < raw_line.size(); ++i) {
		//	std::wcout << warray[i];
		//}
		//cout << endl;
		//wstring ws(warray);
		wstring ws(warray, 0, raw_line.size());
		//ws += L'\\n';
		//ws += L'\0';

		//std::wcout << "--- " << ws << endl;

		res.push_back(ws);
	}

	//cout << "-" << endl;
	//for (auto i : res) {
	//	std::wcout << i << endl;
	//}

	//------
	//wchar_t warray[90000];
	//MultiByteToWideChar(CP_ACP, 0, m_raw.c_str(), m_raw.size(), warray, m_raw.size());
	//wstring ws(warray);
	//auto tmp = StringHandler::split<wstring, wchar_t>(StringHandler::tab2space<wstring, wchar_t>(ws, 4), L'\n');
	//if (false == line_feed_) {
	//	return tmp;
	//}
	//vector<wstring> res;
	//for (auto item : tmp) {
	//	res.push_back(item + L'\n');
	//}
	return res;

#else


	//vector<wstring> res;

	////cout << 1 << endl;

	wchar_t warray[90000];

	//cout << 2 << endl;

	MultiByteToWideChar(CP_ACP, 0, m_raw.c_str(), m_raw.size(), warray, m_raw.size());

	//cout << 3 << endl;

	wstring ws(warray);

	//cout << 4 << endl;

	//std::wcout << ws << endl;

	//cout << 5 << endl;

	auto tmp = StringHandler::split<wstring, wchar_t>(StringHandler::tab2space<wstring, wchar_t>(ws, 4), L'\n');

	//cout << 6 << endl;

	if (false == line_feed_) {
		//std::wcout << warray << endl;
		//cout << 6.5 << endl;
		return tmp;
	}

	//cout << 7 << endl;

	vector<wstring> res;
	for (auto item : tmp) {
		res.push_back(item + L'\n');
	}

	//cout << 8 << endl;

	return res;





	//res.push_back(wstring(warray));




	//for (auto item : spl) {

	//	cout << item << endl;

	//	wchar_t warray[4096];
	//	MultiByteToWideChar(CP_ACP, 0, item.c_str(), item.size(), warray, item.size());
	//	res.push_back(wstring(warray));
	//}

	//cout << "-" << endl;

	//for (auto i : res) {
	//	std::wcout << i << endl;
	//}

	//cout << "-" << endl;
	//cout << "in size : " << spl.size() << endl;
	//std::wcout << "out size : " << res.size() << endl;
 

	//return res;

	//wchar_t warray[4096];
	//string tmp = getRaw();
	//size_t size = tmp.length();

	//MultiByteToWideChar(CP_ACP, 0, tmp.c_str(), size, warray, size);
	//return vector<wstring>();

#endif

}
#endif

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

vector<string> cBaseToken::parse_members(bool root_, const string & patern_name_)
{
	return vector<string>();
}
