#include "fileTree.h"

FileTree::FileTree(const string & path_, int error_status_): m_path(path_)
{
	m_error_status = 0;

	if (error_status_) {
		m_error_status |= error_arg;
	}

	if (!m_error_status) {

		WIN32_FIND_DATA wfd;
		HANDLE const hFind = FindFirstFile((LPCSTR)(m_path + "\\*").c_str(), &wfd);

		if (INVALID_HANDLE_VALUE != hFind) {

			do {
				if (FILE_ATTRIBUTE_ARCHIVE == wfd.dwFileAttributes) {
					m_files.push_back(string(wfd.cFileName));
				}
				else if (FILE_ATTRIBUTE_DIRECTORY == wfd.dwFileAttributes) {
					if (wfd.cFileName[0] != '.') {
						string path = m_path + "\\" + string(wfd.cFileName);
						m_directory.push_back(new FileTree(path, 0));
					}
				}
			} while (NULL != FindNextFile(hFind, &wfd));

		}
	}

	//WIN32_FIND_DATA wfd;
	//HANDLE const hFind = FindFirstFile((LPCSTR)(m_source_dir + "\\*").c_str(), &wfd);

	//if (INVALID_HANDLE_VALUE != hFind) {
	//	do {
	//		string str;
	//		cout << &wfd.cFileName[0] << " -- ";
	//		if (FILE_ATTRIBUTE_ARCHIVE == wfd.dwFileAttributes) {
	//			str = "File";
	//		}
	//		else if (FILE_ATTRIBUTE_DIRECTORY == wfd.dwFileAttributes) {
	//			str = "Directory";
	//		}
	//		cout << str << endl;
	//	} while (NULL != FindNextFile(hFind, &wfd));
	//}
}

FileTree::~FileTree()
{
	for (auto dir : m_directory) {
		delete dir;
	}
}

void FileTree::show() const
{
	cout << "Path = " << m_path << endl;

	for (auto file : m_files) {
		cout << file << endl;
	}

	for (auto dir : m_directory) {
		dir->show();
	}
}
