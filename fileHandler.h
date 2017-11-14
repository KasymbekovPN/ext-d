#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <ios>
#include <vector>
#include <sstream>

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::stringstream;

class FileHandler
{
public:
	FileHandler(const string&);
	~FileHandler();

	const string& getAsString() const;
	bool isExist() const;

	//void clearFile() const;
	//int getNumLine() const;
	//void rewriteLine(int, const string&);
	//void insertLine(int, const string&);
	//void deleteLine(int);

	//static bool fileExist(const string& path_);
	//static bool fileExist(const string& path_, ifstream* p_fin_, bool needClose);

private:

	stringstream m_ss;
	string m_file;
	string m_path;
	bool m_file_exist;

	//vector<string> readFile();
	//void rewriteFile(vector<string>) const;

	//string m_filePath;

};
