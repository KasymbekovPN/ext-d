#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class StringHandler
{
public:
	static const int flagUpperAlpha	= 0b000001;
	static const int flagLowerAlpha	= 0b000010;
	static const int flagAlpha		= 0b000011;
	static const int flagSpace		= 0b000100;
	static const int flagRSlash		= 0b001000;
	static const int flagPoint		= 0b010000;
	static const int fladLowLine	= 0b100000;
	static const int flagAll		= 0b111111;

	static string filter(const string&, int);
	static vector<string> split(const string&, char);

};