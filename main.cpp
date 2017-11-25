
#include "config.h"
#include "commandHandler.h"
#include "fileHandler.h"
#include "configHandler.h"
#include "stringHandler.h"

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
	ConfigHandler config_file(s);

	if (!config_file.errorStatus()) {

	}
	else {
		cout << "Ошибка конфигурационного файла : " << config_file.errorStatus() << endl;
	}
	

	system("pause");

    return 0;
}