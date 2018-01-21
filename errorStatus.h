#pragma once 

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

		json_objectInvalid,
		json_invalidSyntax,
		json_cnfg_num_of_trt_inv,
		json_cnfg_inv_target_name,
		json_cnfg_inv_target_path,
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