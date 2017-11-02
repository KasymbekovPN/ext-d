#include "commandHandler.h"

const string CommandHandler::validCommandName[CommandHandler::NUMBER_OF_COMMAND] = {"--help", "--version", "--run", "--global"};

CommandHandler::CommandHandler(const vector<string>& commands_)
{
	handlers[validCommandName[0]] = &CommandHandler::helpHandler;
	handlers[validCommandName[1]] = &CommandHandler::versionHandler;
	handlers[validCommandName[2]] = &CommandHandler::runHandler;
	handlers[validCommandName[3]] = &CommandHandler::globalHandler;

	if (commands_.size() < 1) {
		hasCommand = false;
	}
	
	if (commands_.size() > 0){
		hasCommand = true;
		command = commands_[0];
	}
	
	if (commands_.size() > 1) {
		
		for (int i = 1; i < commands_.size(); ++i) {
			arguments.push_back(commands_[i]);
		}
	}
}

CommandHandler::~CommandHandler()
{
}

void CommandHandler::run()
{

	if (!hasCommand) {
		cout << "Должна быть введена одна команда." << endl
			 << "Для уточнения используйте команду --help." << endl;
		return;
	}

	for (auto i = handlers.begin(); i != handlers.end(); ++i) {
		if (i->first == command) {
			(this->*handlers[command])(arguments);
			return;
		}
	}

	cout << "Введена невалидная команда." << endl
		<< "Для уточнения используйте команду --help." << endl;
}

void CommandHandler::helpHandler(vector<string> arguments_)
{

	if (arguments_.size() != 0) {

		cout << "Команда --help не поддерживает аргументы." << endl
			<< "Подробнее --help help." << endl;
		return;
	}

	cout << "--help" << endl;
	cout << "\tВызов справки." << endl;
	cout << "--version" << endl;
	cout << "\tВерсия утилиты." << endl;
	cout << "--run" << endl;
	cout << "\tВыполнить сценарий." << endl;
	cout << "--global" << endl;
	cout << "\tГлобальные настройки." << endl;
}

void CommandHandler::versionHandler(vector<string> arguments_)
{
	if (arguments_.size() != 0) {
		
		cout << "Команда --version не поддерживает аргументы." << endl
			 << "Подробнее --help version." << endl;
		return;
	}

#ifdef PROJECT_VERSION
	const string version = PROJECT_VERSION;
#else   
	const string version = "<unknow version>";
#endif

	cout << "Версия " << version << endl;
}

void CommandHandler::runHandler(vector<string> arguments_)
{
	if (arguments_.size() != 1) {
		
		cout << "Команда run должна иметь один аргумент - имя модуля." << endl
			 << "Подробнее --help run." << endl;
		return;
	}
	
	cout << "--run " << arguments_[0] << endl;
}

void CommandHandler::globalHandler(vector<string> arguments_)
{
	cout << "--global" << endl;

	for (auto item : arguments_) {
		cout << item << endl;
	}

}
