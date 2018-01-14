#pragma once

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;

class StringHandler
{
public:

	enum class FBE {
		begin,
		end,
		begin_and_end,
		all,
	};

	static const int flagUpperAlpha	= 0b0000000001;
	static const int flagLowerAlpha	= 0b0000000010;
	static const int flagAlpha		= 0b0000000011;
	static const int flagSpace		= 0b0000000100;
	static const int flagRSlash		= 0b0000001000;
	static const int flagPoint		= 0b0000010000;
	static const int fladLowLine	= 0b0000100000;
	static const int flagLSlash		= 0b0001000000;
	static const int flagsColon		= 0b0010000000;
	static const int flagsNumber	= 0b0100000000;
	static const int flagsHyphen	= 0b1000000000;
	static const int flagAll		= 0b1111111111;

	static string filter(const string&, int);
	static string filter(const string&, FBE, vector<char>);
	static vector<string> split(const string&, char);
	static vector<string> space(const string& line);
	static vector<string> file2line(const string& file, bool replace_tab);
};
