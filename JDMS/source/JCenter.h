#pragma once
#ifndef JCENTER_H
#define JCENTER_H
#define RESTRICTION 0
#include "Cmd.h"
#include"User.h"
#include"JInput.h"
enum class sysLan
{
	Chinese,
	English
};
class Center
{
	User* currentUser;
	CmdPack currentCmd;
	sysLan Language;
	void border();
	bool logInterface(string& userNameT, string& passwordT);
	void changeDockInfor();
	void InsufficientPara();
public:
	Center();
	static Center sysCenter;
	void receiveCmd();
	void receiveInput();
	void help(vector<string>&);
	bool command(string ,vector<string>&);
	void execute();
	void version();
	bool exist(string,vector<string>&);
	bool login(string,vector<string>&);
	void change(string,vector<string>&);
};

#endif