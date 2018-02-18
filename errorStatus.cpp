#include "errorStatus.h"

ErrorStatus::ENM ErrorStatus::errorNamesMap {
	{ ErrorStatus::error::consoleCmdHand_listCmdIsEmpty, "Ќи одна консольна€ команда не задана." },
	{ ErrorStatus::error::consoleCmdHand_invalidConsoleCmd, "Ќевалидна€ команда."},
	{ ErrorStatus::error::consoleCmdHand_helpHandInvalidArg, "Ќевалидный список аргументов --help."},
	{ ErrorStatus::error::consoleCmdHand_verHandInvalidArg, "Ќевалидный список аргументов --version."},
	{ ErrorStatus::error::consoleCmdHand_tarShowAllInvalidArg, "Ќевалидный список аргументов --target.show.all." },
	{ ErrorStatus::error::consoleCmdHand_tarShowInvalidArg, "Ќевалидный список аргументов --target.show" },
	{ ErrorStatus::error::consoleCmdHand_tarRunInvalidArg, "Ќевалидный список аргументов --target.run" },
	{ ErrorStatus::error::configHand_cnfgFileNoExitst, " онфигурационный файл не существует." },
	{ ErrorStatus::error::configHand_cmdSetTargetInvalid, "Ќевалидна€ команда SETTARGET." },
	{ ErrorStatus::error::configHand_targetRun_targetNoExists, "÷ель не существует." },
	{ ErrorStatus::error::configHand_noTargetSpec, "Ќи одной цели не задано." },
	{ ErrorStatus::error::configHand_currentTargetNoExists, "»скома€ цель не существует." },
	{ ErrorStatus::error::target_outputDirInvalidParam, "Ќевалидный параметр SET_OUTPUT_DIR." },
	{ ErrorStatus::error::target_sourceDirInvalidParam, "Ќевалидный параметр SET_SOURCE_DIR." },
	{ ErrorStatus::error::target_outputDirNoExists, "ƒиректори€ out_dir не существует." },
	{ ErrorStatus::error::target_sourceDirNoExists, "ƒиректори€ source_dir не существует." },
	{ ErrorStatus::error::target_unknowLang, "Target - неизвестный €зык." },
	{ ErrorStatus::error::target_invalidFlag, "Target - невалидный флаг."},
	{ ErrorStatus::error::fileTree_unknowLang, "FileTree - неизвестный €зык." },
	{ ErrorStatus::error::fileTree_noExists, "FileTree - не удалось сформировать."},
	{ ErrorStatus::error::json_objectInvalid, "Json - ќбъект невалиден."},
	{ ErrorStatus::error::json_invalidSyntax, "Json - невалидный синтаксис."},
	{ ErrorStatus::error::json_cnfg_num_of_trt_inv, "Json-conf - невалидный параметр : numder-of-targets"},
	{ ErrorStatus::error::json_cnfg_inv_target_name, "Json-conf - невалидный параметр цели : name"},
	{ ErrorStatus::error::json_cnfg_inv_target_path, "Json-conf - невалидный параметр цели : path" },
	{ ErrorStatus::error::json_extdlists_no_exists, "Json-conf - файл описани€ цели не существует."},
	{ ErrorStatus::error::json_extdlists_source_dir_inv, "ExtDLists - невалидный параметр source_dir"},
	{ ErrorStatus::error::json_extdlists_out_dir_inv, "ExtDLists - невалидный параметр out_dir" },
	{ ErrorStatus::error::json_extdlists_lang_inv, "ExtDLists - невалидный параметр lang" },
	{ ErrorStatus::error::json_extdlists_inv_num_unhand_files, "ExtDLists - невалидное количество необраб. файлов"},
	{ ErrorStatus::error::json_extdlists_inv_unhand_files, "ExtDLists - невалидно заданные необраб. файлы"},
	{ ErrorStatus::error::json_extdlists_inv_num_unhand_dir, "ExtDLists - невалидное количество необраб. директорий"},
	{ ErrorStatus::error::json_extdlists_inv_unhand_dir, "ExtDLists - невалидно заданые необраб. директории"},
	{ ErrorStatus::error::json_extdlists_inv_tokens_rel, "ExiDLists - невадидный параметр tokens-relative"},
	{ ErrorStatus::error::json_extdlists_inv_tokens_path, "ExtDLists - невадидный параметр tokens-path"},
#ifdef  TASK_27__1
	{ ErrorStatus::error::json_extdlists_inv_user_rel, "ExtDLists - невалидный параметр user-rel."},
	{ ErrorStatus::error::json_extdlists_inv_user_path, "ExtDLists - невалидный параметр user-path."},
#endif
#ifdef  TASK_3_0__1
	{ ErrorStatus::error::tokenList_invalid_numbes, "_tokens_list - невалидный параметр numbers."},
	{ ErrorStatus::error::tokenList_invalid_file_paths, "_token_list - невалидный параметр file_paths."},
	{ ErrorStatus::error::tokenList_file_paths_empty, "_token_list - file_paths пуст."},
	{ ErrorStatus::error::tokenList_file_no_exists, "_token_list - файл из списка не существует."},
	{ ErrorStatus::error::user_directory_no_exists, "ƒиректори€ с пользовательскими файлами не существует."}
#endif
};

ErrorStatus::ErrorStatus(): value(0){}

void ErrorStatus::clear()
{
	value = 0;
}

void ErrorStatus::set(error error_, bool act_)
{
	if (act_) {
		value |= unsigned long long(1) << unsigned long long(error_);
	}
	else {
		value &= ~(unsigned long long(1) << unsigned long long(error_));
	}
}

void ErrorStatus::set(ErrorStatus error_)
{
	value |= error_.get();
}

unsigned long long ErrorStatus::get()
{
	return value;
}

void ErrorStatus::display() const
{

	for (auto iter = errorNamesMap.begin(); iter != errorNamesMap.end(); ++iter) {

		if (value & (unsigned long long(1) << int(iter->first))) {
			cout << int(iter->first) << ") " << iter->second << endl;
		}
	}
}
