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
	bool JCmd::operator==(const JCmd& Obj)
	{
		return this->word == Obj.word;
	}
	bool JCmd::operator<(const JCmd& obj)
	{
		return this->word > obj.word;
	}
	bool JCmd::operator>(const JCmd& obj)
	{
		return this->word > obj.word;
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