#include "stringHandler.h"

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