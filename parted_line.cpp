#include "parted_line.hpp"

PartedLine::PartedLine(const wstring & source_line_, shared_ptr<vector<TokenPath>> token_file_list_)
{

	array<size_t, 4> founds;
	size_t start = 0;
	bool cond = true;

	while (cond)
	{
		founds[0] = source_line_.find_first_of(L'[', start);
		founds[1] = source_line_.find_first_of(L']', start);
		founds[2] = source_line_.find_first_of(L'(', start);
		founds[3] = source_line_.find_first_of(L')', start);

		cond = PartedLine::check_founds(founds);

		if (cond) {			
			wstring str = source_line_.substr(start, founds[0] - start);
			m_parts.push_back(new PartPLine(str));			

			wstring head_link = source_line_.substr(founds[0] + 1, founds[1] - founds[0] - 1);
			wstring link = source_line_.substr(founds[2] + 1, founds[3] - founds[2] - 1);
			m_parts.push_back(new PartPLine(head_link, link, token_file_list_));

			start = founds[3] + 1;
		}
		else {
			wstring str = source_line_.substr(start);
			m_parts.push_back(new PartPLine(str));
		}
	}
}

PartedLine::~PartedLine()
{
	for (auto iter : m_parts) {
		delete iter;
	}
}

wstring PartedLine::processedWString() const
{
	wstring res;
	for (auto it : m_parts) {
		res += it->string();
	}

	return res;
}

bool PartedLine::check_founds(const array<size_t, 4> founds_)
{
	bool cond = true;

	for (size_t i = 0; i < founds_.size(); ++i) {
		cond &= wstring::npos != founds_[i];
		if (0 != i) {
			cond &= founds_[i - 1] < founds_[i];
		}
	}

	cond &= founds_[1] + 1 == founds_[2];

	return cond;
}
