#pragma once

#include "config.h"

#include <string>
#include <vector>
#include <iostream>
#include <locale>
#include <codecvt>
#include <Windows.h>

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

	static vector<string> space(const string& line);
	static wstring escape_wchar(const wstring& line_, wchar_t ch_);

	static wstring str2wstr(const string& in);
	static string wstr2str(const wstring& in);

	template <class T, class C> 
	static T filter(const T& line, FBE, vector<C>);

	template <class T, class C>
	static T replace_all(const T& str_, C orig_, C new_);

	template <class T, class C>
	static T tab2space(const T& str_, size_t size_);

	template <class T, class C>
	static vector<T> split(const T& line_, C delit);
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

template<class T, class C>
inline vector<T> StringHandler::split(const T & line_, C delit)
{
	T buffer;
	vector<T> result;

	for (C ch : line_) {
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
