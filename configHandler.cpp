#include "configHandler.h"

ConfigHandler::ConfigHandler(const string & path_, shared_ptr<ErrorStatus> p_error_)
{

	p_error = p_error_;

	FileHandler file(path_);

	if (!file.isExist()) {
		p_error->set(ErrorStatus::error::configHand_cnfgFileNoExitst, true);
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
					m_targets.push_back(new Target(cmd_list[1], cmd_list[2], p_error));
				}
			}
			else {
				p_error->set(ErrorStatus::error::configHand_cmdSetTargetInvalid, true);
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

void ConfigHandler::targetRun(const string & target_name_) const
{
	bool target_no_exists = true;

	for (auto target : m_targets) {
		if (target->getName() == target_name_) {
			target_no_exists = false;
			target->run();
		}
	}

	if (target_no_exists) {
		p_error->set(ErrorStatus::error::configHand_targetRun_targetNoExists, true);
	}
}

void ConfigHandler::showAllTarget() const
{
	if (m_targets.size() == 0) {
		p_error->set(ErrorStatus::error::configHand_noTargetSpec, true);
	}
	else {
		for (auto target : m_targets) {
			target->toConsole();
		}
	}
}

void ConfigHandler::showTarget(const string & target_name_) const
{
	p_error->set(ErrorStatus::error::configHand_currentTargetNoExists, true);

	for (auto target : m_targets) {
		if (target->getName() == target_name_) {
			p_error->set(ErrorStatus::error::configHand_currentTargetNoExists, false);
			target->toConsole();
		}
	}
}
