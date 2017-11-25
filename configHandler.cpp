#include "configHandler.h"

ConfigHandler::ConfigHandler(const string & path_)
{

	m_error_status = 0;

	FileHandler file(path_);

	if (!file.isExist()) {
		m_error_status |= error_cnf_file_no_exists;
		return;
	}

	vector<vector<string>> result = file.getCmdLists();

	for (vector<string> cmd_list : result) {

		if (cmd_list[0] == cmd_settarget) {

			if (cmd_list.size() == 3) {
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
			else {
				m_error_status |= error_cmd_settarget_invalid;
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

int ConfigHandler::errorStatus() const
{
	return m_error_status;
}

void ConfigHandler::targetRun(const string & target_name_) const
{
}
