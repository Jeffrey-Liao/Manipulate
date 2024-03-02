#pragma once
#ifndef JCENTER_H
#define JCENTER_H
#include "Cmd.h"
#include"User.h"
#include "JUi.h"
static class Center
{
	onebyte curStage = UNIVER_CMD;
	User* currentUser;
	JCmd* currentCmd;
	vector<string> parameter;
public:
	static Center sysCenter;
	void add_parameter(vector<string> newParameter);
};
Center Center::sysCenter;
#endif