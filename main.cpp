
#include "config.h"
#include "commandHandler.h"
#include "fileHandler.h"

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

	FileHandler f1 = FileHandler("C:/projects/external-description/_build_vs/Debug/test-1.txt");
	FileHandler f2 = FileHandler("C:/projects/external-description/_build_vs/Debug/test-2.txt");
	FileHandler f3 = FileHandler("C:/projects/external-description/_build_vs/Debug/test-3.txt");

	f2.clearFile();

	//FileHandler f = FileHandler("test-2.txt");

    return 0;
}