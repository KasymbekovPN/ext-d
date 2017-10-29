#include "commandHandler.h"

CommandHandler::CommandHandler(){

	m_command.clear();
	m_buffer.clear();
	m_buffer.push_back("--global");
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

void CommandHandler::test() const
{

	for (auto item : m_command) {
		std::cout << item[0] << std::endl;
		for (int i = 1; i < item.size(); i++) {
			std::cout << "\t" << item[i] << std::endl;
		}
	}
}
