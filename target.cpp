#include "target.h"

const int Target::cmd_size[Target::number_of_cmd] = {2, 2};

Target::Target(const wstring & name_, const wstring & path_, std::shared_ptr<ErrorStatus> p_error_)
{

	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	m_fileTree = nullptr;

	p_error = p_error_;
	m_name = name_;
	m_path = converter.to_bytes(path_);

	FileHandler file(m_path);
	if (!file.isExist()) {
		p_error->set(ErrorStatus::error::json_extdlists_no_exists, true);
		return;
	}

	string tmp = file.getAsString();
	wstring wtmp = converter.from_bytes(tmp);

	JsonObject json_object(wtmp, L"root", p_error_);
	JsonBase::eType type;

	auto source_dir = json_object.get({ L"source-dir" }, &type);
	try {
		m_source_dir = converter.to_bytes(
			StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(source_dir), L'/', L'\\')
		);
	}
	catch (const std::bad_variant_access&) {
		p_error->set(ErrorStatus::error::json_extdlists_source_dir_inv, true);
	}

	auto out_dir = json_object.get({ L"out-dir" }, &type);
	try
	{
		m_output_dir = converter.to_bytes(
			StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(out_dir), L'/', L'\\')
		);
	}
	catch (const std::bad_variant_access&)
	{
		p_error->set(ErrorStatus::error::json_extdlists_out_dir_inv, true);
	}

	auto lang = json_object.get({ L"lang" }, &type);
	string supp_lang;
	try
	{
		supp_lang = converter.to_bytes(
			StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(lang), '/', '\\')
		);
	}
	catch (const std::bad_variant_access&)
	{
		p_error->set(ErrorStatus::error::json_extdlists_lang_inv, true);
	}

	auto o_number_unhand_files = json_object.get({ L"unhandled", L"files", L"number" }, &type);
	size_t number_unhand_files = 0;
	try {
		double tmp = std::get<double>(o_number_unhand_files);
		number_unhand_files = tmp < 0 ? 0 : size_t(tmp);
	}
	catch (std::bad_variant_access&) {
		number_unhand_files = 0;
		p_error->set(ErrorStatus::error::json_extdlists_inv_num_unhand_files, true);
	}

	vector<string> unhand_files;
	for (size_t i = 0; i < number_unhand_files; ++i) {
		auto o_unhand_files = json_object.get({ L"unhandled", L"files", L"names", L"names_" + std::to_wstring(i) }, &type);
		try {
			unhand_files.push_back(converter.to_bytes(
				StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(o_unhand_files), L'/', L'\\')
			));
		}
		catch (std::bad_variant_access&) {
			unhand_files.clear();
			p_error->set(ErrorStatus::error::json_extdlists_inv_unhand_files, true);
			break;
		}
	}

	auto o_number_unhand_dir = json_object.get({ L"unhandled", L"directory", L"number" }, &type);
	size_t number_unhand_directory = 0;
	try {
		double tmp = std::get<double>(o_number_unhand_dir);
		number_unhand_directory = tmp < 0 ? 0 : size_t(tmp);
	}
	catch (std::bad_variant_access&) {
		number_unhand_directory = 0;
		p_error->set(ErrorStatus::error::json_extdlists_inv_num_unhand_dir, true);
	}

	vector<string> unhand_dir;
	for (size_t i = 0; i < number_unhand_directory; ++i) {
		auto o_unhand_directory = json_object.get({ L"unhandled", L"directory", L"names", L"names_" + std::to_wstring(i) }, &type);
		try {
			unhand_dir.push_back(converter.to_bytes(
				StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(o_unhand_directory), L'/', L'\\')
			));
		}
		catch (std::bad_variant_access&) {
			unhand_dir.clear();
			p_error->set(ErrorStatus::error::json_extdlists_inv_unhand_dir, true);
			break;
		}
	}

	auto o_tokens_relative = json_object.get({ L"tokens", L"relative" }, &type);
	JsonBase::eSimple tokens_relative;
	try {
		tokens_relative = std::get<JsonBase::eSimple>(o_tokens_relative);
	}
	catch (std::bad_variant_access&) {
		p_error->set(ErrorStatus::error::json_extdlists_inv_tokens_rel, true);
	}

	auto o_tokens_path = json_object.get({ L"tokens", L"path" }, &type);
	string tokens_path;
	try {
		tokens_path = converter.to_bytes(
			StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(o_tokens_path), L'/', L'\\')
		);
	}
	catch (std::bad_variant_access&) {
		p_error->set(ErrorStatus::error::json_extdlists_inv_tokens_path, true);
	}

#ifdef  TASK_27__1
	//
	// Вызрузка параметра user-relative
	//
	auto o_user_relative = json_object.get({L"user", L"relative"}, &type);
	JsonBase::eSimple user_relative;
	try{
		user_relative = std::get<JsonBase::eSimple>(o_user_relative);
	}
	catch (std::bad_variant_access&) {
		p_error->set(ErrorStatus::error::json_extdlists_inv_user_rel, true);
	}

	//
	// Выгрузка параметра user-path
	//
	auto o_user_path = json_object.get({L"user", L"path"}, &type);
	string user_path;
	try {
		user_path = converter.to_bytes(
			StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(o_user_path), L'/', L'\\')
		);
	}
	catch (std::bad_variant_access&) {
		p_error->set(ErrorStatus::error::json_extdlists_inv_user_path, true);
	}
#endif

	if (0 == p_error->get()) {

		if (JsonBase::eSimple::simple_true == tokens_relative) {
			m_tokens_output = m_output_dir + tokens_path;
		}
		else {
			m_tokens_output = tokens_path;
		}

		if (JsonBase::eSimple::simple_true == user_relative) {
			m_user_output = m_output_dir + user_path;
		}
		else {
			m_user_output = user_path;
		}

		if (!std::experimental::filesystem::exists(m_source_dir)) {
			p_error->set(ErrorStatus::error::target_sourceDirNoExists, true);
		}

		if (!std::experimental::filesystem::exists(m_output_dir)) {
			p_error->set(ErrorStatus::error::target_outputDirNoExists, true);
		}

		m_fileTree = new FileTree(m_source_dir, p_error, supp_lang, unhand_files, unhand_dir);
	}
}

Target::~Target()
{
	if (nullptr != m_fileTree) {
		delete m_fileTree;
	}
}

wstring Target::getWName() const
{
	return m_name;
}

string Target::getName() const
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	return converter.to_bytes(m_name);
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
	std::wcout << endl;
	std::wcout << L"Target Name\t\t : " << m_name << endl;
	std::wcout << L"Error Status\t\t : " << p_error->get() << endl;

	if (!p_error->get()) {
		cout << L"Param Source Dir\t : " << m_source_dir << endl;
		cout << "Param Output Dir\t : " << m_output_dir << endl;
	}

	cout << endl;
}

void Target::run(const string& flag_) const
{

	if (nullptr == m_fileTree) {
		p_error->set(ErrorStatus::error::fileTree_noExists, true);
		return;
	}

	std::shared_ptr<vector<string>> res(new vector<string>());
	m_fileTree->filePaths(res, true);

	if (tgt_flg_d == flag_) {
		//----не-удалять----------
		make_token_generators(res);
		//------------------------
	}
	else if (tgt_flg_m == flag_) {
		//----не-удалять----------
		//make_source_out(res);
		//make_source_token_out();
		////make_functional_out();
		//make_functional_page();
		//make_tokens_page();
		//make_sources_page();
		//make_main_out();
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

#ifdef  TASK_27__1

	vector<std::experimental::filesystem::path> file_paths;
	for (auto t : tGenerators) {
		t->parse(m_source_dir.size(), m_tokens_output, &file_paths);
	}

	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

	JsonObject json_object(L"root");
	json_object.set({}, L"file_paths", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());

	
	for (size_t i = 0; i < file_paths.size(); ++i) {
		json_object.set({ L"file_paths" }, L"path_" + std::to_wstring(i), JsonBase::eType::string, 
			variant<wstring, double, JsonBase::eSimple>(converter.from_bytes(file_paths[i].string())));
	}

	json_object.write(m_tokens_output + "\\_tokens_list.json", "json", true);
#else

	string to_file;
	for (auto t : tGenerators) {
		t->parse(m_source_dir.size(), m_tokens_output, &to_file);
	}

	cout << m_user_output << endl;

	ofstream fTokenList(m_tokens_output + "\\_token_list.txt");
	fTokenList << to_file;
	fTokenList.close();
#endif
}

void Target::make_source_token_out() const
{

	FileHandler fTokenList(m_output_dir + "\\tokens\\descr\\_token_list.txt");

	auto file_names = StringHandler::split(fTokenList.getAsString(), '\n');

	for (auto name : file_names) {
		std::experimental::filesystem::path name_(m_output_dir + "\\tokens\\descr\\" + name);
		if (std::experimental::filesystem::exists(name_)) {
			if (".rst" == name_.extension()) {
				RstHandler rstH(name_.string(), m_output_dir + "\\tokens\\html");
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
	string index_name = m_source_dir + "\\" + m_fileTree->getIndexRstName();
	RstHandler rstH(index_name, m_output_dir);
	rstH.write2html();
}
