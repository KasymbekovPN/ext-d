#include "token_path.hpp"

TokenPath::TokenPath(const std::wstring & path_) : fs::path(path_)
{

	//
	// Получаем имя без расширения.
	//
	size_t found_last_point = filename().wstring().find_last_of(L'.');	
	std::wstring file_name_without_ext = (
		wstring::npos == found_last_point
		? filename().wstring()
		: filename().wstring().substr(0, found_last_point)
		);

	size_t found_last_dash = file_name_without_ext.find_last_of(L'-');
	if (wstring::npos == found_last_dash) {
		m_clean_file_name = file_name_without_ext;
		m_hash_of_file_name = L"";
	}
	else {
		std::wstring presumably_hash = file_name_without_ext.substr(found_last_dash + 1);
		if (L'0' == presumably_hash[0] && L'x' == presumably_hash[1]) {
			m_clean_file_name = file_name_without_ext.substr(0, found_last_dash);
			m_hash_of_file_name = presumably_hash;
		}
		else {
			m_clean_file_name = file_name_without_ext;
			m_hash_of_file_name = L"";
		}
	}
}

TokenPath::~TokenPath()
{
}

std::wstring TokenPath::clean_file_name() const
{
	return m_clean_file_name;
}