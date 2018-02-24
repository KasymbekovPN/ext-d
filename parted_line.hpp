#pragma once

#include "config.h"
#include "part_pline.hpp"
#include "token_path.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <array>

using std::wcout;
using std::endl;
using std::wstring;
using std::vector;
using std::shared_ptr;
using std::array;

class PartedLine
{
public:
#ifdef  TASK_3_0__3
	PartedLine(const wstring& source_line_, shared_ptr<vector<TokenPath>> token_file_list_);
#else
	PartedLine(const wstring& source_line_, shared_ptr<vector<wstring>> token_file_lists_);
#endif
	~PartedLine();

	wstring processedWString() const;

private:

	vector<PartPLine*> m_parts;

#ifdef  TASK_3_0__2
	static bool check_founds(const array<size_t, 4> founds_);
#endif
};

