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
	int listLock; //目前目标指令子表
	int cmdLock;//目前子表内子指令
	bool isShr;//是否为短指令/是否有指令字符出现错误
	int match;//匹配的指令字符数量
	int _index;//目前匹配index位置
public:
	static JCmdList cmdlist;
	JCmdList();
	//获取指令总表长度
	int size();
	//指向总表的下一个
	JCmd* const  next();
	//获取当前指令（未匹配部分）
	string getCmdLock();
	//根据str推出指令结构
	JCmd* const get(string potential);
	//获取所有的表层级指令
	vector<JCmd*> getTable();
	//检查当前指令是否正确
	pair<JCmd*,bool> check(char,onebyte);
	bool exist(string);
	inline bool start()
	{
		return _index > 0;
	}
	//将指令匹配index-1
	void back();
	//判断当前选中是否为短指令
	bool isShort();
	//清除所有成员标志位
	void clear();
	//按总表索引获取指令
	JCmd& operator[](unsigned int index);
	//完成未输入完成指令匹配
	pair<JCmd*, bool> complete(bool input = true);
	//获取当前子表内下一个指令
	const JCmd& lockNext();
	//获取当前子表内上一个指令
	const JCmd& lockPrev();
};
#endif