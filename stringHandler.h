#pragma once

#include "config.h"

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::wstring;

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


	static string filt(const string&, int);
#ifndef  TASK_0_2_5__4
	static string filter(const string&, FBE, vector<char>);
#endif
	static vector<string> split(const string&, char);
	static vector<string> space(const string& line);
	static vector<string> file2line(const string& file, bool replace_tab);
#ifndef  TASK_0_2_5__4
	static string replace_all(const string& str_, char orig_, char new_);
#endif

	template <class T, class C> 
	static T filter(const T& line, FBE, vector<C>);

	template <class T, class C>
	static T replace_all(const T& str_, C orig_, C new_);

	template <class T, class C>
	static T tab2space(const T& str_, size_t size_);
};

template<class T, class C>
inline T StringHandler::filter(const T & line, FBE mode, vector<C> ignore)
{

	if (FBE::all == mode) {

		T result;
		
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

template<class T, class C>
inline T StringHandler::replace_all(const T & str_, C orig_, C new_)
{
	T res;

	for (C ch : str_) {
		res += ch == orig_ ? new_ : ch;
	}

	return res;
}

template<class T, class C>
inline T StringHandler::tab2space(const T & str_, size_t size_)
{
	T result;

	C marker = C('\t');
	for (C ch : str_) {
		if (ch == marker) {
			for (size_t i = 0; i < size_; ++i) {
				result += ' ';
			}
		}
		else {
			result += ch;
		}
	}

	return result;
}
