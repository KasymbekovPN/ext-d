#include "target.h"

const int Target::cmd_size[Target::number_of_cmd] = {2, 2};

Target::Target(const string & name_, const string& path_, std::shared_ptr<ErrorStatus> p_error_)
{
	p_error = p_error_;

	m_name = name_;
	m_path = path_;

	FileHandler file(m_path);
	is_exist = file.isExist();

	FileHandler file_out(m_path);
	vector<string> arg_buffer_out = file_out.getCmdArgList(cmd_set_output_dir);
	if (arg_buffer_out.size() == 1) {
		m_output_dir = arg_buffer_out[0];
	}
	else {
		p_error->set(ErrorStatus::error::target_outputDirInvalidParam, true);
	}

	FileHandler file_src(m_path);
	vector<string> arg_buffer_src = file_src.getCmdArgList(cmd_set_source_dir);
	if (arg_buffer_src.size() == 1) {
		m_source_dir = arg_buffer_src[0];
	}
	else {
		p_error->set(ErrorStatus::error::target_sourceDirInvalidParam, true);
	}

	FileHandler file_supp_lang(m_path);
	vector<string> supp_lang = file_supp_lang.getCmdArgList(cmd_set_lang);
	if (supp_lang.size() != 1) {
		p_error->set(ErrorStatus::error::target_unknowLang, true);
	}

	if (!p_error->get()) {
		DWORD f = GetFileAttributes(m_source_dir.c_str());
		if ((f == INVALID_FILE_ATTRIBUTES) || (f & FILE_ATTRIBUTE_DIRECTORY) == 0) {
			p_error->set(ErrorStatus::error::target_sourceDirNoExists, true);
		}

		f = GetFileAttributes(m_output_dir.c_str());
		if ((f == INVALID_FILE_ATTRIBUTES) || (f & FILE_ATTRIBUTE_DIRECTORY) == 0) {
			p_error->set(ErrorStatus::error::target_outputDirNoExists, true);
		}
	}

	m_fileTree = new FileTree(m_source_dir, p_error, supp_lang[0]);

}

Target::~Target()
{
	delete m_fileTree;
}

string Target::getName() const
{
	return m_name;
}

string Target::getPath() const
{
	return m_path;
}

bool Target::isExist() const
{
	return is_exist;
}

void Target::toConsole() const
{

	cout << endl;
	cout << "Target Name\t\t : " << m_name << endl;
	cout << "Error Status\t\t : " << p_error->get() << endl;

	if (!p_error->get()) {
		cout << "Param Source Dir\t : " << m_source_dir << endl;
		cout << "Param Output Dir\t : " << m_output_dir << endl;
	}

	cout << endl;
}

void Target::run() const
{

	std::shared_ptr<vector<string>> res(new vector<string>());
	m_fileTree->filePaths(res, true);

	for (auto p_file_name = res->begin(); p_file_name != res->end(); ++p_file_name) {

		string short_name = p_file_name->substr(m_source_dir.size());

		string sfn;
		for (int i = 0; i < short_name.size(); ++i) {
			sfn += ('.' == short_name[i] ? '_' : short_name[i]);
		}

		string out_file_name = m_output_dir + "\\\\source" + sfn + ".html";

		FileHandler file(*p_file_name);
		vector<string> codeLines = StringHandler::split(file.getAsString(), '\n');

		int line_idx = 0;

		Dom dom(Dom::item::html, true, out_file_name, "", "", "html");
		dom.set(Dom::item::head, "", "", "head");
		dom.set({"head"}, Dom::item::title, "", "Τΰιλ " + short_name, "title");
		dom.set(Dom::item::body, "", "", "body");
		
		for (auto line : codeLines) {
			dom.set({"body"}, Dom::item::p, "", line, "p_code_line_" + std::to_string(line_idx++));
		}

		dom.make_doc();
	}
}
