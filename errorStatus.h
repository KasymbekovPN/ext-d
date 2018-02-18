#pragma once 

#include "config.h"

#include <map>
#include <string>
#include <iostream>

using std::map;
using std::string;
using std::cout;
using std::endl;

class ErrorStatus
{
public:

	enum class error {
		consoleCmdHand_listCmdIsEmpty,
		consoleCmdHand_invalidConsoleCmd,
		consoleCmdHand_helpHandInvalidArg,
		consoleCmdHand_verHandInvalidArg,
		consoleCmdHand_tarShowAllInvalidArg,
		consoleCmdHand_tarShowInvalidArg,
		consoleCmdHand_tarRunInvalidArg,

		configHand_cnfgFileNoExitst,
		configHand_cmdSetTargetInvalid,
		configHand_targetRun_targetNoExists,
		configHand_noTargetSpec,
		configHand_currentTargetNoExists,
		
		target_outputDirInvalidParam,
		target_sourceDirInvalidParam,
		target_outputDirNoExists,
		target_sourceDirNoExists,
		target_unknowLang,
		target_invalidFlag,
		
		fileTree_unknowLang,
		fileTree_noExists,

		json_objectInvalid,
		json_invalidSyntax,
		json_cnfg_num_of_trt_inv,
		json_cnfg_inv_target_name,
		json_cnfg_inv_target_path,
		json_extdlists_no_exists,
		json_extdlists_source_dir_inv,
		json_extdlists_out_dir_inv,
		json_extdlists_lang_inv,
		json_extdlists_inv_num_unhand_files,
		json_extdlists_inv_unhand_files,
		json_extdlists_inv_num_unhand_dir,
		json_extdlists_inv_unhand_dir,
		json_extdlists_inv_tokens_rel,
		json_extdlists_inv_tokens_path,
#ifdef  TASK_27__1
		json_extdlists_inv_user_rel,
		json_extdlists_inv_user_path,
#endif
#ifdef  TASK_27__1
		tokenList_invalid_numbes,
		tokenList_invalid_file_paths,
		tokenList_file_paths_empty,
		tokenList_file_no_exists,
		user_directory_no_exists,
#endif
	};

	explicit ErrorStatus();

	void clear();
	void set(error error_, bool act_);
	void set(ErrorStatus error_);
	unsigned long long get();

	void display() const;

private:

	typedef map<error, string> ENM;
	static ENM errorNamesMap;

	unsigned long long value;

};