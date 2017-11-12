#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <ios>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;

class FileHandler
{
public:
	FileHandler(const string& path_);
	~FileHandler();

	void clearFile() const;
	int getNumLine() const;
	void rewriteLine(int, const string&);
	void insertLine(int, const string&);
	void deleteLine(int);

	static bool fileExist(const string& path_);
	static bool fileExist(const string& path_, ifstream* p_fin_, bool needClose);

private:

	vector<string> readFile();
	void rewriteFile(vector<string>) const;

	string m_filePath;

};
