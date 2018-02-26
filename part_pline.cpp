#include "part_pline.hpp"

PartPLine::PartPLine(const wstring & content_) : m_type(type::string), m_content(content_)
{
	//wcout << m_content << endl;
}

#ifndef  TASK_3_0__3
PartPLine::PartPLine(const wstring & head_link, const wstring & link, shared_ptr<vector<wstring>> token_file_list_) 
	: m_type(type::link), m_head_link(head_link), m_link(link)
#else
PartPLine::PartPLine(const wstring& head_link_, const wstring& link_, shared_ptr<vector<TokenPath>> token_file_list_) 
	:  m_type(type::link), m_head_link(head_link_)
#endif
{

	TokenPath tp(link_);
	bool token_found = false;
	wstring filename;

	//
	// »щем токен с соответвующим имененм
	//
	for (auto it = token_file_list_->begin(); it < token_file_list_->end(); ++it) {
		if (it->clean_file_name() == tp.clean_file_name()) {
			filename = it->filename();
			token_found = true;
			break;
		}
	}

	m_link = token_found ? tp.parent_path().wstring() + L"\\" + filename : link_;
	m_link = StringHandler::replace_all<wstring, wchar_t>(m_link, L'\\', L'/');
}

PartPLine::~PartPLine()
{
}

wstring PartPLine::string() const
{
	wstring res;

	switch (m_type)
	{
	case type::string:
		res = m_content;
		break;
	case type::link:
		res = L"[" + m_head_link + L"](" + m_link + L")";
		break;
	default:
		break;
	}

	return res;
}
