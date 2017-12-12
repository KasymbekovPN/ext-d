
#include "config.h"
#include "fileHandler.h"
#include "configHandler.h"
#include "stringHandler.h"
#include "errorStatus.h"

#include <consoleCmdHandler.h>
#include <iostream>
#include <clocale>
#include <vector>
#include <string>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

int main(int argc, char** argv){

	setlocale(LC_ALL, "Russian");

	string s = "C:/projects/external-description/_build_vs/Debug/config.txt";
	vector<string> args;
	for (int i = 1; i < argc; i++) {
		args.push_back(argv[i]);
	}

	ConsoleCmdHandler cmdHandler(s, args);
	cmdHandler.showErrorStatus();

	//string s1 = "Hello";
	//size_t f = s1.find_last_of('k');
	//cout << int(f) << endl;
	//cout << f << endl;
	//cout << std::string::npos << endl;

    return 0;
}