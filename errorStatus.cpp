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
	{ ErrorStatus::error::target_outputDirNoExists, "���������� out_dir �� ����������." },
	{ ErrorStatus::error::target_sourceDirNoExists, "���������� source_dir �� ����������." },
	{ ErrorStatus::error::target_unknowLang, "Target - ����������� ����." },
	{ ErrorStatus::error::target_invalidFlag, "Target - ���������� ����."},
	{ ErrorStatus::error::fileTree_unknowLang, "FileTree - ����������� ����." },
	{ ErrorStatus::error::fileTree_noExists, "FileTree - �� ������� ������������."},
	{ ErrorStatus::error::json_objectInvalid, "Json - ������ ���������."},
	{ ErrorStatus::error::json_invalidSyntax, "Json - ���������� ���������."},
	{ ErrorStatus::error::json_cnfg_num_of_trt_inv, "Json-conf - ���������� �������� : numder-of-targets"},
	{ ErrorStatus::error::json_cnfg_inv_target_name, "Json-conf - ���������� �������� ���� : name"},
	{ ErrorStatus::error::json_cnfg_inv_target_path, "Json-conf - ���������� �������� ���� : path" },
	{ ErrorStatus::error::json_extdlists_no_exists, "Json-conf - ���� �������� ���� �� ����������."},
	{ ErrorStatus::error::json_extdlists_source_dir_inv, "ExtDLists - ���������� �������� source_dir"},
	{ ErrorStatus::error::json_extdlists_out_dir_inv, "ExtDLists - ���������� �������� out_dir" },
	{ ErrorStatus::error::json_extdlists_lang_inv, "ExtDLists - ���������� �������� lang" },
	{ ErrorStatus::error::json_extdlists_inv_num_unhand_files, "ExtDLists - ���������� ���������� �������. ������"},
	{ ErrorStatus::error::json_extdlists_inv_unhand_files, "ExtDLists - ��������� �������� �������. �����"},
	{ ErrorStatus::error::json_extdlists_inv_num_unhand_dir, "ExtDLists - ���������� ���������� �������. ����������"},
	{ ErrorStatus::error::json_extdlists_inv_unhand_dir, "ExtDLists - ��������� ������� �������. ����������"},
	{ ErrorStatus::error::json_extdlists_inv_tokens_rel, "ExiDLists - ���������� �������� tokens-relative"},
	{ ErrorStatus::error::json_extdlists_inv_tokens_path, "ExtDLists - ���������� �������� tokens-path"},
#ifdef  TASK_27__1
	{ ErrorStatus::error::json_extdlists_inv_user_rel, "ExtDLists - ���������� �������� user-rel."},
	{ ErrorStatus::error::json_extdlists_inv_user_path, "ExtDLists - ���������� �������� user-path."},
#endif
#ifdef  TASK_3_0__1
	{ ErrorStatus::error::tokenList_invalid_numbes, "_tokens_list - ���������� �������� numbers."},
	{ ErrorStatus::error::tokenList_invalid_file_paths, "_token_list - ���������� �������� file_paths."},
	{ ErrorStatus::error::tokenList_file_paths_empty, "_token_list - file_paths ����."},
	{ ErrorStatus::error::tokenList_file_no_exists, "_token_list - ���� �� ������ �� ����������."},
	{ ErrorStatus::error::user_directory_no_exists, "���������� � ����������������� ������� �� ����������."}
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
