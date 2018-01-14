
#include "config.h"
#include "fileHandler.h"
#include "configHandler.h"
#include "stringHandler.h"
#include "errorStatus.h"
#include "dom.hpp"
#include "dirHandler.hpp"

#include <consoleCmdHandler.h>
#include <iostream>
#include <clocale>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>
#include <codecvt>
#include <locale>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::wcout;
using std::wstring;

int main(int argc, char** argv){

	setlocale(LC_ALL, "Russian");

	string s = "C:/projects/external-description/_build_vs/Debug/config.txt";
	vector<string> args;
	for (int i = 1; i < argc; i++) {
		args.push_back(argv[i]);
	}

	ConsoleCmdHandler cmdHandler(s, args);
	cmdHandler.showErrorStatus();

    return 0;
}