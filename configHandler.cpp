#include "configHandler.h"

ConfigHandler::ConfigHandler(const string& path_json_, shared_ptr<ErrorStatus> p_error_)
{

#ifdef  TASK_0_3_4__1

	p_error = p_error_;

	//
	// Если конфигурационный файл не существует,
	// то утсанавливаем соответствующую ошибку.
	//
	FileHandler file_json(path_json_);
	if (!file_json.isExist()) {
		p_error->set(ErrorStatus::error::configHand_cnfgFileNoExitst, true);
		return;
	}

	//
	// Получем из содержимого конфигурационног файла
	// json-объект.
	//
	string tmp = file_json.getAsString();
	JsonObject json_object(StringHandler::str2wstr(tmp), L"root", p_error);

	if (0 == p_error->get()) {
		JsonBase::eType type;

		vector<pair<wstring, wstring>> target_buffer;

		wstring array_name = L"targets";
		size_t num_of_targets = 0;

		//
		// Обрабатываем json-объекст, содержащий  имена целей 
		// и пути до файдов их описывающих.
		//
		while (true)
		{

			//
			// Проверяем следующий элемент в массиве с именем array_name.
			//
			auto o_target = json_object.get({array_name, array_name + L"_" + std::to_wstring(num_of_targets)}, &type);
			try
			{
				JsonBase::eGetterMsg msg = std::get<JsonBase::eGetterMsg>(o_target);
				if (JsonBase::eGetterMsg::is_object != msg)
				{
					break;
				}
			}
			catch (std::bad_variant_access&)
			{
				break;
			}

			auto o_target_name = json_object.get({array_name, array_name + L"_" + std::to_wstring(num_of_targets), L"name" }, &type);
			auto o_target_path = json_object.get({ array_name, array_name + L"_" + std::to_wstring(num_of_targets), L"path" }, &type);

			try
			{
				wstring target_name = std::get<wstring>(o_target_name);
				wstring target_path = std::get<wstring>(o_target_path);

				target_buffer.push_back(pair<wstring, wstring>(
					StringHandler::replace_all<wstring, wchar_t>(target_name, L'/', L'\\'),
					StringHandler::replace_all<wstring, wchar_t>(target_path, L'/', L'\\')
					));

				num_of_targets++;
			}
			catch (std::bad_variant_access&)
			{
				p_error->set(ErrorStatus::error::json_cnfg_inv_target_name, true);
				break;
			}
		}

		if (0 == num_of_targets)
		{
			p_error->set(ErrorStatus::error::json_cnfg_num_of_trt_inv, true);
			return;
		}

		if (0 == p_error->get()) {
			for (auto item : target_buffer) {
				bool need_add = true;
				for (auto p_target : m_targets) {
					if (p_target->getWName() == item.first) {
						need_add = false;
					}
				}

				if (need_add) {
					m_targets.push_back(new Target(item.first, item.second, p_error));
				}
			}
		}
	}

#else

	p_error = p_error_;

	FileHandler file_json(path_json_);
	if (!file_json.isExist()) {
		p_error->set(ErrorStatus::error::configHand_cnfgFileNoExitst, true);
		return;
	}

	string tmp = file_json.getAsString();
#ifdef  TASK_0_3_1__1
	JsonObject json_object(StringHandler::str2wstr(tmp), L"root", p_error);
#else
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	wstring wtmp = converter.from_bytes(tmp);
	JsonObject json_object(wtmp, L"root", p_error);
#endif	

	if (0 == p_error->get()) {
		JsonBase::eType type;

		//
		// Определяем количество целей
		//
		auto number_of_targets = json_object.get({ L"number-of-targets" }, &type);
		size_t size = 0;
		try
		{
			size = size_t(std::get<double>(number_of_targets));
		}
		catch (const std::bad_variant_access&)
		{
			p_error->set(ErrorStatus::error::json_cnfg_num_of_trt_inv, true);
		}

		vector<pair<wstring, wstring>> target_buffer;

		if (0 == p_error->get()) {

			for (size_t i = 0; i < size; ++i) {
				auto name = json_object.get({ L"targets", L"targets_" + std::to_wstring(i), L"name" }, &type);
				auto path = json_object.get({ L"targets", L"targets_" + std::to_wstring(i), L"path" }, &type);

				try
				{
					target_buffer.push_back(pair<wstring, wstring>(
						StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(name), L'/', L'\\'),
						StringHandler::replace_all<wstring, wchar_t>(std::get<wstring>(path), L'/', L'\\')
						));
				}
				catch (const std::bad_variant_access&)
				{
					p_error->set(ErrorStatus::error::json_cnfg_inv_target_name, true);
				}
				
				if (0 != p_error->get()) {
					break;
				}

			}

			if (0 == p_error->get()) {
				for (auto item : target_buffer) {
					bool need_add = true;
					for (auto p_target : m_targets) {
						if (p_target->getWName() == item.first) {
							need_add = false;
						}
					}

					if (need_add) {
						m_targets.push_back(new Target(item.first, item.second, p_error));
					}
				}
			}
		}
	}
#endif
}

ConfigHandler::~ConfigHandler()
{
	for (auto item : m_targets) {
		delete item;
	}
}

void ConfigHandler::targetRun(const string & target_name_, const string& flag_) const
{

	bool target_no_exists = true;

	for (auto target : m_targets) {
		if (target->getName() == target_name_) {
			target_no_exists = false;
			target->run(flag_);
		}
	}

	if (target_no_exists) {
		p_error->set(ErrorStatus::error::configHand_targetRun_targetNoExists, true);
	}
}

void ConfigHandler::showAllTarget() const
{
	if (m_targets.size() == 0) {
		p_error->set(ErrorStatus::error::configHand_noTargetSpec, true);
	}
	else {
		for (auto target : m_targets) {
			target->toConsole();
		}
	}
}

void ConfigHandler::showTarget(const string & target_name_) const
{
	p_error->set(ErrorStatus::error::configHand_currentTargetNoExists, true);

	for (auto target : m_targets) {
		if (target->getName() == target_name_) {
			p_error->set(ErrorStatus::error::configHand_currentTargetNoExists, false);
			target->toConsole();
		}
	}
}
