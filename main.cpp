
#include "config.h"
#include "commandHandler.h"

#include <iostream>
#include <clocale>
#include <vector>
#include <string>

int main(int argc, char** argv){

	setlocale(LC_ALL, "Russian");

	vector<string> cmds;
	for (int i = 1; i < argc; ++i) {
		cmds.push_back(string(argv[i]));
	}

	CommandHandler cHandler = CommandHandler(cmds);
	cHandler.run();                                             

    return 0;
}