#pragma once

#include <iostream>
#include <string>
#include <vector>

class CommandHandler
{
public:
	CommandHandler();
	~CommandHandler();

	void setStringItems(std::vector<std::string>);
	void test() const;
private:

	std::vector<std::vector<std::string>> m_command;	
	std::vector<std::string> m_buffer;
};