#include "errorStatus.h"

ErrorStatus::ENM ErrorStatus::errorNamesMap {
	{ ErrorStatus::error::consoleCmdHand_listCmdIsEmpty, "�� ���� ���������� ������� �� ������." },
	{ ErrorStatus::error::consoleCmdHand_invalidConsoleCmd, "���������� �������."},
	{ ErrorStatus::error::consoleCmdHand_helpHandInvalidArg, "���������� ������ ���������� --help."},
	{ ErrorStatus::error::consoleCmdHand_verHandInvalidArg, "���������� ������ ���������� --version."},
	{ ErrorStatus::error::consoleCmdHand_tarShowAllInvalidArg, "���������� ������ ���������� --target.show.all." },
	{ ErrorStatus::error::consoleCmdHand_tarShowInvalidArg, "���������� ������ ���������� --target.show" },
	{ ErrorStatus::error::consoleCmdHand_tarRunInvalidArg, "���������� ������ ���������� --target.run" },
	{ ErrorStatus::error::configHand_cnfgFileNoExitst, "���������������� ���� �� ����������." },
	{ ErrorStatus::error::configHand_cmdSetTargetInvalid, "���������� ������� SETTARGET." },
	{ ErrorStatus::error::configHand_targetRun_targetNoExists, "���� �� ����������." },
	{ ErrorStatus::error::configHand_noTargetSpec, "�� ����� ���� �� ������." },
	{ ErrorStatus::error::configHand_currentTargetNoExists, "������� ���� �� ����������." },
	{ ErrorStatus::error::target_outputDirInvalidParam, "���������� �������� SET_OUTPUT_DIR." },
	{ ErrorStatus::error::target_sourceDirInvalidParam, "���������� �������� SET_SOURCE_DIR." },
	{ ErrorStatus::error::target_outputDirNoExists, "���������� SET_OUTPUT_DIR �� ����������." },
	{ ErrorStatus::error::target_sourceDirNoExists, "���������� SET_SORCE_DIR �� ����������." },
	{ ErrorStatus::error::target_unknowLang, "Target - ����������� ����." },
	{ ErrorStatus::error::fileTree_unknowLang, "FileTree - ����������� ����." },
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
