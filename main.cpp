
#include "config.h"
#include "commandHandler.h"
#include "fileHandler.h"
#include "configHandler.h"

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
	ConfigHandler ch(s);
	ch.test();

	//FileHandler fh(s);
	//cout << fh.getAsString() << endl;

	//string s1 = fh.getAsString();
	//cout << s1 << endl;

	//s1 += "add";
	//
	//cout << s1 << endl;
	//cout << fh.getAsString() << endl;


	system("pause");

    return 0;
}