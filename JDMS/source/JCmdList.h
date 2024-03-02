#pragma once
#ifndef JCMDLIST_H
#define JCMDLIST_H
#include "JUi.h"
#include"JCmd.h"
#include "Table.h"
#include "./storage/LinkList.h"
#define PASSRATE 0.85
using namespace jeff;
class JCmdList
{
	static DoubleLinkList<JCmd>AllCmd;
	vector<vector<JCmd*>> cmdTree;
	int listLock,cmdLock;//目前目标指令子表/目前子表内子指令
	bool isShr;//是否为短指令/是否有指令字符出现错误
	int match,_index;//匹配的指令字符数量
public:
	static JCmdList cmdlist;
	JCmdList();
	int size();
	string getCmdLock();
	const JCmd* const get(string potential);
	vector<string> getTable();
	pair<JCmd*,double> check(char,onebyte);
	inline bool start()
	{
		return _index > 0;
	}
	void back();
	bool isShort();
	void clear();
	JCmd& operator[](unsigned int index);
	pair<JCmd*, double> complete();
	JCmd& lockNext();
	JCmd& lockPrev();
};
#endif