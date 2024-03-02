#pragma once
#ifndef JCMDLIST_H
#define JCMDLIST_H
#include"JCmd.h"
#include "Table.h"
class JCmdList
{
	vector<JCmd>AllCmd;
	vector<vector<const JCmd*>> cmdTree;
	int _size;
public:
	static JCmdList cmdList;
	JCmdList();
	JCmd* get(string cmd);
	inline int size()
	{
		return _size;
	}
	void add(Table* newTable);
	JCmd* const operator[](string);
	JCmd* const operator[](unsigned int index);

};
JCmdList JCmdList::cmdList;
class CmdCheck
{
public:
	static CmdCheck Checker;
private:
	vector<vector<JCmd*>> cmdTree;
public:
	CmdCheck();
	vector<JCmd*> CmdTest(char, onebyte);
	JCmd* const  CmdMatch(string);
	void operator+(JCmd*);
	JCmd* const operator [](string checkCmd);
};
#endif