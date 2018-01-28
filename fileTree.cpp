#include "fileTree.h"

namespace fs = std::experimental::filesystem;

FileTree::FileTree(const string & path_, std::shared_ptr<ErrorStatus> p_error_, const string& supp_lang_, vector<string> unhand_files_, vector<string> unhand_dir_)
	: m_path(path_)
{

	//
	// Определяемся с языком.
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
			// Обработка директории
			//
			if (fs::file_type::directory == iter.status().type()) {
				std::stringstream str_dir_name;
				str_dir_name << iter;

				//
				// Директория не должна быть помечена как необрабатываемая
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

						bool unhandled = false;
						for (auto uh : unhand_files_) {
							if (file_path.string() == uh) {
								unhandled = true;
								break;
							}
						}

						if (!unhandled) {
							m_files.push_back(file_path.string());
						}						
					}
				}
			}
		}
	}
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

