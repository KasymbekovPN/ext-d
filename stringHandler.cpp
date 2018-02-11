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

#ifndef  TASK_0_2_5__4
string StringHandler::filter(const string & line, FBE mode, vector<char> ignore)
{

	if (FBE::all == mode) {

		string result;

		for (auto ch : line) {
			int flag = 0;
			for (auto ign_ch : ignore) {
				flag += int(ign_ch == ch);
			}

			if (0 == flag) {
				result += ch;
			}
		}
		return result;
	}

	bool was_start = false;
	size_t start = 0;
	size_t stop = line.size();

	int i = 0;
	for (; i < line.size(); ++i) {

		int flag = 0;
		for (auto ign_ch : ignore) {
			flag += int(ign_ch == line[i]);
		}

		if (0 == flag) {

			if (FBE::begin == mode || FBE::begin_and_end == mode) {
				if (!was_start) {
					was_start = true;
					start = i;
				}
			}

			if (FBE::end == mode || FBE::begin_and_end == mode) {
				stop = i;
			}			
		}
	}

	return line.substr(start, stop - start + 1);
}
#endif

#ifndef  TASK_0_2_5__8
vector<string> StringHandler::split(const string & line, char delit)
{

	string buffer;
	vector<string> result;

	for (char ch : line) {
		if (ch == delit) {
			if (buffer.size() > 0) {
				result.push_back(buffer);
				buffer.clear();
			}
		}
		else {
			buffer += ch;
		}		
	}

	if (buffer.size() > 0) { result.push_back(buffer); }

	return result;
}
#endif

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

#ifndef  TASK_0_2_5__4
string StringHandler::replace_all(const string & str_, char orig_, char new_)
{
	string res;

	for (auto ch : str_) {
		res += ch == orig_ ? new_ : ch;
	}

	return res;
}
#endif

#ifdef  TASK_0_2_5__8
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
#endif
