#ifndef ERROR_H
#define ERROR_H
#include"JMacro.h"
#include <ctime>
static class Debug
{
	static string Timer(bool localTime = true);
public:
	static string lastInfor;
	static string debugInfor(string className, string methodName, string infor);
	static string operateInfor(string User, string operation);
	static string errorInfor(string className, string methodName, string infor);
	static void versionInfor(vector<string> versionInfor);
};

 class LiaoException
{
	string errorMessage;
public:
	LiaoException(string className, string methodName, string errorMessage);
	LiaoException(const LiaoException& Obj);
	string getErrorMessage();
	~LiaoException();
};


#endif