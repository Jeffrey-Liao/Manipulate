#include "debugInfor.h"	
#pragma region DEBUGDEF
string Debug::lastInfor;
string Debug::Timer(bool localTime)
{
	string timeMessage;
	time_t now = time(NULL);
	tm* timeStru = new tm;
	localtime_s(timeStru, &now);
	string timePart;
	timeMessage = to_string(timeStru->tm_year + 1900) + "-" +
		to_string(timeStru->tm_mon + 1) + "-" +
		to_string(timeStru->tm_mday);
	if (localTime)
	{
		timeMessage +="-" +
			to_string(timeStru->tm_hour) + "-" +
			to_string(timeStru->tm_min) + "-" +
			to_string(timeStru->tm_sec) + "::";
	}
	delete timeStru;
	return timeMessage;
}
string Debug::debugInfor(string className, string methodName, string infor)
{
	string devMessage, timeMessage;
	fstream devFile;
	devFile.open(DEBUGF, ios::app);
	timeMessage = Timer();
	devMessage = "[Infor]{" + className + "}" + ":" + " <" + methodName + "> " + devMessage + "\n";
	devFile << timeMessage + devMessage;
	devFile.close();
	lastInfor = devMessage;
	return devMessage;
}
string Debug::operateInfor(string User, string operation)
{
	fstream devFile;
	devFile.open(DEBUGF, ios::app);
	devFile << Timer() << User << operation << "\n";
	return User + operation;
}
string Debug::errorInfor(string className, string methodName, string infor)
{
	string errorMessage, timeMessage;
	fstream errorFile(ERRORF, ios::app);
	timeMessage = Timer();
	errorMessage = "[Error]{" + className + "}" + ":" + " <" + methodName + "> " + infor + "\n";
	errorFile << timeMessage + errorMessage;
	errorFile.close();
	lastInfor = errorMessage;
	return errorMessage;
}
void Debug::versionInfor(vector<string> versionInfor)
{
	fstream file;
	int iterNum = 0;
	file.open("./resource/versionInf.txt", ios::in|ios::out);
	if (file.fail())
	{
		throw new LiaoException("Debug", "versionInfor", "Target File not exist");
	}
	else
	{
		while (!file.eof())
		{
			
		}
	}
	file.close();
}
#pragma endregion
#pragma region EXCEPTIONDEF
LiaoException::LiaoException(string className, string methodName, string errorMessage)
{
	this->errorMessage = Debug::errorInfor(className, methodName, errorMessage);
}
LiaoException::LiaoException(const LiaoException& Obj)
{
	errorMessage = Obj.errorMessage;
}
string LiaoException::getErrorMessage()
{
	return errorMessage;
}
LiaoException::~LiaoException()
{
}
#pragma endregion