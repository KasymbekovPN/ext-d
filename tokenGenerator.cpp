#include "tokenGenerator.hpp"

TokenGenerator::TokenGenerator(const string & path_)
{
	size_t found = path_.find_last_of('.');
	m_path = string::npos != found ? path_.substr(0, found) : "";

	m_was_header = "h" == path_.substr(found + 1);
	m_was_source = "c" == path_.substr(found + 1);
}

bool TokenGenerator::equal(const string & path_)
{
	bool res = false;

	size_t found = path_.find_last_of('.');
	if (string::npos != found) {

		string path = path_.substr(0, found);
		string ext = path_.substr(found + 1);

		if (m_path == path) {

			if ("h" == ext) {
				m_was_header = true;
			}
			else if ("c" == ext) {
				m_was_source = true;
			}

			res = true;

		}		
	}

	return res;
}

void TokenGenerator::show()
{
	cout << endl;
	cout << m_path << endl;
	cout << "h : " << m_was_header << endl;
	cout << "c : " << m_was_source << endl;
	cout << endl;
}

