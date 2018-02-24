#pragma once

#include <iostream>
#include <string>
#include <filesystem>

using std::wstring;
using std::wcout;
using std::endl;

namespace fs = std::experimental::filesystem;

class TokenPath : public fs::path
{
public:
	TokenPath(const std::wstring& path_);
	~TokenPath();

	std::wstring clean_file_name() const;
	std::wstring hash_of_file_name() const;

private:

	std::wstring m_clean_file_name;
	std::wstring m_hash_of_file_name;
};