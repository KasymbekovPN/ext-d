
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

//template <class T>
//class test_class
//{
//public:
//    T value;
//    bool flag;
//};

//template <class T>
//test_class<T> test(T value)
//{
//    test_class<T> tc;
//    tc.value = value;
//    tc.flag = true;

//    return tc;
//}

//vector<int> test()
//{
//    return {1, 2, 3};
//}

int main(int argc, char** argv){

	setlocale(LC_ALL, "Russian");

	vector<string> args;
	for (int i = 1; i < argc; i++) {
		args.push_back(argv[i]);
	}

	ConsoleCmdHandler cmdHandler("config.json", args);
	cmdHandler.showErrorStatus();

//    auto x = test();
//    cout << x[0] << endl;

//    auto tc = test<int>(12);
//    cout << tc.value << "  " << tc.flag << endl;

    return 0;
}
