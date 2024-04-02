#include "debugInfor.h"	
#pragma region DEBUGDEF
#define OPERATIONDAT "./resource/operation.dat"
string Debug::lastInfor;
string Debug::Timer(bool localTime)
{
	string timeMessage;
	time_t now = time(NULL);
	tm* timeStru = new tm;
	localtime_s(timeStru, &now);
	string datePart;
	string timePart;

	datePart = to_string(timeStru->tm_year + 1900);
	datePart += "-";
	if (timeStru->tm_mon < 10)
		datePart += to_string(0) + to_string(timeStru->tm_mon+1);
	else
		datePart += to_string(timeStru->tm_mon);
	datePart += "-";
	if(timeStru->tm_mday<10)
		datePart += to_string(0) + to_string(timeStru->tm_mday);
	else
		datePart += to_string(timeStru->tm_mday);
	timeMessage = datePart;
	if (localTime)
	{
		if (timeStru->tm_hour < 10)
			timePart = to_string(0) + to_string(timeStru->tm_hour);
		else
			timePart = to_string(timeStru->tm_hour);
		timePart += "-";
		if (timeStru->tm_min < 10)
			timePart += to_string(0) + to_string(timeStru->tm_min);
		else
			timePart += to_string(timeStru->tm_min);
		timePart += "-";
		if (timeStru->tm_sec < 10)
			timePart += to_string(0) + to_string(timeStru->tm_sec);
		else
			timePart += to_string(timeStru->tm_sec);
		timeMessage  += "|" + timePart + "::";
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
string Debug::operateInfor(string User, string operation,bool success)
{
	fstream devFile;
	devFile.open(OPERATIONDAT, ios::app);
	devFile << Timer()<<"[Operation] (" << User << "): " << operation << success << "\n";
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
	file.open("./resource/versionInf.txt", ios::in|ios::out);
	if (file.fail())
	{
		throw new LiaoException("Debug", "versionInfor", "Target File not exist");
	}
	else
	{
		for (auto& temp : versionInfor)
		{
			file << temp<<"\n";
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