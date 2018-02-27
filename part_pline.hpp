#pragma once

#include <iostream>
#include <string>
#include <variant>
#include <memory>
#include <vector>
#include <array>

#include "config.h"
#include "token_path.hpp"
#include "stringHandler.h"

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
	PartPLine(const wstring& head_link_, const wstring& link_, shared_ptr<vector<TokenPath>> token_file_list_);

	~PartPLine();
	wstring string() const;

private:

	type m_type;
	wstring m_content;
	wstring m_head_link;
	wstring m_link;
};