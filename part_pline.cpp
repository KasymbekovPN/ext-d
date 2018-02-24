#include "part_pline.hpp"

PartPLine::PartPLine(const wstring & content_) : m_type(type::string), m_content(content_)
{
	wcout << m_content << endl;
}

#ifndef  TASK_3_0__3
PartPLine::PartPLine(const wstring & head_link, const wstring & link, shared_ptr<vector<wstring>> token_file_list_) 
	: m_type(type::link), m_head_link(head_link), m_link(link)
#else
PartPLine::PartPLine(const wstring& head_link_, const wstring& link_, shared_ptr<vector<TokenPath>> token_file_list_) 
	:  m_type(type::link), m_head_link(head_link_), m_link(link_)
#endif
{
	wcout << m_head_link << endl;
	wcout << m_link << endl;

	TokenPath tp(m_link);
	cout << "---" << endl;
	wcout << "~~~ " << tp.wstring() << endl;
	wcout << "~~~ " << tp.filename() << endl;
	wcout << "~~~ " << tp.extension() << endl;
	wcout << "~~~ " << tp.parent_path() << endl;
	wcout << "~~~ " << tp.clean_file_name() << endl;
	wcout << "~~~ " << tp.hash_of_file_name() << endl;
	cout << "---" << endl;
}

PartPLine::~PartPLine()
{
}

wstring PartPLine::string() const
{
	wstring res;

	return res;
}
