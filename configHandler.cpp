#include "configHandler.h"

ConfigHandler::ConfigHandler(const string & path_)
{
	m_fileHandler = new FileHandler(path_);
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
