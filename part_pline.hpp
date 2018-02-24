#pragma once

#include <iostream>
#include <string>
#include <variant>
#include <memory>
#include <vector>
#include <array>

#include "config.h"
#include "token_path.hpp"

using std::wcout;
using std::cout;
using std::endl;
using std::string;
using std::variant;
using std::wstring;
using std::shared_ptr;
using std::vector;
using std::pair;
using std::array;

class PartPLine
{
public:
	
	enum class type {
		string,
		link
	};

	PartPLine(const wstring& content_);
#ifdef  TASK_3_0__3
	PartPLine(const wstring& head_link_, const wstring& link_, shared_ptr<vector<TokenPath>> token_file_list_);
#else
	PartPLine(const wstring& head_link, const wstring& link, shared_ptr<vector<wstring>> token_file_list_);
#endif

	~PartPLine();
	wstring string() const;

private:

	type m_type;
	wstring m_content;
	wstring m_head_link;
	wstring m_link;
};