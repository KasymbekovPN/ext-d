#include "stringHandler.h"

string StringHandler::filter(const string & line, int flags)
{

	string result;

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
		else if (ch = '_') {
			if (flags & fladLowLine) {
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
