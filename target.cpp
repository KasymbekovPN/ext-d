#include "target.h"

namespace fs = std::experimental::filesystem;

Target::Target(const wstring & name_, const wstring & path_, std::shared_ptr<ErrorStatus> p_error_)
{

	flag_handlers = {
		{"-d", std::bind(&Target::flag_d_handler, this)},
		{"-m", std::bind(&Target::flag_m_handler, this)}
	};

	m_fileTree = nullptr;

	p_error = p_error_;
	m_name = name_;
	m_path = StringHandler::wstr2str(path_);

	FileHandler file(m_path);
	if (!file.isExist()) {
		p_error->set(ErrorStatus::error::json_extdlists_no_exists, true);
		return;
	}

    JsonObject json_object(StringHandler::str2wstr(file.getAsString()), L"root", p_error_);

    variantItem<wstring> vi_source_dir = json_object.variantExp<wstring>({ L"source-dir" },
                                                                         ErrorStatus::error::json_extdlists_source_dir_inv);
    if (!vi_source_dir.except_flag)
    {
        m_source_dir = StringHandler::wstr2str(
            StringHandler::replace_all<wstring, wchar_t>(vi_source_dir.value, L'/', L'\\')
        );
    }

    variantItem<wstring> vi_output_dir = json_object.variantExp<wstring>({ L"out-dir" },
                                                                         ErrorStatus::error::json_extdlists_out_dir_inv);
    if (!vi_output_dir.except_flag)
    {
        m_output_dir = StringHandler::wstr2str(
            StringHandler::replace_all<wstring, wchar_t>(vi_output_dir.value, L'/', L'\\')
        );
    }

    variantItem<wstring> vi_supp_lang = json_object.variantExp<wstring>({ L"lang" },
                                                                        ErrorStatus::error::json_extdlists_lang_inv);
    string supp_lang;
    if (!vi_supp_lang.except_flag)
    {
        supp_lang = StringHandler::wstr2str(
            StringHandler::replace_all<wstring, wchar_t>(vi_supp_lang.value, '/', '\\')
        );
    }

	//
	// Проверяем наличие массива имен необрабатываемых файлов.
	//
    variantItem<JsonObject::eGetterMsg> vi_unhand_file_array = json_object.variantExp<JsonBase::eGetterMsg>(
                {L"unhandled", L"files", L"names"}
                );

    if (vi_unhand_file_array.except_flag || JsonBase::eGetterMsg::is_array != vi_unhand_file_array.value)
    {
        p_error->set(ErrorStatus::error::json_extdlists_inv_unhand_file_array, true);
    }

    //
	// Проверяем наличие массива имен необрабатываемых директорий.
	//

    variantItem<JsonBase::eGetterMsg> vi_unhand_dir_array = json_object.variantExp<JsonBase::eGetterMsg>(
                {L"unhandled", L"directory", L"names"}
                );

    if (vi_unhand_dir_array.except_flag || JsonBase::eGetterMsg::is_array != vi_unhand_dir_array.value)
    {
        p_error->set(ErrorStatus::error::json_extdlists_inv_unhand_dir_array, true);
    }

	//
	// Опрделяем списки необрабатываемых директорий и файлов.
	//
	vector<string> unhand_files;
	vector<string> unhand_dir;
	if (0 == p_error->get())
	{
		size_t idx = 0;
		while (true)
		{

            variantItem<wstring> vi_unhand_file = json_object.variantExp<wstring>(
                        {L"unhandled", L"files", L"names", L"names_" + std::to_wstring(idx++)});

            if (!vi_unhand_file.except_flag)
            {
                unhand_files.push_back(
                    StringHandler::wstr2str(
                        StringHandler::replace_all<wstring, wchar_t>(vi_unhand_file.value, L'/', L'\\')
                    )
                );
            }
            else
            {
                break;
            }
		}

		idx = 0;
		while (true)
		{
            variantItem<wstring> vi_unhand_directory = json_object.variantExp<wstring>(
                        {L"unhandled", L"directory", L"names", L"names_" + std::to_wstring(idx++)});

            if (!vi_unhand_directory.except_flag)
            {
                unhand_dir.push_back(
                    StringHandler::wstr2str(
                        StringHandler::replace_all<wstring, wchar_t>(vi_unhand_directory.value, L'/', L'\\')
                    )
                );
            }
            else
            {
                break;
            }
		}
	}

	//
	// Получаем путь (относительный) до пааки с файлами-токенами.
	//
    variantItem<wstring> vi_token_path = json_object.variantExp<wstring>({L"tokens", L"path"},
                                                                         ErrorStatus::error::json_extdlists_inv_tokens_path);

    string token_path;
    if (!vi_token_path.except_flag)
    {
        token_path = StringHandler::wstr2str(
            StringHandler::replace_all<wstring, wchar_t>(vi_token_path.value, L'/', L'\\')
        );
    }

	//
	// Получаем путь (относительный) до папки с пользовательскими файлами.
	//
    variantItem<wstring> vi_user_path = json_object.variantExp<wstring>({L"user", L"path"},
                                                                        ErrorStatus::error::json_extdlists_inv_user_path);

    string user_path;
    if (!vi_user_path.except_flag)
    {
        user_path = StringHandler::wstr2str(
            StringHandler::replace_all<wstring, wchar_t>(vi_user_path.value, L'/', L'\\')
        );
    }

	if (0 == p_error->get()) {

		//
		// Получаем полные пути до:
		// 1. Папки с файлами-токенами.
		// 2. Папки с пользовательскими файлами.
		// 3. Файла со списком файлов-токенов.
		//
		m_tokens_output = m_output_dir + token_path;
		m_relative_tokens_output = token_path;
        m_user_output = m_output_dir + user_path;
		m_tokens_list_file_path = m_tokens_output + "\\_tokens_list.json";

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
	return StringHandler::wstr2str(m_name);
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

	JsonObject json_object(L"root");
	json_object.set({}, L"file_paths", JsonBase::eType::array, variant<wstring, double, JsonBase::eSimple>());

	std::set<std::experimental::filesystem::path> uniq_file_paths;
	for (auto iter : file_paths) {
		uniq_file_paths.emplace(iter);
	}

	size_t idx = 0;
	for (auto iter : uniq_file_paths) {
		string tmp = StringHandler::replace_all<string, char>(iter.string(), '\\', '/');
		json_object.set({ L"file_paths" }, L"path_" + std::to_wstring(idx++), JsonBase::eType::string,
			variant<wstring, double, JsonBase::eSimple>(StringHandler::str2wstr(tmp)));
	}

	json_object.write(m_tokens_list_file_path, "json", true);
}

void Target::flag_m_handler() {

	FileHandler file(m_tokens_list_file_path);

	JsonObject json_object(StringHandler::str2wstr(file.getAsString()), L"root", p_error);

	JsonBase::eType type;
	size_t idx = 0;
	std::shared_ptr<vector<TokenPath>> file_list(new vector<TokenPath>());
	while (true)
	{
		auto o_file_path = json_object.get({L"file_paths", L"file_paths_" + std::to_wstring(idx++)}, &type);
		try
		{
			wstring file_path = std::get<wstring>(o_file_path);

			if (!std::experimental::filesystem::exists(file_path))
			{
				p_error->set(ErrorStatus::error::tokenList_file_no_exists, true);
				break;
			}
			file_list->push_back(TokenPath(file_path));
		}
		catch (std::bad_variant_access&)
		{
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
			WFileHandler wfile(StringHandler::str2wstr(iter.path().string()));
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
						PartedLine pline(source, file_list, m_relative_tokens_output);
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
