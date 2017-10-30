
#include "config.h"
#include "commandHandler.h"

#include <iostream>
#include <clocale>
#include <vector>
#include <string>

const char g_project_version[] = {
#ifdef PROJECT_VERSION
    PROJECT_VERSION
#else   
    "<unknow version>"
#endif
};

int main(int argc, char** argv){

	setlocale(LC_ALL, "Russian");

	CommandHandler cmdH = CommandHandler();

	if (argc > 1) {

		std::vector<std::string> cmd;

		for (int i = 1; i < argc; ++i) {
			cmd.push_back((std::string)argv[i]);
		}

		cmdH.setStringItems(cmd);
	}
	else {
		std::cout << "Команды не введены." << std::endl;
	}

	//cmdH.test();

	cmdH.run();

    return 0;
}