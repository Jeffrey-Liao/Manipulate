#include "JCmd.h"
#define CMD_RESERVED 2
	JCmd::JCmd()
		:word(WC Empty), paraNum(0), stdCmd(), shrCmd(), cmdType(UNIVER_CMD)
	{}
	JCmd::JCmd(const char* newStd, const char* newShr, onebyte dominInfor, WordCmd newWord, onebyte newRequire)
		:word(newWord), paraNum(newRequire), cmdType(dominInfor)
	{
		strcpy_s(this->stdCmd, STDCLEN, newStd);
		strcpy_s(this->shrCmd, SHRCLEN, newShr);
	}
	JCmd::JCmd(const char* newStd)
		:word(WC Empty), cmdType(TABLE), paraNum(0)
	{
		strcpy_s(this->stdCmd, STDCLEN, newStd);
	}
	bool JCmd::operator==(char* testCmd)
	{
		return strcmp(stdCmd, testCmd) == 0 || strcmp(shrCmd, testCmd) == 0;
	}
	bool JCmd::operator==(string testCmd)
	{
		return stdCmd == testCmd || shrCmd == testCmd;
	}
	void JCmd::ChangeShrCmd(const char* newShr)
	{
		strcpy_s(this->shrCmd, SHRCLEN, newShr);
	}

	
	/* if (restriction == "on" && CurrentUser.isActive())
		{

		}
		else if (restriction == "in"&&CurrentUser.isActive())
		{
			char newUserName[NAMELEN] = { "\0" }, newPassword[PASSWORDLEN] = { "\0" };
			cout << "Please enter your user name:	";
			cin >> newUserName;
			cout << "Please enter your password:	";
			cin >> newPassword;
			CurrentUser.log(newUserName, newPassword);
		}
		else if (restriction == "out" && this->CurrentUser.isActive())
		{
			return -1;
		}
		else if (restriction == "out" )
		{

		}
		else if (restriction == "back")
		{

		}*/
		/*
		CMDP cmdControl():stage(STAGE_NOLOG)
		{
			for (int n = 0; AllCmd[n].word != WC Change; ++n)
				this->LoadedCmd.push_back(&AllCmd[n]);
		}
		CMDP cmdControl(int newStage) : stage(newStage)
		{
			if (stage == STAGE_NOLOG)
			{
				for (int n = 0; AllCmd[n].word != WC Change; ++n)
					this->LoadedCmd.push_back(&AllCmd[n]);
			}
			else if (stage == STAGE_LOG)
			{
				for (int n = 0; AllCmd[n].word != WC Append; ++n)
					this->LoadedCmd.push_back(&AllCmd[n]);
			}
			else if (stage == TABLE_CMD)
			{
				for (int n = 0; AllCmd[n].word != WC User; ++n)
					this->LoadedCmd.push_back(&AllCmd[n]);
			}
		}
		void CMDP cmdUpdate(int newStage)
		{
			this->stage = newStage;
		}
		void CMDP checkCmd_word(char word, int start)
		{

		}
		WordCmd CMDP cmdInput(parameter& parameters)
		{
			char key = 0;
			string Cache="";
			for (int n = 0; key != 27; ++n)
			{
				if (CONTROL)
				{
					if (ENTER)
					{

					}
				}
				else
				{
					cout << key;
					Cache += key;
				}
			}
			return WordCmd::Quit;
		}

		void CMDP JCmdMain()
		{
			parameter parameterList;
			WordCmd result = cmdInput(parameterList);
			if (result < WordCmd::Change)
			{

			}
		}
		*/
