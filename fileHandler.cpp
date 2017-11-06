#include "fileHandler.h"

FileHandler::FileHandler(const string& filePath_): m_filePath(filePath_)
{

	if (FileHandler::fileExist(m_filePath)) {
		return;
	}

	ofstream fout_(m_filePath);
	fout_.close();

}

FileHandler::~FileHandler()
{
}

void FileHandler::clearFile() const
{
	ofstream fout_(m_filePath, std::ios_base::out | std::ios_base::trunc);
	fout_.close();
}

int FileHandler::getNumLine() const
{
	ifstream* fin_ = new ifstream;
	bool exist_ = FileHandler::fileExist(m_filePath, fin_, false);
	int number_of_line = 0;

	if (exist_) {

		number_of_line = 1;

		char ch = char(fin_->get());
		while (ch != EOF) {

			if (ch == '\n') {
				number_of_line++;
			}
			ch = char(fin_->get());
		}

		fin_->close();
	}
	
	delete fin_;
	return number_of_line;
}

bool FileHandler::rewriteLine(int line_idx_, const string & new_line_)
{

	bool result = false;
	int num = getNumLine();

	if (num > 0 && line_idx_ < num ) {		

		vector<string> result = readFile();
		result.at(line_idx_) = new_line_ + '\n';
		rewriteFile(result);
	}

	return result;
}

bool FileHandler::fileExist(const string& path_)
{
	ifstream fin_(path_, std::ios::in | std::ios::_Nocreate);
	bool exist_ = !fin_.fail();
	fin_.close();

	return exist_;
}

bool FileHandler::fileExist(const string & path_, ifstream* p_fin_, bool needClose)
{

	p_fin_->open(path_, std::ios::in | std::ios::_Nocreate);
	bool exist_ = !p_fin_->fail();

	if (!exist_ || needClose) {
		p_fin_->close();
	}

	return exist_;
}

vector<string> FileHandler::readFile()
{
	vector<string> result;
	ifstream* fin_ = new ifstream;
	bool exist = FileHandler::fileExist(m_filePath, fin_, false);

	if (exist) {

		char ch = fin_->get();
		string line = "";
		while (ch != EOF){

			line += ch;
			if (ch == '\n') {
				result.push_back(line);
				line = "";
			}
			ch = fin_->get();
		}

		result.push_back(line);

		fin_->close();
	}

	delete fin_;
	return result;
}

void FileHandler::rewriteFile(vector<string> lines) const
{

	ifstream* fin_ = new ifstream;
	bool exist = FileHandler::fileExist(m_filePath, fin_, false);

	if (exist) {
		fin_->close();

		ofstream fout_(m_filePath, std::ios::in | std::ios::trunc);
		for (auto line : lines) {
			fout_ << line;
		}
		fout_.close();
	}

	delete fin_;
}
