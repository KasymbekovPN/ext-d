#include "configHandler.h"

ConfigHandler::ConfigHandler(const string & path_)
{

	FileHandler file(path_);
	vector<vector<string>> result = file.getCmdLists();

	for (vector<string> cmd_list : result) {

		if (cmd_list.size() != 3 ) {
			cout << error4 << endl;
			break;
		}

		if (cmd_list[0] == cmd_settarget) {
			bool need_add = true;
			for (auto p_target : m_targets) {
				if (p_target->getName() == cmd_list[1]) {
					need_add = false;
				}
			}

			if (need_add) {
				m_targets.push_back(new Target(cmd_list[1], cmd_list[2]));
			}
		}

	}
}

ConfigHandler::~ConfigHandler()
{
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
}
