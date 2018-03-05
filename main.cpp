
#include "fileHandler.h"
#include "configHandler.h"

#include <consoleCmdHandler.h>
#include <clocale>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::wcout;
using std::wstring;

int main(int argc, char** argv){

	setlocale(LC_ALL, "Russian");

	vector<string> args;
	for (int i = 1; i < argc; i++) {
		args.push_back(argv[i]);
	}

	ConsoleCmdHandler cmdHandler("config.json", args);
	cmdHandler.showErrorStatus();

    return 0;
}