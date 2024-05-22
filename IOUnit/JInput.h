#pragma once
#include "UiUnit.h"
#ifndef JINPUT_H
#define JINPUT_H
namespace liao
{
#define MODE_TEXT 3
#define MODE_PWD 2
#define MODE_STR 1
#define MODE_PARA -2//parameter mode(cannot set as this mode)
#define MODE_RSTR -1//restrict mode(cannot set as this mode)
#define MODE_CMD 0//default mode
	class LInput
	{
		STR inputCache;
		onebyte mode;
	protected:
		STR input();
	public:
		void setMode();

	};
}
#endif

/*
* OLD VERSION
class JInput
{
	onebyte mode;
	CmdPack resultCache;
	string inputCache;
	char key;
private:
	void clear();
	bool Enter(bool valid);
	void Tab(bool& valid, bool in);
	void BackSapce();
	void Space();
	bool input();
public:
	JInput();
	const string& getString();
	const vector<string>& getText();
	const CmdPack& getCmd();
	const WordCmd& getCmdWord();
	void updateMode(onebyte mode);
	void updateStage(onebyte newStage);
	bool paraEmpty();
	JInput& operator[](onebyte mode);
	JInput& operator>> (string& input);
	JInput& operator>> (vector<string>&);
	JInput& operator>>(CmdPack&);
};
static  JInput liao_input;


*/