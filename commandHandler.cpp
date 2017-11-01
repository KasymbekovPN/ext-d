#include "commandHandler.h"

const string CommandHandler::validCommandName[CommandHandler::NUMBER_OF_COMMAND] = {"--help", "--version", "--run"};

CommandHandler::CommandHandler(const vector<string>& commands_)
{
	handlers[validCommandName[0]] = &CommandHandler::helpHandler;
	handlers[validCommandName[1]] = &CommandHandler::versionHandler;
	handlers[validCommandName[2]] = &CommandHandler::runHandler;

	if (commands_.size() != 1) {
		cout << "������ ���� ������� ���� �������." << endl
			 << "��� ��������� ����������� ������� --help." << endl;
	}
	else {
		command = commands_[0];
	}
}

CommandHandler::~CommandHandler()
{
}

void CommandHandler::run()
{
	for (auto i = handlers.begin(); i != handlers.end(); ++i) {
		if (i->first == command) {
			(this->*handlers[command])();
			return;
		}
	}

	cout << "������� ���������� �������." << endl
		<< "��� ��������� ����������� ������� --help." << endl;
}

void CommandHandler::helpHandler()
{
	cout << "--help" << endl;
	cout << "\t����� �������." << endl;
	cout << "--version" << endl;
	cout << "\t������ �������." << endl;
	cout << "--run" << endl;
	cout << "\t��������� ��������." << endl;
}

void CommandHandler::versionHandler()
{
#ifdef PROJECT_VERSION
	const string version = PROJECT_VERSION;
#else   
	const string version = "<unknow version>";
#endif

	cout << "������ " << version << endl;
}

void CommandHandler::runHandler()
{
	cout << "run" << endl;
}

