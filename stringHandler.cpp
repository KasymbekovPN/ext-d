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
