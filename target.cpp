#include "target.h"

const int Target::cmd_size[Target::number_of_cmd] = {2, 2};

Target::Target(const string & name_, const string& path_)
{

	m_error_status = 0;

	m_name = name_;
	m_path = path_;

	FileHandler file(m_path);
	is_exist = file.isExist();

	FileHandler file_out(m_path);
	vector<string> arg_buffer_out = file_out.getCmdArgList(cmd_set_output_dir);
	if (arg_buffer_out.size() == 1) {
		m_output_dir = arg_buffer_out[0];
	}
	else {
		m_error_status |= error_output_dir_invalid_param;
	}

	FileHandler file_src(m_path);
	vector<string> arg_buffer_src = file_src.getCmdArgList(cmd_set_source_dir);
	if (arg_buffer_src.size() == 1) {
		m_source_dir = arg_buffer_src[0];
	}
	else {
		m_error_status |= error_source_dir_invalid_param;
	}

	FileHandler file_supp_lang(m_path);
	vector<string> supp_lang = file_supp_lang.getCmdArgList(cmd_set_lang);
	if (supp_lang.size() != 1) {
		m_error_status |= error_unknow_lang;
	}

	if (!m_error_status) {
		DWORD f = GetFileAttributes(m_source_dir.c_str());
		if ((f == INVALID_FILE_ATTRIBUTES) || (f & FILE_ATTRIBUTE_DIRECTORY) == 0) {
			m_error_status |= error_source_dir_no_exists;
		}

		f = GetFileAttributes(m_output_dir.c_str());
		if ((f == INVALID_FILE_ATTRIBUTES) || (f & FILE_ATTRIBUTE_DIRECTORY) == 0) {
			m_error_status |= error_output_dir_no_exists;
		}
	}

	m_fileTree = new FileTree(m_source_dir, m_error_status, supp_lang[0]);

}

Target::~Target()
{
	delete m_fileTree;
}

string Target::getName() const
{
	return m_name;
}

string Target::getPath() const
{
	return m_path;
}

bool Target::isExist() const
{
	return is_exist;
}

void Target::toConsole() const
{

	cout << endl;
	cout << "Target Name\t\t : " << m_name << endl;
	cout << "Error Status\t\t : " << m_error_status << endl;
	
	if (!m_error_status) {
		cout << "Param Source Dir\t : " << m_source_dir << endl;
		cout << "Param Output Dir\t : " << m_output_dir << endl;
	}	

	cout << endl;
}

void Target::run() const
{
	m_fileTree->show();
}
