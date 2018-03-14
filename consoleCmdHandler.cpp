#include "consoleCmdHandler.h"

const string ConsoleCmdHandler::commandList[ConsoleCmdHandler::NUMBER_OF_COMMAND] = {
	"--help",
	"--version",
	"--target.show.all",
	"--target.show",
	"--target.run"
};

ConsoleCmdHandler::ConsoleCmdHandler(const string& config_path_json_, vector<string> command_)
{

	p_error = std::make_shared<ErrorStatus>();

	m_config = new ConfigHandler(config_path_json_, p_error);

	if (command_.size() < 1) {
		p_error->set(ErrorStatus::error::consoleCmdHand_listCmdIsEmpty, true);
	}
	
	cmdHandlers[commandList[0]] = &ConsoleCmdHandler::helpHandler;
	cmdHandlers[commandList[1]] = &ConsoleCmdHandler::versionHandler;
	cmdHandlers[commandList[2]] = &ConsoleCmdHandler::targetShowAllHandler;
	cmdHandlers[commandList[3]] = &ConsoleCmdHandler::targetShowHandler;
	cmdHandlers[commandList[4]] = &ConsoleCmdHandler::targetRunHandler;

	if (!p_error->get()) {
		p_error->set(ErrorStatus::error::consoleCmdHand_invalidConsoleCmd, true);
		for (auto iter = cmdHandlers.begin(); iter != cmdHandlers.end(); ++iter) {
			if (iter->first == command_[0]) {
				p_error->clear();
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

void ConsoleCmdHandler::helpTest()
{
}

void ConsoleCmdHandler::helpHandler(vector<string> command_)
{

	if (command_.size() != 0) {
		p_error->set(ErrorStatus::error::consoleCmdHand_helpHandInvalidArg, true);
		return;
	}

    cout << "  --help - вызов справки." << endl;
    cout << "  --version - версия." << endl;
    cout << "  --target.show.all - показать все цели." << endl;
    cout << "  --target.show <target name> - показать цель <target name>." << endl;
    cout << "  --target.run <target name> <flag> - выполнить цель <target name>" << endl;
    cout << "    -d - получить токены кода." << endl;
    cout << "    -m - проверить пользовательские файлы." << endl;
}

void ConsoleCmdHandler::versionHandler(vector<string> command_)
{
	if (command_.size() != 0) {
		p_error->set(ErrorStatus::error::consoleCmdHand_verHandInvalidArg, true);
		return;
	}

	cout << PROJECT_VERSION << endl;
}

void ConsoleCmdHandler::targetShowAllHandler(vector<string> command_)
{
	if (command_.size() != 0) {
		p_error->set(ErrorStatus::error::consoleCmdHand_tarShowAllInvalidArg, true);
		return;
	}

	m_config->showAllTarget();

}

void ConsoleCmdHandler::targetShowHandler(vector<string> command_)
{
	if (command_.size() != 1) {
		p_error->set(ErrorStatus::error::consoleCmdHand_tarShowInvalidArg, true);
		return;
	}

	m_config->showTarget(command_[0]);
}

void ConsoleCmdHandler::targetRunHandler(vector<string> command_)
{

	if (command_.size() != 2) {
		p_error->set(ErrorStatus::error::consoleCmdHand_tarRunInvalidArg, true);
		return;
	}

	m_config->targetRun(command_[0], command_[1]);
}

void ConsoleCmdHandler::showErrorStatus() const
{
	p_error->display();
}
