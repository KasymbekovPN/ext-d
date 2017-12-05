#include "configHandler.h"

ConfigHandler::ConfigHandler(const string & path_)
{

	//m_error_status = 0;
	m_error = new ErrorStatus();

	FileHandler file(path_);

	if (!file.isExist()) {
		//m_error_status |= error_cnf_file_no_exists;
		m_error->set(ErrorStatus::error::configHand_cnfgFileNoExitst, true);
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
				//m_error_status |= error_cmd_settarget_invalid;
				m_error->set(ErrorStatus::error::configHand_cmdSetTargetInvalid, true);
			}

		}

	}
}

ConfigHandler::~ConfigHandler()
{

	for (auto item : m_targets) {
		delete item;
	}

	delete m_error;
}

ErrorStatus ConfigHandler::errorStatus() const
{
	return *m_error;
}

void ConfigHandler::targetRun(const string & target_name_) const
{
	bool target_no_exists = true;

	for (auto target : m_targets) {
		if (target->getName() == target_name_) {
			target_no_exists = false;
			m_error->set(target->run());
			//target->run();
		}
	}

	if (target_no_exists) {
		//cout << "Цель с именем " << target_name_ << " не существиет" << endl;
		m_error->set(ErrorStatus::error::configHand_targetRun_targetNoExists, true);
	}
}

void ConfigHandler::showAllTarget() const
{
	if (m_targets.size() == 0) {
		//cout << "Ни одной цели не задано." << endl;
		m_error->set(ErrorStatus::error::configHand_noTargetSpec, true);
	}
	else {
		for (auto target : m_targets) {
			//target->toConsole();
			m_error->set(target->toConsole());
		}
	}
}

void ConfigHandler::showTarget(const string & target_name_) const
{
	bool target_no_exists = true;

	for (auto target : m_targets) {
		if (target->getName() == target_name_) {
			//target->toConsole();
			m_error->set(target->toConsole());
			target_no_exists = false;
		}
	}

	if (target_no_exists) {
		//cout << "Цель с именем " << target_name_ << " не существиет" << endl;
		m_error->set(ErrorStatus::error::configHand_currentTargetNoExists, true);
	}
}
