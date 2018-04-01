#include "part_pline.hpp"

PartPLine::PartPLine(const wstring& content_, const std::string& token_output_): m_type(type::string), m_content(content_)
{
}

PartPLine::PartPLine(const wstring& head_link_, const wstring& link_, shared_ptr<vector<TokenPath>> token_file_list_, const std::string& token_output_)
	:  m_type(type::link)
{
	const wstring flag_404_str = L"-404-";

	m_relative_token_output = L".." + StringHandler::str2wstr(token_output_);

	//
	// Проверяем: помечен ли заголовок ссылки флагом -404- (файл по ссылки не существует).
	//
	wstring head_link = StringHandler::filter<wstring, wchar_t>(head_link_, StringHandler::FBE::begin_and_end, {L' '});
	if (flag_404_str == head_link.substr(0, flag_404_str.size()))
	{
		head_link = StringHandler::filter<wstring, wchar_t>(head_link.substr(flag_404_str.size()), StringHandler::FBE::begin_and_end, {L' '});
	}

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

	m_head_link = token_found ? head_link : flag_404_str + head_link;
	m_link = token_found ? m_relative_token_output + L"\\" + filename : link_;
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
