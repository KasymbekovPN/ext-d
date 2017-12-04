#pragma once 

class ErrorStatus
{
public:

	enum class error {
		consoleCmdHand_configError,
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
		
		fileTree_argError,
		fileTree_unknowLang,
	};

	ErrorStatus();

	void clear();
	void set(error error_, bool act_);
	void set(ErrorStatus error_);
	unsigned long long get();

private:

	unsigned long long value;

};