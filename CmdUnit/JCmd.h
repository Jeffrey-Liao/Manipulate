#pragma once
#include "../InforUnit/LiaoException.h"
#include "../UserUnit/User.h"
#ifndef JCMD_H
#define JCMD_H
namespace liao
{
#define PRINT_ALL 2
#define PRINT_CMDS 1
#define PRINT_CMD 0
	enum class CmdID
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
	class Operation
	{
		//stand length operation name
		char stdName[STDCLEN];
		//short length operation name
		char shrName[SHRCLEN];
		onebyte operId;
	public:
		Operation(const char* newStd, const char* newShr, onebyte operId);
		Operation(const char* newStd, const char* newShr, CmdID operId);
		void changeShrName(const char* newShr);
		onebyte getID();
		bool checkStd(string name);
		bool checkShr(string name);
		bool check(string cmd);
		bool checkByChar(char word, int pos);
		onebyte getStdLen();
		onebyte getShrLen();
		virtual bool valid() = 0;
		virtual bool usable(onebyte level) = 0;
		virtual bool usable(User user) = 0;

	};
	class TableOperation:public Operation
	{

	};
	class CommandOperation :public Operation
	{

	};
	class JCmd
	{
		char stdCmd[STDCLEN] = { '\0' };
		char shrCmd[SHRCLEN] = { '\0' };
		onebyte cmdType;
		WordCmd word;
		UserLevel levelRequired;
		onebyte paraNum;
	public:
		JCmd();
		JCmd(const char* newStd, const char* newShr, onebyte stage,
			WordCmd newWord, bool paraRequire, onebyte newParaNum, UserLevel newLevelRequire);
		void ChangeShrCmd(const char* newShr);
		bool test(char key, int index, onebyte stage);
		int lenSt();
		int lenSh();
		//查看在不在当前阶段
		bool usable(onebyte type);
		const char* const getStd();
		//获取指令enum
		const WordCmd& getWord();
		//比较用户是否有权限执行该操作
		bool executable(UserLevel user);
		//c查看给定参数数量是否足够
		bool enoughPara(onebyte para);
		//输出当前指令记录
		string print(onebyte mode = PRINT_CMD);
		bool operator ==(const JCmd& Obj);
		bool operator <(const JCmd& Obj);
		bool operator >(const JCmd& Obj);
		bool operator==(char* testCmd);
		bool operator==(string testCmd);
		bool operator == (const onebyte stage);
	};
	class CmdPack
	{
		JCmd* command;
		string restriction;
		vector<string> parameter;
	public:
		CmdPack();
		CmdPack(CmdPack&);
		CmdPack(string newRestriction);
		//新增restriction
		void addRestrict(string newRestrict);
		//插入新的参数/文本单元
		void insert(string newPara);
		//移除一个文本单元/参数
		void remove();
		//移除restriction
		void removeR();
		//计算文本单元/参数和限制的数量总和
		int count();
		//判断指令包内有无限制存在
		bool hasRestrict();
		//判断指令包内有无参数和文本单元存在
		bool hasPara();
		//判断指令包内有无指令存在
		bool hasCmd();
		//清空所有成员
		void clear();
		//检查是否拥有足够的参数
		bool enoughPara();
		//修改指令（会清空已有的参数和限制）
		void setCmd(JCmd* newCommand);
		//获取当前指令的指针
		JCmd* const getCmd();
		//获取当前指令的word形式
		WordCmd getCmdWord();
		//获取指令长度
		onebyte getCmdLen();
		//获取参数/限制是否均为空
		bool notEmpty();
		//获取参数列表
		vector<string>& getPara();
		//获取限制
		const string& getRestrict();
		//获取参数和限制（-1）
		const string& operator[](int index);
		//将新的指令写入包
		CmdPack& operator<< (JCmd* newCmd);
	};
}

#endif