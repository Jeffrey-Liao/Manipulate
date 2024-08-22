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
	void Infor::display(string message)
	{
		this->update(message);
		this->display();
	}
	void Infor::update(const char* label, const  string errorClass, const string errorFunc, const string errorMessage, bool timer)
	{
		message.clear();
		if (timer)
		{
			const string time = Timer();
			message = std::format("[{}] :: There is a(n) {} detected in class:({}) function:[{}]: {}", time, label, errorClass, errorFunc, errorMessage);
		}
		else
			message = std::format("There is a(n) {} detected in class: ({}) function: [{}]: {}", label, errorClass, errorFunc, errorMessage);
	}
	void  Infor::update(string message)
	{
		this->message = message;
	}
	void Infor::write(const char* dir = "log.log")
	{
		writeToFile(message, dir);
	}
	void Infor::display()
	{
		cout << message;
	}
#pragma endregion
#pragma region DebugInfor
	DebugInfor::DebugInfor()
		:Infor()
	{}
	void DebugInfor::update(const string errorClass, const string errorFunc, const string errorMessage, bool timer)
	{
		Infor::update(DEBUGLABEL, errorClass, errorFunc, errorMessage, timer);
	}
#pragma endregion
#pragma region ErrorInfor
	ErrorInfor::ErrorInfor()
		:Infor()
	{}
	void ErrorInfor::update(const string errorClass, const  string errorFunc, const string errorMessage, bool timer)
	{
		Infor::update(ERRORLABEL, errorClass, errorFunc, errorMessage);
	}
#pragma endregion
#pragma region ExceptionInfor
	ExceptionInfor::ExceptionInfor()
		:Infor()
	{}
	void ExceptionInfor::update(const string exception, const string errorClass, const string errorFunc, const string errorMessage, bool timer)
	{
		Infor::update(std::format("|>{}:Exception<|",exception).c_str(), errorClass, errorFunc, errorMessage);
	}
#pragma endregion

#pragma region RuntimeInfor
	RuntimeInfor::RuntimeInfor()
		:Infor()
	{}
	void RuntimeInfor::update(const string errorClass, const  string errorFunc, const string errorMessage, bool timer)
	{
		Infor::update(RUNTIMELABEL, errorClass, errorFunc, errorMessage);
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