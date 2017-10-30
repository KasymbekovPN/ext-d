#include "commandHandler.h"

CommandHandler::CommandHandler(){

	m_command.clear();
	m_buffer.clear();
	m_buffer.push_back("--global");

	//handlers["--global"] = &CommandHandler::globalHandler;
	//handlers.insert(std::pair<std::string, void(CommandHandler::*)(std::vector<std::string>)>("--global", &CommandHandler::globalHandler));
}

CommandHandler::~CommandHandler(){	
}

void CommandHandler::setStringItems(std::vector<std::string> items_)
{

	for (auto item = items_.begin(); item != items_.end(); ++item) {

		std::string temp_ = *item;

		if (temp_[0] == '-' && temp_[1] == '-') {

			m_command.push_back(m_buffer);

			m_buffer.clear();
		}

		m_buffer.push_back(*item);

	}

	m_command.push_back(m_buffer);
}

void CommandHandler::run() {

	if (m_command.size() == 0) {
		std::cout << "Ни одна команда не введена. Для вызова справки введите --help" << std::endl;
	}
	else {

		for (auto line : m_command) {

			//
			// TODO: Засунуть обработчики в map
			//
			std::vector<std::string> temp_;
			for (int i = 1; i < line.size(); ++i) {
				temp_.push_back(line[i]);
			}

			if (line[0] == "--global") {
				//std::cout << "1" << std::endl;
				globalHandler(temp_);
			}
			else if (line[0] == "--help") {
				//std::cout << "2" << std::endl;
				helpHandler(temp_);
			}
			else if (line[0] == "--version"){
				//std::cout << "3" << std::endl;
				versionHandler(temp_);
			}
		}

		//std::vector<std::string> temp_;
		//for (int i = 1; i < m_command[0].size(); ++i) {
		//	temp_.push_back(m_command[0][i]);
		//}
		//handlers[(std::string)"--global"](temp_);
		//auto it = handlers.begin();
		//std::cout << it->first << std::endl;
		//std::cout << it->second << std::endl;
	}

}

void CommandHandler::test() const
{

	for (auto item : m_command) {
		std::cout << item[0] << std::endl;
		for (int i = 1; i < item.size(); i++) {
			std::cout << "\t" << item[i] << std::endl;
		}
	}
}

void CommandHandler::globalHandler(std::vector<std::string> cmd_args)
{
	std::cout << "Обработчик команды --global с аргументами:" << std::endl;
	//for (auto item : cmd_args) {
	//	std::cout << "\t" << item << std::endl;
	//}
}

void CommandHandler::helpHandler(std::vector<std::string> cmd_args)
{
	std::cout << "Обработчик команды --help" << std::endl;
	if (cmd_args.size() != 0) {
		std::cout << "Команда --help не должна иметь аргументов" << std::endl;
	}
}

void CommandHandler::versionHandler(std::vector<std::string> cmd_args)
{
	std::cout << "Обработчик команды --version" << std::endl;
	if (cmd_args.size() != 0) {
		std::cout << "Команда --version не должна иметь аргументов" << std::endl;
	}
}
