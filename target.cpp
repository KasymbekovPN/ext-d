#include "target.h"

Target::Target(const string & str_)
{

	vector<string> buffer;

	string line;
	for (auto item : str_) {

		if (item == ' ') {			
			if (line.size() > 0) {
				buffer.push_back(line);

				line.clear();
			}			
		}
		else {
			line += item;
		}		
	}

	if (line.size() > 0) {
		buffer.push_back(line);
	}

	if (buffer.size() == 2) {
		m_name = buffer[0];

		FileHandler f(buffer[1]);
		is_exist = f.isExist();

		if (is_exist) {
			m_path = buffer[1];
		}
	}
	else {
		cout << error1 << endl;
	}

	FileHandler file(m_path);
	if (!file.isExist()) {
		cout << "Target "<< m_name << " : "<< error2 << endl;
	}
	else {
		string buffer;
		char begin = '(';
		char end = ')';
		char ch = file.get();
		bool rec = false;
		while (ch != EOF){
			if (!rec && ch == begin) {
				rec = true;
			}
			else {
				if (ch == begin) {
					cout << "Target " << m_name << " : " << error3 << endl;
				}
				else if (ch == end) {
					rec = false;
					vector<string> vBuffer = StringHandler::split(
						StringHandler::filter(buffer, StringHandler::flagAll),
						' '
					);

					if (vBuffer.size() == 2) {
						if (vBuffer[0] == cmd_set_source_dir) {
							m_source_dir = vBuffer[1];
							m_source_dir_was_set = true;
						}
						else if (vBuffer[0] == cmd_set_output_dir) {
							m_output_dir = vBuffer[1];
							m_output_dir_was_set = true;
						}
						else {
							cout << "Target " << m_name << " : " << error5 << endl;
						}
					}
					else {
						cout << "Target " << m_name << " : " << error4 << endl;
					}
					buffer.clear();
				}
				else {
					buffer += ch;
				}
			}

			ch = file.get();
		}
	}

	DWORD f = GetFileAttributes(m_source_dir.c_str());
	m_source_dir_exists = (f != INVALID_FILE_ATTRIBUTES) && (f & FILE_ATTRIBUTE_DIRECTORY);

	f = GetFileAttributes(m_output_dir.c_str());
	m_output_dir_exists = bool ((f != INVALID_FILE_ATTRIBUTES) && (f & FILE_ATTRIBUTE_DIRECTORY));

	cout << "---" << endl;
	cout << "Target : " << m_name << endl;
	cout << "Source Dir : " << m_source_dir << endl;
	cout << "SD : " << m_source_dir_was_set << " : " << m_source_dir_exists << endl;
	cout << "Output Dir : " << m_output_dir << endl;
	cout << "SD : " << m_output_dir_was_set << " : " << m_output_dir_exists << endl;
	cout << "---" << endl;

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
