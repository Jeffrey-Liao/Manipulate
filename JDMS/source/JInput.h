#pragma once
#include "JUi.h"
#include "Cmd.h"
#ifndef JINPUT_H
#define JINPUT_H
class JInput
{
	bool control;
	vector<string> inputCache;
	string cmdCache;
	char key;
	pair<JCmd*, double> curCmd;
private:
	void clear();
	JCmd* Enter(string& cache, const bool cmdMode);
	void Tab(string& cache);
	void BackSapce(string&,const bool);
public:
	static JInput liao_input;
	JInput();
	JCmd* input(const bool cmdMode = true);
	vector<string>& getParameter();
	void updateStage(onebyte newStage);
	bool paraEmpty();
};
#endif