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
