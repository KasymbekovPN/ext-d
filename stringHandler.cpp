#include "stringHandler.h"

string StringHandler::filt(const string & line, int flags)
{

	string result;

	//
	// todo: сделать менее громоздким
	//
	for (char ch : line) {
		if (ch >= 'A' && ch <= 'Z') {
			if (flags & flagUpperAlpha) {
				result += ch;
			}
		}
		else if (ch >= 'a' && ch <= 'z') {
			if (flags & flagLowerAlpha) {
				result += ch;
			}
		}
		else if (ch == ' ') {
			if (flags & flagSpace) {
				result += ch;
			}
		}
		else if (ch == '/') {
			if (flags & flagRSlash) {
				result += ch;
			}
		}
		else if (ch == '.') {
			if (flags & flagPoint) {
				result += ch;
			}
		}
		else if (ch == '_') {
			if (flags & fladLowLine) {
				result += ch;
			}
		}
		else if (ch == '\\') {
			if (flags & flagLSlash) {
				result += ch;
			}
		}
		else if (ch == ':'){
			if (flagsColon & flags) {
				result += ch;
			}
		}
		else if (ch >= '0' && ch <= '9') {
			if (flags & flagsNumber) {
				result += ch;
			}
		}
		else if (ch == '-') {
			if (flags & flagsHyphen) {
				result += ch;
			}
		}

	}

	return result;
}

vector<string> StringHandler::space(const string & line)
{
	string buffer;
	for (auto ch : line) {
		if ('\t' == ch || '\n' == ch) {
			buffer += "    ";
		}
		else {
			buffer += ch;
		}
	}

	return split(buffer, ' ');
}

vector<string> StringHandler::file2line(const string & file, bool replace_tab)
{
	vector<string> result;
	string buffer;

	for (char ch : file) {
		if (replace_tab && '\t' == ch) {
			buffer += "&nbsp;";
		}
		else {
			buffer += ch;
		}

		if ('\n' == ch) {
			result.push_back(buffer);
			buffer.clear();
		}
	}

	return result;
}

wstring StringHandler::escape_wchar(const wstring & line_, wchar_t ch_)
{
	wstring res;
	for (auto i : line_) {
		if (ch_ == i) {
			res += L'\\';
			res += i;
		}
		else {
			res += i;
		}
	}

	return res;
}

wstring StringHandler::str2wstr(const string & in)
{
#ifdef DEPR_STR_CVT_OPTION_EN
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	return converter.from_bytes(in);
#else
	if (in.empty())
	{
		return wstring();
	}

	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &in[0], int(in.size()), NULL, 0);
	wstring wstr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &in[0], int(in.size()), &wstr[0], size_needed);
	return wstr;
#endif
}

string StringHandler::wstr2str(const wstring & in)
{
#ifdef  DEPR_STR_CVT_OPTION_EN
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	return converter.to_bytes(in);
#else

	if (in.empty())
	{
		return string();
	}

	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &in[0], int(in.size()), NULL, 0, NULL, NULL);
	string str(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &in[0], int(str.size()), &str[0], size_needed, NULL, NULL);
	return str;
#endif
}