#include "configHandler.h"

ConfigHandler::ConfigHandler(const string & path_)
{
	m_fileHandler = new FileHandler(path_);

	const char begin = '(';
	const char end = ')';
	bool rec = false;

	string buffer = "";

	char ch = m_fileHandler->get();
	while (ch != EOF)
	{		

		if (!rec && ch == begin) {
			rec = true;
		}
		else {
			if (ch == begin) {
				cout << error1 << endl;
				break;
			}
			else if (ch == end) {
				rec = false;
				int first_space = int(buffer.find(" "));

				if (first_space < 0) {
					cout << error2 << endl;
				}
				else {
					string raw_command = buffer.substr(0, first_space);
					string command = "";
					for (auto ch : raw_command) {
						if (ch >= 'A' && ch <= 'Z') {
							command += ch;
						}
					}

					if (command == cmd_settarget) {
						m_targets.push_back(new Target(buffer.substr(first_space + 1)));
					}
					
				}
				buffer.clear();
			}
			else {
				buffer += ch;
			}
		}

		ch = m_fileHandler->get();
	}

	for (int i = 0; i < m_targets.size() - 1; ++i) {
		for (int j = i + 1; j < m_targets.size(); ++j) {
			if (m_targets[i]->getName() == m_targets[j]->getName()) {
				cout << error3 << endl;
			}
		}
	}

}

ConfigHandler::~ConfigHandler()
{
	delete m_fileHandler;
	for (auto item : m_targets) {
		delete item;
	}
}

void ConfigHandler::test() const
{
	for (auto item : m_targets) {
		cout << "\nTarget Name: " << item->getName() << endl;
		cout << "Target Path: " << item->getPath() << endl;
		cout << "Target is exists: " << item->isExist() << endl;
	}
}

void ConfigHandler::test1() const
{
	if (m_fileHandler->isExist()) {
		cout << m_fileHandler->getAsString() << endl;
	}
	else {
		cout << "No" << endl;
	}
}
