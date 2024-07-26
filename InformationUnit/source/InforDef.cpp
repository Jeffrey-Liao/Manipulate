#include"../include/Infor.h"
namespace liaoInfor
{
	DebugInfor DebugInfor::instance;
	ErrorInfor ErrorInfor::instance;
	RuntimeInfor RuntimeInfor::instance;
#pragma region  Infor
	Infor::Infor()
	{}
	string Infor::Timer(bool localTime)
	{
		string timeMessage;
		time_t now = time(NULL);
		tm* timeStru = new tm;
		localtime_s(timeStru, &now);
		string datePart;
		string timePart;
		datePart = STD to_string(timeStru->tm_year + 1900);
		datePart += "-";
		if (timeStru->tm_mon < 10)
			datePart += STD to_string(0) + STD to_string(timeStru->tm_mon + 1);
		else
			datePart += STD to_string(timeStru->tm_mon);
		datePart += "-";
		if (timeStru->tm_mday < 10)
			datePart += STD to_string(0) + STD to_string(timeStru->tm_mday);
		else
			datePart += STD to_string(timeStru->tm_mday);
		timeMessage = datePart;
		if (localTime)
		{
			if (timeStru->tm_hour < 10)
				timePart = STD to_string(0) + STD to_string(timeStru->tm_hour);
			else
				timePart = STD to_string(timeStru->tm_hour);
			timePart += "-";
			if (timeStru->tm_min < 10)
				timePart += STD to_string(0) + STD to_string(timeStru->tm_min);
			else
				timePart += STD to_string(timeStru->tm_min);
			timePart += "-";
			if (timeStru->tm_sec < 10)
				timePart += STD to_string(0) + STD to_string(timeStru->tm_sec);
			else
				timePart += STD to_string(timeStru->tm_sec);
			timeMessage += "|" + timePart + "::";
		}
		delete timeStru;
		return timeMessage;
	}
	void Infor::writeToFile(string& newMessage, const char* fileName)
	{
		message = newMessage;
		STD ofstream file;
		file.open(fileName, STD ios::app);
		string outMessage = Timer()
			+ MESSAGEBREAK + message;
		file << outMessage<<"\n";
		file.close();
	}
	string Infor::messageGener(const char* label, string errorClass, string errorFunc, string errorMessage)
	{
		string mes = "There is an";
		mes += label;
		mes += "message from {" + errorClass + "} class in method [" + errorFunc + "]: " + errorMessage;
		return mes;
	}
	void Infor::showTime()
	{
		timeDisplay = true;
	}
	void Infor::noTime()
	{
		timeDisplay = false;
	}
#pragma endregion
#pragma region DebugInfor
	DebugInfor::DebugInfor()
	{}
	void DebugInfor::write(string errorClass, string errorFunc, string errorMessage)
	{
		message = messageGener(DEBUGLABEL, errorClass, errorFunc, errorMessage);
		Infor::writeToFile(message, DEBUGFILE);
	}
	void DebugInfor::write(string message)
	{
		Infor::writeToFile(message, DEBUGFILE);
	}
	void DebugInfor::write()
	{
		Infor::writeToFile(message, DEBUGFILE);
	}
	void DebugInfor::display(string message)
	{
		this->message = message;
		cout << DEBUGLABEL << " Message :" << message << "\n";
	}
	void DebugInfor::display(string errorClass, string errorFunc, string errorMessage)
	{
		message = messageGener(ERRORLABEL, errorClass, errorFunc, errorMessage);
		cout << message<<"\n";
	}
	void DebugInfor::display()
	{
		cout << message<<"\n";
	}
#pragma endregion
#pragma region ErrorInfor
	ErrorInfor::ErrorInfor()
	{}
	void ErrorInfor::write(string errorClass, string errorFunc, string errorMessage)
	{
		message = messageGener(ERRORLABEL, errorClass, errorFunc, errorMessage);
		Infor::writeToFile(message, ERRORFILE);
	}
	void ErrorInfor::write(string message)
	{
		this->message = message;
		Infor::writeToFile(message, ERRORFILE);
	}
	void ErrorInfor::write()
	{
		Infor::writeToFile(message, ERRORFILE);
	}
	void ErrorInfor::display(string message)
	{
		cout << ERRORLABEL << " Message :" << message << "\n";
	}
	void ErrorInfor::display(string errorClass, string errorFunc, string errorMessage)
	{
		message = messageGener(ERRORLABEL, errorClass, errorFunc, errorMessage);
		cout << message<<"\n";
	}
	void ErrorInfor::display()
	{
		cout << message<<"\n";
	}
#pragma endregion
#pragma region RuntimeInfor
	RuntimeInfor::RuntimeInfor()
	{}
	void RuntimeInfor::write(string message)
	{
		Infor::writeToFile(message, RUNTIMEFILE);
	}
	void RuntimeInfor::write(string errorClass, string errorFunc, string errorMessage)
	{
		message = messageGener(ERRORLABEL, errorClass, errorFunc, errorMessage);
		Infor::writeToFile(message, ERRORFILE);
	}
	void RuntimeInfor :: write()
	{
		Infor::writeToFile(message, ERRORFILE);
	}
	void RuntimeInfor::display(string message)
	{
		cout << RUNTIMELABEL << " Message: " << message << "\n";
	}
	void RuntimeInfor::display(string errorClass, string errorFunc, string errorMessage)
	{
		message = messageGener(ERRORLABEL, errorClass, errorFunc, errorMessage);
		cout << message << "\n";
	}
	void RuntimeInfor::display()
	{
		cout << message<<"\n";
	}
#pragma endregion
#pragma region InforReader
	InforReader::InforReader(string fileName) 
	{
		STD ifstream file;
		file.open(fileName, STD ios::in);
		if (file.fail())
		{
			ErrorInfor::instance.write("file cannot be open");
		}
		char input[200];
		file.getline(input, 200);
		int fs = 0,sc = 0,end = 0;
		for (int n = 0; n < 200; ++n)
		{
			if (input[n] == '~')
			{
				if (fs == 0)
					fs = n;
				else
					sc = n;
			}
			else if (input[n] == '\0')
			{
				end = n;
				break;
			}

		}
		this->date.assign(input, 0, fs);
		this->date.assign(input, sc, end);
	}
	string InforReader::getDate()
	{
		return date;
	}
	string InforReader::getInfor()
	{
		return infor;
	}
	string InforReader::getAll()
	{
		return getDate() + " " + getInfor();
	}
#pragma endregion


}