#ifndef ERROR_H
#define ERROR_H
#include"JMacro.h"
#include <ctime>
namespace jeff
{
	static class Exception
	{
		string errorMessage;
		fstream errorFile;
	public:
		Exception(string className, string methodName, string errorMessage)
		{
			time_t now = time(NULL);
			tm* timeStru = new tm;
			localtime_s(timeStru, &now);
			this->errorMessage = to_string(timeStru->tm_year + 1900) + "-" +
				to_string(timeStru->tm_mon + 1) + "-" +
				to_string(timeStru->tm_mday) + "-" +
				to_string(timeStru->tm_hour) + "-" +
				to_string(timeStru->tm_min) + "-" +
				to_string(timeStru->tm_sec) + "::";
			errorFile.open(ERRORF, ios::app);
			this->errorMessage += "{" + className + "}" + ":" + " <" + methodName + "> " + errorMessage + "\n";
			errorFile << this->errorMessage;
			errorFile.close();
			delete timeStru;
		}
		Exception(vector<string>newErrorMessageList)
		{
			errorFile.open("errorLog.log", ios::app);
			for (int n = 0; n < newErrorMessageList.size(); ++n)
				this->errorMessage += newErrorMessageList[n];
			this->errorMessage += "\n";
			errorFile << errorMessage;
			errorFile.close();
		}
		inline string getErrorMessage()
		{
			return this->errorMessage;
		}
	};
}

static class Debug
{
	static string Timer()
	{
		string timeMessage;
		time_t now = time(NULL);
		tm* timeStru = new tm;
		localtime_s(timeStru, &now);
		timeMessage = to_string(timeStru->tm_year + 1900) + "-" +
			to_string(timeStru->tm_mon + 1) + "-" +
			to_string(timeStru->tm_mday) + "-" +
			to_string(timeStru->tm_hour) + "-" +
			to_string(timeStru->tm_min) + "-" +
			to_string(timeStru->tm_sec) + "::";
		delete timeStru;
		return timeMessage;
	}
public:
	static string devInfor(string infor,int importance = 0)
	{
		fstream devFile;
		devFile.open(DEBUGF, ios::out);
		if (importance == 1)
			infor = "(" + infor + ")";
		else if (importance == 2)
			infor = "<" + infor + ">";
		else if (importance == 3)
			infor = "!!" + infor + "!!";
		infor += "\n";
		cout << infor;
		devFile << infor;
	}
	static string logInfor(string User, string operation)
	{
		fstream devFile;
		devFile.open(DEBUGF, ios::out);
		devFile <<Timer()<< User<<operation<<"\n";
	}
	static string errorInfor(string className, string methodName, string infor)
	{
		string errorMessage,timeMessage;
		fstream errorFile;
		timeMessage = Timer();
		errorMessage = "[Error]{" + className + "}" + ":" + " <" + methodName + "> " + errorMessage + "\n";
		errorFile << timeMessage+errorMessage;
		errorFile.close();
	}
};
#endif