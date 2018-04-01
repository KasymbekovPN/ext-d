#include "part_pline.hpp"

#ifndef TASK_0_3_6__1
PartPLine::PartPLine(const wstring & content_) : m_type(type::string), m_content(content_)
#else
PartPLine::PartPLine(const wstring& content_, const std::string& token_output_): m_type(type::string), m_content(content_)
#endif
{
}

#ifndef  TASK_0_3_7__1
#ifndef  TASK_0_3_6__1
PartPLine::PartPLine(const wstring& head_link_, const wstring& link_, shared_ptr<vector<TokenPath>> token_file_list_) 
#else
PartPLine::PartPLine(const wstring& head_link_, const wstring& link_, shared_ptr<vector<TokenPath>> token_file_list_, const std::string& token_output_)
#endif
	:  m_type(type::link), m_head_link(head_link_)
#else
PartPLine::PartPLine(const wstring& head_link_, const wstring& link_, shared_ptr<vector<TokenPath>> token_file_list_, const std::string& token_output_)
	:  m_type(type::link)
#endif
{


#ifdef  TASK_0_3_6__1

#ifdef  TASK_0_3_7__1
	const wstring flag_404_str = L"-404-";
#endif

	m_relative_token_output = L".." + StringHandler::str2wstr(token_output_);

#ifdef  TASK_0_3_7__1

	//
	// Проверяем: помечен ли заголовок ссылки флагом -404- (файл по ссылки не существует).
	//
	wstring head_link = StringHandler::filter<wstring, wchar_t>(head_link_, StringHandler::FBE::begin_and_end, {L' '});
	if (flag_404_str == head_link.substr(0, flag_404_str.size()))
	{
		head_link = StringHandler::filter<wstring, wchar_t>(head_link.substr(flag_404_str.size()), StringHandler::FBE::begin_and_end, {L' '});
	}

#endif

	TokenPath tp(link_);
	bool token_found = false;
	wstring filename;

	//
	// Ищем токен с соответвующим именем
	//
	for (auto it = token_file_list_->begin(); it < token_file_list_->end(); ++it) {
		if (it->clean_file_name() == tp.clean_file_name()) {
			filename = it->filename();
			token_found = true;
			break;
		}
	}

#ifdef  TASK_0_3_7__1
	m_head_link = token_found ? head_link : flag_404_str + head_link;
	m_link = token_found ? m_relative_token_output + L"\\" + filename : link_;
	m_link = StringHandler::replace_all<wstring, wchar_t>(m_link, L'\\', L'/');
#else
	m_link = token_found ? m_relative_token_output + L"\\" + filename : link_;
	m_link = StringHandler::replace_all<wstring, wchar_t>(m_link, L'\\', L'/');
#endif

#else
	TokenPath tp(link_);
	bool token_found = false;
	wstring filename;

	//
	// Ищем токен с соответвующим имененм
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

#endif
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
