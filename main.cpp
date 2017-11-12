
#include "config.h"
#include "commandHandler.h"
#include "fileHandler.h"
#include "jsonItem.h"
#include "jsonNumber.h"
#include "jsonHandler.h"

#include <iostream>
#include <clocale>
#include <vector>
#include <string>

int main(int argc, char** argv){

	setlocale(LC_ALL, "Russian");

	string s1 = "C:/projects/external-description/_build_vs/Debug/test.json";
	JsonHandler j(s1);
	cout << j.exist() << endl;

	//vector<JsonNumber*> vj;

	//vj.push_back(new JsonNumber(12, "first"));
	//vj.push_back(new JsonNumber(13));
	//vj.push_back(new JsonNumber());

	//for (auto item : vj) {
	//	item->test();
	//}

	//for (auto item : vj) {
	//	delete item;
	//}

	//JsonNumber* j = new JsonNumber(91, "o_1");
	//j->test();
	//cout << j->get() << endl;
	//cout << j->getName() << endl;
	//cout << j->getID() << endl;

	//delete j;
	
	system("pause");

	//---
	//vector<string> cmds;
	//for (int i = 1; i < argc; ++i) {
	//	cmds.push_back(string(argv[i]));
	//}

	//CommandHandler cHandler = CommandHandler(cmds);
	//cHandler.run();                                             
	//-----

	//string s1 = "C:/projects/external-description/_build_vs/Debug/test-1.txt";
	//FileHandler f1(s1);
	//f1.deleteLine(3);

	//string s1 = "C:/projects/external-description/_build_vs/Debug/test-1.txt";
	//FileHandler f1(s1);
	//f1.insertLine(61, "new 61");


	//string s2 = "C:/projects/external-description/_build_vs/Debug/test-2.txt";
	//string s3 = "C:/projects/external-description/_build_vs/Debug/test-3.txt";

	//FileHandler f1(s1);
	//cout << f1.getNumLine() << endl;
	//f1.rewriteLine(0, "abc");
	//f1.rewriteLine(1, "ddf");
	//f1.rewriteLine(2, "xyz");

	//FileHandler f2(s2);
	//cout << f2.getNumLine() << endl;

	//FileHandler f3(s3);
	//cout << f3.getNumLine() << endl;

	//FileHandler f1 = FileHandler("C:/projects/external-description/_build_vs/Debug/test-1.txt");
	//FileHandler f2 = FileHandler("C:/projects/external-description/_build_vs/Debug/test-2.txt");
	//FileHandler f3 = FileHandler("C:/projects/external-description/_build_vs/Debug/test-3.txt");
	//f2.clearFile();
	//FileHandler f = FileHandler("test-2.txt");

    return 0;
}