#include "wfileHandler.hpp"

WFileHandler::WFileHandler(const std::wstring & file_name_) : m_path(file_name_)
{
	std::wifstream wfin(m_path);
	m_file_exist = !wfin.fail();

	if (!m_file_exist) {
		wfin.close();
		return;
	}

	wfin.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	std::wstringstream wss;
	wss << wfin.rdbuf();

	m_file_content = wss.str();

	wfin.close();
}

WFileHandler::~WFileHandler()
{
}

const wstring & WFileHandler::wstring() const
{
	return m_file_content;
}