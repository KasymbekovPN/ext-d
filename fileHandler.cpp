#include "fileHandler.h"

FileHandler::FileHandler(const string & path_): m_path(path_)
{

	ifstream fin(m_path, std::ios::in | std::ios::_Nocreate);
	m_file_exist = !fin.fail();

	if (!m_file_exist) {
		fin.close();
		return;
	}

	char ch;
	while (fin.get(ch)) {
		m_ss << ch;
	}

	m_file = m_ss.str();

	fin.close();

	//std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	//m_wfile = converter.from_bytes(m_file);

	//	using convert_typeX = std::codecvt_utf8<wchar_t>;
	//std::wstring_convert<convert_typeX, wchar_t> converterX;
	//return converterX.from_bytes(str);
}

FileHandler::~FileHandler()
{
}

const string & FileHandler::getAsString() const
{
	return m_file;
}

#ifdef  TASK_0_2_5__4
//const wstring & FileHandler::getAsWString() const
//{
//	return m_wfile;
//}
#endif

vector<string> FileHandler::getAsLineList() const
{
	return vector<string>();
}

bool FileHandler::isExist() const
{
	return m_file_exist;
}

char FileHandler::get()
{
	return m_ss.get();
}

vector<vector<string>> FileHandler::getCmdLists()
{

	m_error_status = 0;

	vector<vector<string>> result;
	string buffer;

	if (m_file_exist) {
		char begin = '(';
		char end = ')';
		bool rec = false;
		char ch = m_ss.get();
		
		while (ch != EOF) {

			if (!rec && ch == begin) {
				rec = true;
			}
			else {
				if (ch == begin) {
					m_error_status |= error_cmd_format;
				}
				else if (ch == end) {
					rec = false;
#ifdef  TASK_0_2_5__4
					vector<string> vBuffer = StringHandler::split(
						StringHandler::filt(buffer, StringHandler::flagAll),
						' '
					);
#else
					vector<string> vBuffer = StringHandler::split(
						StringHandler::filter(buffer, StringHandler::flagAll),
						' '
					);
#endif
					result.push_back(vBuffer);
					buffer.clear();
				}
				else {
					buffer += ch;
				}
			}

			ch = m_ss.get();
		}
	}

	if (m_error_status) {
		result.clear();
	}

	return result;
}

vector<string> FileHandler::getCmdArgList(const string & cmd_)
{
	vector<string> result;
	auto buffer = getCmdLists();

	for (auto item : buffer) {
		if (item.size() >= 2) {
			if (item[0] == cmd_) {
				std::copy(item.begin() + 1, item.end(), std::inserter(result, result.begin()));
			}
		}
	}

	return result;
}

string FileHandler::getStream()
{
	return m_ss.str();
}
