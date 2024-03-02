#pragma once
#ifndef ERRORS_H
#define ERRORS_H
#include"../JMacro.h"
#include <ctime>
namespace jeff
{
	static class Exception
	{
		string errorMessage;
		fstream errorFile;
	public:
		Exception(string className,string methodName,string errorMessage)
		{
			string timeMessage;
			time_t now = time(NULL);
			tm* timeStru = new tm;
			localtime_s(timeStru, &now);
			timeMessage = to_string(timeStru->tm_year+1900) + "-" +
				to_string(timeStru->tm_mon+1) + "-" + 
				to_string(timeStru->tm_mday)+"-"+                                                                                                               
				to_string(timeStru->tm_hour)+"-"+
				to_string(timeStru->tm_min)+"-"+
				to_string(timeStru->tm_sec)+"::";
			errorFile.open("errorLog.log",ios::app);
			this->errorMessage = "{" + className + "}" + ":" + " <" + methodName + "> " + errorMessage+"\n";
			errorFile << timeMessage+this->errorMessage;
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

#endif