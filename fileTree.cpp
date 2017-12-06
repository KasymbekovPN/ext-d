#include "fileTree.h"

FileTree::FileTree(const string & path_, ErrorStatus error_status_, const string& supp_lang_)
	: m_path(path_)
{

	m_ll["c-lang"] = FileTreeLang::c_lang;

	m_lang_ext[FileTreeLang::c_lang].push_back("h");
	m_lang_ext[FileTreeLang::c_lang].push_back("c");

	m_error_status = new ErrorStatus();

	m_lang = (m_ll.find(supp_lang_) != m_ll.end() ? m_ll[supp_lang_] : FileTreeLang::unknow);

	if (FileTreeLang::unknow == m_lang) {
		m_error_status->set(ErrorStatus::error::fileTree_unknowLang, true);
	}

	if (!m_error_status->get()) {

		WIN32_FIND_DATA wfd;
		HANDLE const hFind = FindFirstFile((LPCSTR)(m_path + "\\*").c_str(), &wfd);

		if (INVALID_HANDLE_VALUE != hFind) {

			do {

				if (FILE_ATTRIBUTE_ARCHIVE == wfd.dwFileAttributes) {

					size_t found = string(wfd.cFileName).find_last_of(".");
					string ext = string(wfd.cFileName).substr(found + 1);

					for (auto item : m_lang_ext[m_lang]) {
						if (ext == item) {
							m_files.push_back(m_path + "\\\\" + string(wfd.cFileName));
						}
					}

				}
				else if (FILE_ATTRIBUTE_DIRECTORY == wfd.dwFileAttributes) {
					if (wfd.cFileName[0] != '.') {
						string path = m_path + "\\\\" + string(wfd.cFileName);
						m_directory.push_back(new FileTree(path, *m_error_status, supp_lang_));
					}
				}
			} while (NULL != FindNextFile(hFind, &wfd));

		}
	}
}

FileTree::~FileTree()
{
	for (auto dir : m_directory) {
		delete dir;
	}

	delete m_error_status;
}

ErrorStatus FileTree::show() const
{
	cout << "Path = " << m_path << endl;

	for (auto file : m_files) {
		cout << file << endl;
	}

	for (auto dir : m_directory) {
		m_error_status->set(dir->show());
	}

	return *m_error_status;
}

