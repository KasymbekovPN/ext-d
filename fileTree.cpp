#include "fileTree.h"

namespace fs = std::experimental::filesystem;

FileTree::FileTree(const string & path_, std::shared_ptr<ErrorStatus> p_error_, const string& supp_lang_, vector<string> unhand_files_, vector<string> unhand_dir_)
	: m_path(path_)
{

#ifdef  TASK_001__2 

	//
	// ќпредел€емс€ с €зыком.
	//
	m_ll["c-lang"] = FileTreeLang::c_lang;

	m_lang_ext[FileTreeLang::c_lang].push_back(".h");
	m_lang_ext[FileTreeLang::c_lang].push_back(".c");

	p_error = p_error_;

	m_lang = (m_ll.find(supp_lang_) != m_ll.end() ? m_ll[supp_lang_] : FileTreeLang::unknow);

	if (FileTreeLang::unknow == m_lang) {
		p_error->set(ErrorStatus::error::fileTree_unknowLang, true);
	}

	if (0 == p_error->get()) {

		for (auto & iter : fs::directory_iterator(path_)) {

			//
			// ќбработка директории
			//
			if (fs::file_type::directory == iter.status().type()) {
				std::stringstream str_dir_name;
				str_dir_name << iter;

				//
				// ƒиректори€ не должна быть помечена как необрабатываема€
				//
				bool unhandled = false;
				for (auto ud : unhand_dir_) {
					if (ud == str_dir_name.str()) {
						unhandled = true;
						break;
					}
				}

				if ('.' != str_dir_name.str()[0] && !unhandled) {
					m_directory.push_back(new FileTree(str_dir_name.str(), p_error, supp_lang_, unhand_files_, unhand_dir_));
				}
			}
			else if (fs::file_type::regular == iter.status().type()) {

				std::stringstream str_file_names;
				str_file_names << iter;
				fs::path file_path(str_file_names.str());

				for (auto en_ext: m_lang_ext[m_lang]) {

					if (file_path.extension() == en_ext) {
						m_files.push_back(file_path.string());
					}
				}
			}
		}
	}

	//cout << path_ << endl;
	//for (auto i : m_files) {
	//	cout << i << endl;
	//}

#endif//TASK_001__2 

#ifdef  TASK_001__1 
	m_ll["c-lang"] = FileTreeLang::c_lang;

	m_lang_ext[FileTreeLang::c_lang].push_back("h");
	m_lang_ext[FileTreeLang::c_lang].push_back("c");

	p_error = p_error_;

	m_lang = (m_ll.find(supp_lang_) != m_ll.end() ? m_ll[supp_lang_] : FileTreeLang::unknow);

	if (FileTreeLang::unknow == m_lang) {
		p_error->set(ErrorStatus::error::fileTree_unknowLang, true);
	}

	//
	// ѕереписать использу€ filesystem
	//
	if (!p_error->get()) {

		WIN32_FIND_DATA wfd;
		HANDLE const hFind = FindFirstFile((LPCSTR)(m_path + "\\*").c_str(), &wfd);

		if (INVALID_HANDLE_VALUE != hFind) {

			do {

				if (FILE_ATTRIBUTE_ARCHIVE == wfd.dwFileAttributes) {

					size_t found = string(wfd.cFileName).find_last_of(".");

					if (string::npos != found) {
						string ext = string(wfd.cFileName).substr(found + 1);
						for (auto item : m_lang_ext[m_lang]) {
							if (ext == item) {
								m_files.push_back(m_path + "\\\\" + string(wfd.cFileName));
							}
						}

						if ("index.rst" == string(wfd.cFileName)) {
							m_index_rst = string(wfd.cFileName);
						}
					}

				}
				else if (FILE_ATTRIBUTE_DIRECTORY == wfd.dwFileAttributes) {
					if (wfd.cFileName[0] != '.') {
						string path = m_path + "\\\\" + string(wfd.cFileName);
						m_directory.push_back(new FileTree(path, p_error, supp_lang_, unhan_files_, unhand_dir_));
					}
				}
			} while (NULL != FindNextFile(hFind, &wfd));

		}
	}
#endif//TASK_001__1

}

FileTree::~FileTree()
{
	for (auto dir : m_directory) {
		delete dir;
	}
}

void FileTree::filePaths(std::shared_ptr<vector<string>> path_out, bool need_clear)
{
	if (need_clear) {
		path_out->clear();
	}

	for (auto file : m_files) {
		path_out->push_back(file);
	}
	for (auto dir : m_directory) {
		dir->filePaths(path_out, false);
	}
}

string FileTree::getIndexRstName() const
{
	return m_index_rst;
}

