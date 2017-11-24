#include "target.h"

const int Target::cmd_size[Target::number_of_cmd] = {2, 2};

Target::Target(const string & name_, const string& path_)
{

	m_name = name_;
	m_path = path_;

	FileHandler file(m_path);
	is_exist = file.isExist();

	FileHandler file_out(m_path);
	vector<string> arg_buffer_out = file_out.getCmdArgList(cmd_set_output_dir);
	if (arg_buffer_out.size() == 1) {
		m_output_dir = arg_buffer_out[0];
		m_output_dir_was_set = true;
	}
	else {
		cout << m_name << " -- " << error2 << endl;
		return;
	}

	FileHandler file_src(m_path);
	vector<string> arg_buffer_src = file_src.getCmdArgList(cmd_set_source_dir);
	if (arg_buffer_src.size() == 1) {
		m_source_dir = arg_buffer_src[0];
		m_source_dir_was_set = true;
	}
	else {
		cout << m_name << " -- " << error3 << endl;
		return;
	}

	DWORD f = GetFileAttributes(m_source_dir.c_str());
	m_source_dir_exists = (f != INVALID_FILE_ATTRIBUTES) && (f & FILE_ATTRIBUTE_DIRECTORY);

	f = GetFileAttributes(m_output_dir.c_str());
	m_output_dir_exists = bool ((f != INVALID_FILE_ATTRIBUTES) && (f & FILE_ATTRIBUTE_DIRECTORY));

	//cout << "---" << endl;
	//cout << "Target : " << m_name << endl;
	//cout << "Source Dir : " << m_source_dir << endl;
	//cout << "SD : " << m_source_dir_was_set << " : " << m_source_dir_exists << endl;
	//cout << "Output Dir : " << m_output_dir << endl;
	//cout << "SD : " << m_output_dir_was_set << " : " << m_output_dir_exists << endl;
	//cout << "---" << endl;

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
