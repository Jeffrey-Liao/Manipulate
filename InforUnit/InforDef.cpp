#include"infor.h"
namespace liao
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
	void Infor::write(string newMessage, string fileName, string label)
	{
		message = newMessage;
		STD ofstream file;
		file.open(fileName, STD ios::app);
		string outMessage = Timer()
			+ MESSAGEBREAK + label
			+ MESSAGEBREAK + message;
		file << outMessage<<"\n";
		file.close();
	}
	Infor& Infor::operator<<(string message)
	{
		this->write(message);
		return *this;
	}
#pragma endregion
#pragma region DebugInfor
	DebugInfor::DebugInfor()
	{}
	void DebugInfor::write(string message)
	{
		Infor::write(message, DEBUGFILE, DEBUGLABEL);
	}
	void DebugInfor::printLastInfor()
	{
		cout << DEBUGLABEL << MESSAGEBREAK << message << "\n";
	}
	void DebugInfor::display(string message)
	{
		cout << DEBUGLABEL << MESSAGEBREAK << message << "\n";
	}
#pragma endregion
#pragma region ErrorInfor
	ErrorInfor::ErrorInfor()
	{}
	void ErrorInfor::write(string message)
	{
		Infor::write(message, ERRORFILE, ERRORLABEL);
	}
	void ErrorInfor::printLastInfor()
	{
		cout << ERRORLABEL << MESSAGEBREAK << message << "\n";
	}
	void ErrorInfor::display(string message)
	{
		cout << ERRORLABEL << MESSAGEBREAK << message << "\n";
	}
#pragma endregion
#pragma region RuntimeInfor
	RuntimeInfor::RuntimeInfor()
	{}
	void RuntimeInfor::write(string message)
	{
		Infor::write(message, RUNTIMEFILE, RUNTIMELABEL);
	}
	void RuntimeInfor::printLastInfor()
	{
		cout <<RUNTIMELABEL << MESSAGEBREAK << message << "\n";
	}
	void RuntimeInfor::display(string message)
	{
		cout << RUNTIMELABEL << MESSAGEBREAK << message<<"\n";
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