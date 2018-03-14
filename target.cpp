#include "target.h"

namespace fs = std::experimental::filesystem;

Target::Target(const wstring & name_, const wstring & path_, std::shared_ptr<ErrorStatus> p_error_)
{

	flag_handlers = {
		{"-d", std::bind(&Target::flag_d_handler, this)},
		{"-m", std::bind(&Target::flag_m_handler, this)}
	};

#ifndef  TASK_0_3_1__1
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
#endif
	m_fileTree = nullptr;

	p_error = p_error_;
	m_name = name_;
#ifdef  TASK_0_3_1__1
	m_path = StringHandler::wstr2str(path_);
#else
	m_path = converter.to_bytes(path_);
#endif

	FileHandler file(m_path);
	if (!file.isExist()) {
		p_error->set(ErrorStatus::error::json_extdlists_no_exists, true);
		return;
	}

#ifdef  TASK_0_3_1__1
	JsonObject json_object(StringHandler::str2wstr(file.getAsString()), L"root", p_error_);
#else
	string tmp = file.getAsString();
	wstring wtmp = converter.from_bytes(tmp);
	JsonObject json_object(wtmp, L"root", p_error_);
#endif

	JsonBase::eType type;

	auto source_dir = json_object.get({ L"source-dir" }, &type);
	try {
#ifdef  TASK_0_3_1__1
		m_source_dir = StringHandler::wstr2str(
			StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(source_dir), L'/', L'\\')
		);
#else
		m_source_dir = converter.to_bytes(
			StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(source_dir), L'/', L'\\')
		);
#endif
	}
	catch (const std::bad_variant_access&) {
		p_error->set(ErrorStatus::error::json_extdlists_source_dir_inv, true);
	}

	auto out_dir = json_object.get({ L"out-dir" }, &type);
	try
	{
#ifdef TASK_0_3_1__1
		m_output_dir = StringHandler::wstr2str(
			StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(out_dir), L'/', L'\\')
		);
#else
		m_output_dir = converter.to_bytes(
			StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(out_dir), L'/', L'\\')
		);
#endif
	}
	catch (const std::bad_variant_access&)
	{
		p_error->set(ErrorStatus::error::json_extdlists_out_dir_inv, true);
	}

	auto lang = json_object.get({ L"lang" }, &type);
	string supp_lang;
	try
	{
#ifdef   TASK_0_3_1__1
		supp_lang = StringHandler::wstr2str(
			StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(lang), '/', '\\')
		);
#else
		supp_lang = converter.to_bytes(
			StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(lang), '/', '\\')
		);
#endif
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
#ifdef  TASK_0_3_1__1
			unhand_files.push_back(
				StringHandler::wstr2str(
					StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(o_unhand_files), L'/', L'\\')
				)
			);
#else
			unhand_files.push_back(converter.to_bytes(
				StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(o_unhand_files), L'/', L'\\')
			));
#endif
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
#ifdef TASK_0_3_1__1
			unhand_dir.push_back(
				StringHandler::wstr2str(
					StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(o_unhand_directory), L'/', L'\\')
				)
			);
#else
			unhand_dir.push_back(converter.to_bytes(
				StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(o_unhand_directory), L'/', L'\\')
			));
#endif
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
#ifdef  TASK_0_3_1__1
		tokens_path = StringHandler::wstr2str(
			StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(o_tokens_path), L'/', L'\\')
		);
#else
		tokens_path = converter.to_bytes(
			StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(o_tokens_path), L'/', L'\\')
		);
#endif
	}
	catch (std::bad_variant_access&) {
		p_error->set(ErrorStatus::error::json_extdlists_inv_tokens_path, true);
	}

	//
	// �������� ��������� user-relative
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
	// �������� ��������� user-path
	//
	auto o_user_path = json_object.get({L"user", L"path"}, &type);
	string user_path;
	try {
#ifdef   TASK_0_3_1__1
		user_path = StringHandler::wstr2str(
			StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(o_user_path), L'/', L'\\')
		);
#else
		user_path = converter.to_bytes(
			StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(o_user_path), L'/', L'\\')
		);
#endif
	}
	catch (std::bad_variant_access&) {
		p_error->set(ErrorStatus::error::json_extdlists_inv_user_path, true);
	}

	if (0 == p_error->get()) {

		if (JsonBase::eSimple::simple_true == tokens_relative) {
			m_tokens_output = m_output_dir + tokens_path;
		}
		else {
			m_tokens_output = tokens_path;
		}

		m_tokens_list_file_path = m_tokens_output + "\\_tokens_list.json";

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
#ifdef  TASK_0_3_1__1
	return StringHandler::wstr2str(m_name);
#else
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	return converter.to_bytes(m_name);
#endif
}

void Target::toConsole() const
{
	std::wcout << endl;
	std::wcout << L"Target Name\t\t : " << m_name << endl;
	std::wcout << L"Error Status\t\t : " << p_error->get() << endl;

	if (!p_error->get()) {
		cout << "Param Source Dir\t : " << m_source_dir << endl;
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

	auto iter = flag_handlers.find(flag_);
	if (flag_handlers.end() != iter)
	{
		iter->second();
	}
	else
	{
		p_error->set(ErrorStatus::error::target_invalidFlag, true);
	}
}

void Target::flag_d_handler() {

	std::shared_ptr<vector<string>> res(new vector<string>());
	m_fileTree->filePaths(res, true);

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

	vector<std::experimental::filesystem::path> file_paths;
	for (auto t : tGenerators) {
		t->parse(m_source_dir.size(), m_tokens_output, &file_paths);
	}

#ifndef  TASK_0_3_1__1
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
#endif

	JsonObject json_object(L"root");
	json_object.set({}, L"file_paths", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());

	std::set<std::experimental::filesystem::path> uniq_file_paths;
	for (auto iter : file_paths) {
		uniq_file_paths.emplace(iter);
	}

#ifdef  TASK_0_3_1__1
	json_object.set({}, L"numbers", JsonBase::eType::number, variant<wstring, double, JsonBase::eSimple>(double(uniq_file_paths.size())));
#else
	json_object.set({}, L"numbers", JsonBase::eType::number, variant<wstring, double, JsonBase::eSimple>(uniq_file_paths.size()));
#endif

	size_t idx = 0;
	for (auto iter : uniq_file_paths) {
		string tmp = StringHandler::replace_all<string, char>(iter.string(), '\\', '/');
#ifdef  TASK_0_3_1__1
		json_object.set({ L"file_paths" }, L"path_" + std::to_wstring(idx++), JsonBase::eType::string,
			variant<wstring, double, JsonBase::eSimple>(StringHandler::str2wstr(tmp)));
#else
		json_object.set({ L"file_paths" }, L"path_" + std::to_wstring(idx++), JsonBase::eType::string,
			variant<wstring, double, JsonBase::eSimple>(converter.from_bytes(tmp)));
#endif
	}

	json_object.write(m_tokens_list_file_path, "json", true);
}

void Target::flag_m_handler() {

	//
	// ��������� ���� �������� ������� �� ����� _token_list.json
	//
	FileHandler file(m_tokens_list_file_path);

#ifdef  TASK_0_3_1__1
	JsonObject json_object(StringHandler::str2wstr(file.getAsString()), L"root", p_error);
#else
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	JsonObject json_object(converter.from_bytes(file.getAsString()), L"root", p_error);
#endif

	JsonBase::eType type;
	auto o_numbers = json_object.get({L"numbers"}, &type);
	size_t numbers = 0;
	try {
		double tmp = std::get<double>(o_numbers);
		numbers = 0 > tmp ? 0 : size_t(tmp);
		
		if (0 == numbers) {
			p_error->set(ErrorStatus::error::tokenList_file_paths_empty, true);
		}
	}
	catch (std::bad_variant_access&) {
		p_error->set(ErrorStatus::error::tokenList_invalid_numbes, true);
	}

	if (0 != p_error->get()) {
		return;
	}

	std::shared_ptr<vector<TokenPath>> file_list(new vector<TokenPath>());
	for (size_t i = 0; i < numbers; ++i) {
		auto o_file_path = json_object.get({L"file_paths", L"file_paths_" + std::to_wstring(i)}, &type);
		try {
			wstring file_path = std::get<wstring>(o_file_path);
			//
			// ���������� �� ���� �� ������?
			//
			if (!std::experimental::filesystem::exists(file_path)) {
				p_error->set(ErrorStatus::error::tokenList_file_no_exists, true);
				break;
			}
			file_list->push_back(TokenPath(file_path));
		}
		catch (std::bad_variant_access&) {
			p_error->set(ErrorStatus::error::tokenList_invalid_file_paths, true);
			break;
		}
	}

	if (0 != p_error->get()) {
		return;
	}

	//
	// ��������� ���� ���������������� ������
	//
	if (!std::experimental::filesystem::exists(m_user_output)) {
		p_error->set(ErrorStatus::error::user_directory_no_exists, true);
		return;
	}

	for (auto & iter : fs::directory_iterator(m_user_output)) {
		
		if (fs::file_type::regular == iter.status().type() && ".ipynb" == iter.path().extension()) {
#ifdef  TASK_0_3_1__1
			WFileHandler wfile(StringHandler::str2wstr(iter.path().string()));
#else
			WFileHandler wfile(converter.from_bytes(iter.path().string()));
#endif
			JsonObject json_object(wfile.wstring(), L"root", p_error);

			JsonBase::eType type;
			size_t cells_idx = 0;			
			while (true) {

				//
				// ���������� �� ������� � �������� cells_idx
				//
				auto o_cells = json_object.get({L"cells", L"cells_" + std::to_wstring(cells_idx)}, &type);
				JsonBase::eGetterMsg msg;
				try {
					msg = std::get<JsonBase::eGetterMsg>(o_cells);
					if (JsonBase::eGetterMsg::is_object != msg) {
						break;
					}
				}
				catch (std::bad_variant_access&) {
					break;
				}

				size_t source_idx = 0;
				while (true) {

					//
					// ���������� �� ������ � �������� source_idx
					//
					auto o_source = json_object.get({L"cells", L"cells_" + std::to_wstring(cells_idx), L"source", L"source_" + std::to_wstring(source_idx)},&type);
					wstring source;
					try {
						source = std::get<wstring>(o_source);
						PartedLine pline(source, file_list);
						json_object.reset({ L"cells", L"cells_" + std::to_wstring(cells_idx), L"source", L"source_" + std::to_wstring(source_idx) }, 
							variant<wstring, double, JsonBase::eSimple>(pline.processedWString()));
					}
					catch (std::bad_variant_access&) {
						break;
					}

					source_idx++;
				}

				cells_idx++;
			}

			json_object.write(iter.path().string(),"", true);
		}
	}

}
