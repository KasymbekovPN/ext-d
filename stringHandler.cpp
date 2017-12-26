#include "stringHandler.h"

string StringHandler::filter(const string & line, int flags)
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
