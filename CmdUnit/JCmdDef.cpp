#include "JCmd.h"
#define CMD_RESERVED 2
#pragma region JCmd
JCmd::JCmd()
	:word(WC Empty), paraNum(0), stdCmd(), shrCmd(), cmdType(UNIVER_CMD),levelRequired(UserLevel::Guest)
{}
JCmd::JCmd(const char* newStd, const char* newShr, onebyte stage, WordCmd newWord, bool paraRequire, onebyte newParaNum, UserLevel newLevelRequire)
	:word(newWord), paraNum(newParaNum), cmdType(stage), levelRequired(newLevelRequire)
{
	strcpy_s(this->stdCmd, STDCLEN, newStd);
	strcpy_s(this->shrCmd, SHRCLEN, newShr);
	if (!paraRequire)
		this->paraNum *= -1;
}
const WordCmd& JCmd::getWord()
{
	return this->word;
}
bool JCmd::executable(UserLevel user)
{
	return user >= this->levelRequired;
}
const char* const JCmd::getStd()
{
	return this->stdCmd;
}
string JCmd::print(onebyte mode)
{
	string cmd = this->stdCmd;
	if(mode >= PRINT_CMDS)
	{
		cmd = cmd +"\t" + this->shrCmd;
	}
	if(mode>=PRINT_ALL)
	{
		cmd += "\t";
		cmd += to_string(this->paraNum);
		cmd += "\t";
		cmd += User::Level2Str(this->levelRequired);
	}
	return cmd;
}
bool JCmd::enoughPara(onebyte para)
{
	if (this->paraNum > 0)
		return this->paraNum == para || paraNum + 1 == para;
	else
		return para == 0 || para >= abs(this->paraNum);
}
bool JCmd::operator == (const onebyte stage)
{
	return this->cmdType == stage;
}
bool JCmd::usable(onebyte type)
{
	return type >= this->cmdType;
}

int JCmd::lenSt()
{
	return strlen(this->stdCmd);
}
int JCmd::lenSh()
{
	return strlen(this->shrCmd);
}
bool JCmd::test(char key, int index, onebyte stage)
{
	return (key == stdCmd[index] || (key == shrCmd[index])) && stage >= this->cmdType;
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
#pragma endregion
#pragma region CmdPack
CmdPack::CmdPack()
	:command(NULL)
{}
CmdPack::CmdPack(CmdPack& obj)
{
	this->command = obj.command;
	this->parameter = obj.parameter;
	this->restriction = obj.restriction;
}
CmdPack::CmdPack(string newRestriction)
	:command(NULL)
{
	restriction = newRestriction;
}
void CmdPack::addRestrict(string newRestrict)
{
	this->restriction = newRestrict;
}
void CmdPack::clear()
{
	this->parameter.clear();
	this->restriction.clear();
	this->command = NULL;
}
void CmdPack::insert(string newPara)
{
	parameter.push_back(newPara);
}
void CmdPack::remove()
{
	parameter.erase(parameter.end() - 1);
}
int CmdPack::count()
{
	if(restriction.size() !=0)
		return parameter.size()+1;
	else
		return parameter.size();
}
JCmd* const CmdPack::getCmd()
{
	if (command)
		return command;
	else
		return NULL;
}
void CmdPack::removeR()
{
	this->restriction.clear();
}
onebyte CmdPack::getCmdLen()
{
	return this->command->lenSt();
}
void CmdPack::setCmd(JCmd* newCommand)
{
	this->command = newCommand;
	this->restriction.clear();
	this->parameter.clear();
}
bool CmdPack::notEmpty()
{
	return restriction.size() != 0 || parameter.size() != 0;
}
bool CmdPack::hasRestrict()
{
	return this->restriction.size() > 0;
}
bool CmdPack::hasPara()
{
	return parameter.size() > 0;
}
vector<string>& CmdPack::getPara()
{
	return this->parameter;
}
const string& CmdPack::getRestrict()
{
	return this->restriction;
}
const string& CmdPack::operator[](int index)
{
	if (index < parameter.size() && index>=0)
		return this->parameter[index];
	else if (index == -1)
		return this->restriction;
	else
		throw LiaoException("CmdPack","operator[]","Index overflow!");
}
WordCmd CmdPack::getCmdWord()
{
	if (command)
		return this->command->getWord();
	else
		return WordCmd::Empty;
}
bool  CmdPack::hasCmd()
{
	return this->command != NULL;
}
bool CmdPack::enoughPara()
{
	return this->command->enoughPara(this->parameter.size());
}
CmdPack& CmdPack::operator<< (JCmd* newCmd)
{
	this->setCmd(newCmd);
	return *this;
}
#pragma endregion

	