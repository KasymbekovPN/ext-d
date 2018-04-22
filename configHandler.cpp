#include "configHandler.h"

ConfigHandler::ConfigHandler(const string& path_json_, shared_ptr<ErrorStatus> p_error_)
{

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
            variantItem<JsonBase::eGetterMsg> msg =
                    json_object.variantExp<JsonBase::eGetterMsg>({array_name, array_name + L"_" + std::to_wstring(num_of_targets)});

            if (JsonBase::eGetterMsg::is_object != msg.value || msg.except_flag)
            {
                break;
            }

            variantItem<wstring> target_name =
                    json_object.variantExp<wstring>({array_name, array_name + L"_" + std::to_wstring(num_of_targets), L"name" });
            variantItem<wstring> target_path =
                    json_object.variantExp<wstring>({ array_name, array_name + L"_" + std::to_wstring(num_of_targets), L"path" });

            if (!target_name.except_flag && !target_path.except_flag)
            {
                target_buffer.push_back(pair<wstring, wstring>(
                            StringHandler::replace_all<wstring, wchar_t>(target_name.value, L'/', L'\\'),
                            StringHandler::replace_all<wstring, wchar_t>(target_path.value, L'/', L'\\')
                            ));

                num_of_targets++;
            }
            else
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
