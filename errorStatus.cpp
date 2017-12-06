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
	{ ErrorStatus::error::target_outputDirNoExists, "Директория SET_OUTPUT_DIR не существует." },
	{ ErrorStatus::error::target_sourceDirNoExists, "Директория SET_SORCE_DIR не существует." },
	{ ErrorStatus::error::target_unknowLang, "Target - неизвестный язык." },
	{ ErrorStatus::error::fileTree_unknowLang, "FileTree - неизвестный язык." },
};

ErrorStatus::ErrorStatus(): value(0){}

void ErrorStatus::clear()
{
	value = 0;
}

void ErrorStatus::set(error error_, bool act_)
{
	if (act_) {
		value |= 1 << unsigned long long(error_);
	}
	else {
		value &= ~(1 << unsigned long long(error_));
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

		if (value & (1 << int(iter->first))) {
			cout << int(iter->first) << ") " << iter->second << endl;
		}
	}
}
