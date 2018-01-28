#include "configHandler.h"

ConfigHandler::ConfigHandler(const string& path_json_, shared_ptr<ErrorStatus> p_error_)
{

	p_error = p_error_;

	FileHandler file_json(path_json_);
	if (!file_json.isExist()) {
		p_error->set(ErrorStatus::error::configHand_cnfgFileNoExitst, true);
		return;
	}

	JsonObject json_object(file_json.getAsString(), "root", p_error);

	if (0 == p_error->get()) {
		JsonBase::eType type;

		//
		// ���������� ���������� �����
		//
		auto number_of_targets = json_object.get({ "number-of-targets" }, &type);
		size_t size = 0;
		try
		{
			size = size_t(std::get<double>(number_of_targets));
		}
		catch (const std::bad_variant_access&)
		{
			p_error->set(ErrorStatus::error::json_cnfg_num_of_trt_inv, true);
		}

		vector<pair<string, string>> target_buffer;

		if (0 == p_error->get()) {

			for (size_t i = 0; i < size; ++i) {
				auto name = json_object.get({ "targets", "targets_" + std::to_string(i), "name"}, &type);
				auto path = json_object.get({ "targets", "targets_" + std::to_string(i), "path" }, &type);

				try
				{
					target_buffer.push_back(pair<string, string>(
						StringHandler::replace_all(std::get<string>(name), '/', '\\'),
						StringHandler::replace_all(std::get<string>(path), '/', '\\')
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
						if (p_target->getName() == item.first) {
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
