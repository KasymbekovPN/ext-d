#include "consoleCmdHandler.h"

const string ConsoleCmdHandler::commandList[ConsoleCmdHandler::NUMBER_OF_COMMAND] = {
	"--help",
	"--version",
	"--target.show.all",
	"--target.show",
	"--target.run"
};

ConsoleCmdHandler::ConsoleCmdHandler(const string & config_path_, vector<string> command_)
{
	m_error = 0;

	m_config = new ConfigHandler(config_path_);
	if (m_config->errorStatus()) {
		m_error |= error_config_error;
	}

	if (command_.size() < 1) {
		m_error |= error_list_cmd_is_empty;
	}
	
	cmdHandlers[commandList[0]] = &ConsoleCmdHandler::helpHandler;
	cmdHandlers[commandList[1]] = &ConsoleCmdHandler::versionHandler;
	cmdHandlers[commandList[2]] = &ConsoleCmdHandler::targetShowAllHandler;
	cmdHandlers[commandList[3]] = &ConsoleCmdHandler::targetShowHandler;
	cmdHandlers[commandList[4]] = &ConsoleCmdHandler::targetRunHandler;

	if (!m_error) {
		m_error |= error_invalid_console_cmd;
		for (auto iter = cmdHandlers.begin(); iter != cmdHandlers.end(); ++iter) {
			if (iter->first == command_[0]) {
				m_error = 0;
				vector<string> arg;
				std::copy(command_.begin() + 1, command_.end(), inserter(arg, arg.begin()));
				(this->*cmdHandlers[iter->first])(arg);
			}
		}
	}
}

ConsoleCmdHandler::~ConsoleCmdHandler()
{
	delete m_config;
}

void ConsoleCmdHandler::helpHandler(vector<string> command_)
{
	if (command_.size() != 0) {
		m_error |= error_help_hand_invalid_arg;
		return;
	}

	cout << "  --help - вызов справки." << endl;
	cout << "  --version - версия." << endl;
	cout << "  --target.show.all - показать все цели." << endl;
	cout << "  --target.show <target name> - показать цель target name" << endl;
	cout << "  --target.run <target name> - запустить цель target name" << endl;
}

void ConsoleCmdHandler::versionHandler(vector<string> command_)
{
	if (command_.size() != 0) {
		m_error |= error_ver_hand_invalid_arg;
		return;
	}

	cout << PROJECT_VERSION << endl;
}

void ConsoleCmdHandler::targetShowAllHandler(vector<string> command_)
{
	if (command_.size() != 0) {
		m_error |= error_tar_show_all_invalid_arg;
		return;
	}

	m_config->showAllTarget();
}

void ConsoleCmdHandler::targetShowHandler(vector<string> command_)
{
	if (command_.size() != 1) {
		m_error |= error_tar_show_invalid_arg;
		return;
	}

	m_config->showTarget(command_[0]);
}

void ConsoleCmdHandler::targetRunHandler(vector<string> command_)
{
	if (command_.size() != 1) {
		m_error |= error_tar_run_invalid_arg;
		return;
	}

	m_config->targetRun(command_[0]);
}

void ConsoleCmdHandler::showErrorStatus() const
{
	if (m_error) {
		cout << "ConsoleCmdHandler Error Status : " << m_error << endl;
	}
}
