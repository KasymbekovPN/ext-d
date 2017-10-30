#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

class CommandHandler
{
public:
	CommandHandler();
	~CommandHandler();

	void setStringItems(std::vector<std::string>);
	void run();
	void test() const;
private:

	void globalHandler(std::vector<std::string> cmd_args);
	void helpHandler(std::vector<std::string> cmd_args);
	void versionHandler(std::vector<std::string> cmd_args);

	//void (*handlers[3])(std::vector<std::string>);

	//std::map<std::string, void(CommandHandler::*)(std::vector<std::string>)> handlers;

	std::vector<std::vector<std::string>> m_command;	
	std::vector<std::string> m_buffer;
};