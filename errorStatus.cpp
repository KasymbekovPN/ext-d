#include "errorStatus.h"

ErrorStatus::ENM ErrorStatus::errorNamesMap {
	{ ErrorStatus::error::consoleCmdHand_listCmdIsEmpty, "Ни одна консольная команда не задана." },
	{ ErrorStatus::error::consoleCmdHand_invalidConsoleCmd, "Невалидная команда."},
	{ ErrorStatus::error::consoleCmdHand_helpHandInvalidArg, "Невалидный список аргументов --help."},
	{ ErrorStatus::error::consoleCmdHand_verHandInvalidArg, "Невалидный список аргументов --version."},
	{ ErrorStatus::error::consoleCmdHand_tarShowAllInvalidArg, "Невалидный список аргументов --target.show.all." },
	{ ErrorStatus::error::consoleCmdHand_tarShowInvalidArg, "Невалидный список аргументов --target.show" },
	{ ErrorStatus::error::consoleCmdHand_tarRunInvalidArg, "Невалидный список аргументов --target.run" },
	{ ErrorStatus::error::configHand_cnfgFileNoExitst, "Конфигурационный файл не существует." },
	{ ErrorStatus::error::configHand_cmdSetTargetInvalid, "Невалидная команда SETTARGET." },
	{ ErrorStatus::error::configHand_targetRun_targetNoExists, "Цель не существует." },
	{ ErrorStatus::error::configHand_noTargetSpec, "Ни одной цели не задано." },
	{ ErrorStatus::error::configHand_currentTargetNoExists, "Искомая цель не существует." },
	{ ErrorStatus::error::target_outputDirInvalidParam, "Невалидный параметр SET_OUTPUT_DIR." },
	{ ErrorStatus::error::target_sourceDirInvalidParam, "Невалидный параметр SET_SOURCE_DIR." },
	{ ErrorStatus::error::target_outputDirNoExists, "Директория out_dir не существует." },
	{ ErrorStatus::error::target_sourceDirNoExists, "Директория source_dir не существует." },
	{ ErrorStatus::error::target_unknowLang, "Target - неизвестный язык." },
	{ ErrorStatus::error::target_invalidFlag, "Target - невалидный флаг."},
	{ ErrorStatus::error::fileTree_unknowLang, "FileTree - неизвестный язык." },
	{ ErrorStatus::error::fileTree_noExists, "FileTree - не удалось сформировать."},
	{ ErrorStatus::error::json_objectInvalid, "Json - Объект невалиден."},
	{ ErrorStatus::error::json_invalidSyntax, "Json - невалидный синтаксис."},
	{ ErrorStatus::error::json_cnfg_num_of_trt_inv, "Json-conf - невалидный параметр : numder-of-targets"},
	{ ErrorStatus::error::json_cnfg_inv_target_name, "Json-conf - невалидный параметр цели : name"},
	{ ErrorStatus::error::json_cnfg_inv_target_path, "Json-conf - невалидный параметр цели : path" },
	{ ErrorStatus::error::json_extdlists_no_exists, "Json-conf - файл описания цели не существует."},
	{ ErrorStatus::error::json_extdlists_source_dir_inv, "ExtDLists - невалидный параметр source_dir"},
	{ ErrorStatus::error::json_extdlists_out_dir_inv, "ExtDLists - невалидный параметр out_dir" },
	{ ErrorStatus::error::json_extdlists_lang_inv, "ExtDLists - невалидный параметр lang" },
	{ ErrorStatus::error::json_extdlists_inv_num_unhand_files, "ExtDLists - невалидное количество необраб. файлов"},
	{ ErrorStatus::error::json_extdlists_inv_unhand_files, "ExtDLists - невалидно заданные необраб. файлы"},
	{ ErrorStatus::error::json_extdlists_inv_num_unhand_dir, "ExtDLists - невалидное количество необраб. директорий"},
	{ ErrorStatus::error::json_extdlists_inv_unhand_dir, "ExtDLists - невалидно заданые необраб. директории"},
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
