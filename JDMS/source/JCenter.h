#pragma once
#ifndef JCENTER_H
#define JCENTER_H
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
	JCmd* currentCmd;
	sysLan Language;
	void border();
	bool logInterface(string& userNameT, string& passwordT);
	void changeDockInfor();
public:
	Center();
	static Center sysCenter;
	vector<string>& receiveCmd();
	vector<string>& receiveInput();
	void help(vector<string>&);
	bool command(vector<string>&);
	void execute();
	void version();
	bool exist(vector<string>&);
	bool login(vector<string>&);

};

#endif