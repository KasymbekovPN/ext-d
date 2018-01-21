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

	cout << "2" << endl;

	FileHandler file_src(m_path);
	vector<string> arg_buffer_src = file_src.getCmdArgList(cmd_set_source_dir);
	if (arg_buffer_src.size() == 1) {
		m_source_dir = arg_buffer_src[0];
	}
	else {
		p_error->set(ErrorStatus::error::target_sourceDirInvalidParam, true);
	}

	cout << "3" << endl;

	FileHandler file_supp_lang(m_path);
	vector<string> supp_lang = file_supp_lang.getCmdArgList(cmd_set_lang);
	if (supp_lang.size() != 1) {
		p_error->set(ErrorStatus::error::target_unknowLang, true);
	}

	cout << "4" << endl;

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

	cout << "5" << endl;

	cout << m_source_dir << endl;
	cout << "6" << endl;
	cout << m_output_dir << endl;
	cout << "7" << endl;
	cout << supp_lang[0] << endl;
	cout << "8" << endl;
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

void Target::run(const string& flag_) const
{

	std::shared_ptr<vector<string>> res(new vector<string>());
	m_fileTree->filePaths(res, true);

	if (tgt_flg_d == flag_) {
		//----не-удалять----------
		make_token_generators(res);
		//------------------------
	}
	else if (tgt_flg_m == flag_) {
		//----не-удалять----------
		make_source_out(res);
		make_source_token_out();
		//make_functional_out();
		make_functional_page();
		make_tokens_page();
		make_sources_page();
		make_main_out();
		//-----------------------
	}
	else {
		p_error->set(ErrorStatus::error::target_invalidFlag, true);
	}

}

void Target::make_source_out(std::shared_ptr<vector<string>> res) const
{
	for (auto p_file_name = res->begin(); p_file_name != res->end(); ++p_file_name) {

		string short_name = p_file_name->substr(m_source_dir.size());
		string sfn;
		for (int i = 0; i < short_name.size(); ++i) {
			sfn += ('.' == short_name[i] ? '_' : short_name[i]);
		}

		string out_file_name = m_output_dir + "\\\\source" + sfn + ".html";
		FileHandler file(*p_file_name);

		vector<string> codeLines = StringHandler::file2line(file.getAsString(), false);

		int line_idx = 0;
		vector<int> tab_offsets_even;
		vector<int> tab_offsets_odd;
		bool is_even = true;		

		Dom dom(Dom::item::html, true, out_file_name, "", "", "html", 0);
		dom.set(Dom::item::head, "", "", "head", 0);
		dom.set({ "head" }, Dom::item::title, "", "Файл " + short_name, "title", 0);
		dom.set(Dom::item::body, " class = body", "", "body", 0);

		dom.set({ "body" }, Dom::item::table, " class = table", "", "table", codeLines.size());

		std::cout << short_name << " : " << line_idx << " / " << codeLines.size();

		for (auto line : codeLines) {

			string tr_name = "tr_" + std::to_string(line_idx);
			dom.set({ "body", "table" }, Dom::item::tr, "", "", tr_name, 0);
			dom.set({ "body", "table", tr_name }, Dom::item::td, " class = num_colon", std::to_string(line_idx + 1), "line_num_" + std::to_string(line_idx + 1), 0);

			int tab_num = 0;
			for (int i = 0; i < line.size(); ++i) {
				if ('\t' != line[i]) {
					break;
				}
				tab_num++;
			}

			if (is_even) {
				if (tab_offsets_even.end() == std::find(tab_offsets_even.begin(), tab_offsets_even.end(), tab_num)) {
					tab_offsets_even.push_back(tab_num);
				}
			}
			else {
				if (tab_offsets_odd.end() == std::find(tab_offsets_odd.begin(), tab_offsets_odd.end(), tab_num)) {
					tab_offsets_odd.push_back(tab_num);
				}
			}

			string class_name = "code_line_";
			class_name += (is_even ? "even_" : "odd_");
			class_name += std::to_string(tab_num);

			dom.set({ "body", "table", tr_name }, Dom::item::td, " class = " + class_name, line, "line_code_" + std::to_string(line_idx + 1), 0);	

			is_even = !is_even;

			line_idx++;
			std::cout << '\r' << short_name << " : " << line_idx << " / " << codeLines.size();
		}
		cout << endl;

		string style_str = "\n<!-- ";

		for (auto item : tab_offsets_even) {
			style_str += "\n.code_line_even_" + std::to_string(item) + \
				" { padding-left: " + std::to_string(20 + item * 40) + "px; background: #e6e6f2; }";
		}

		for (auto item : tab_offsets_odd) {
			style_str += "\n.code_line_odd_" + std::to_string(item) + \
				" { padding-left: " + std::to_string(20 + item * 40) + "px; background: #c1d5f5; }";
		}

		style_str += "\n.num_colon { background: #8d8d94; padding-left: 20px; color: #58c6fc; width: 50px;}";
		style_str += "\n.table {border-spacing: 0px; margin: 0px; width: 100%;}";
		style_str += "\n.body {padding: 0px; margin: 0px;}";
		style_str += "\n-->";
		dom.set({ "head" }, Dom::item::style, " text = \"text/css\"", style_str, "style", 0);

		dom.make_doc();
	}
}

void Target::make_token_generators(std::shared_ptr<vector<string>> res) const
{
	vector<TokenGenerator*> tGenerators;

	for (auto p_file_name = res->begin(); p_file_name != res->end(); ++p_file_name) {

		bool add_to_vector = true;
		for (auto token : tGenerators) {

			if (token->equal(*p_file_name)) {
				add_to_vector = false;
				break;
			}
		}

		if (add_to_vector) {
			tGenerators.push_back(new TokenGenerator(*p_file_name));
		}
	}

	string to_file;
	for (auto t : tGenerators) {
		t->parse(m_source_dir.size(), m_output_dir + "\\\\tokens\\\\descr", &to_file);
	}

	ofstream fTokenList(m_output_dir + "\\\\tokens\\\\descr\\\\_token_list.txt");
	fTokenList << to_file;
	fTokenList.close();
}

void Target::make_source_token_out() const
{
	FileHandler fTokenList(m_output_dir + "\\\\tokens\\\\descr\\\\_token_list.txt");

	auto file_names = StringHandler::split(fTokenList.getAsString(), '\n');

	for (auto name : file_names) {
		std::experimental::filesystem::path name_(m_output_dir + "\\\\tokens\\\\descr\\\\" + name);
		if (std::experimental::filesystem::exists(name_)) {
			if (".rst" == name_.extension()) {
				RstHandler rstH(name_.string(), m_output_dir + "\\\\tokens\\\\html");
				rstH.write2html();
			}
		}
	}
}

void Target::make_functional_page() const
{

	string content = "..ext-d-state:: true\n\n";
	content += ".. ext-d-version:: " + string(PROJECT_VERSION) + "\n\n";
	content += ".. ext-d-nav:: index | functional | tokens | sources\n\n";
	content += ".. ext-d-paragraph:: Функционал\n\n";
	content += "Функционал\n";

	RstHandler rstH("functional.rst", m_output_dir, content);
	rstH.write2html();
}

void Target::make_tokens_page() const
{
	string content = "..ext-d-state:: true\n\n";
	content += ".. ext-d-version:: " + string(PROJECT_VERSION) + "\n\n";
	content += ".. ext-d-nav:: index | functional | tokens | sources\n\n";
	content += ".. ext-d-paragraph:: Токены\n\n";
	content += "Токены\n";

	RstHandler rstH("tokens.rst", m_output_dir, content);
	rstH.write2html();
}

void Target::make_sources_page() const
{
	string content = "..ext-d-state:: true\n\n";
	content += ".. ext-d-version:: " + string(PROJECT_VERSION) + "\n\n";
	content += ".. ext-d-nav:: index | functional | tokens | sources\n\n";
	content += ".. ext-d-paragraph:: Исходный код\n\n";
	content += "Исходный код\n";

	RstHandler rstH("sources.rst", m_output_dir, content);
	rstH.write2html();
}

/*!
 * Генератор индекс-файла.
 * 
*/
void Target::make_main_out() const
{
	string index_name = m_source_dir + "\\\\" + m_fileTree->getIndexRstName();
	RstHandler rstH(index_name, m_output_dir);
	rstH.write2html();
}
