#pragma once
#include"debugInfor.h"
#ifndef JCMD_H
#define JCMD_H
enum class WordCmd
{
	Empty = -1,
	//Universal cmd

	Help,//has parameter
	Lrk,
	Back,//no parameter
	Quit,//no parameter
	Version,//no parameter
	Command,
	Log,//has parameter
	Exist,

	//Share
	Change,//require paramter
	Find,//require paramter
	Remove,//require parameter
	Lock,
	Unlock,
	Undo,

	//Main
	User,//has paramter
	Create,//require paramter
	List, //no parameter
	Authorize,
	Merge,

	Append,//has parameter
	Insert,
	Search,
	Print,
	Locate,

	Max
};
class paraLimit
{
	int paraNum;
	vector<string> restricts;

};
class JCmd
{
public:
	char stdCmd[STDCLEN] = { '\0' };
	char shrCmd[SHRCLEN] = { '\0' };
	onebyte cmdType;
	WordCmd word;
	onebyte paraNum;//positive is require parameter, negative is can have parameter,zero is no parameter
	JCmd();
	JCmd(const char* newStd, const char* newShr, onebyte dominInfor,
		WordCmd newWord, onebyte newRequire);
	JCmd(const char* newStd);
	void ChangeShrCmd(const char* newShr);
	bool operator ==(const JCmd& Obj);
	bool operator <(const JCmd& Obj);
	bool operator >(const JCmd& Obj);
	bool operator==(char* testCmd);
	bool operator==(string testCmd);
};
#endif