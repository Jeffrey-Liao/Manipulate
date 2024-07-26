#ifndef INFOR_H
#define INFOR_H

#include "common.h"

namespace liaoInfor
{
#define DEBUGFILE "./log/debug.log"
#define ERRORFILE "./log/error.log"
#define RUNTIMEFILE "./log/runtime.log"
#define MESSAGEBREAK ""
#define DEBUGLABEL "[DEBUG]"
#define ERRORLABEL "<!ERROR!>"
#define RUNTIMELABEL "(INFOR)"
	/*信息处理基类
	* 声明了三个公用接口（write，display和printLastInfor）
	* 其分别负责输出信息到文件、输出信息到控制台、和将上次的信息输出到控制台*/
 class Infor
	{
	protected:
		bool timeDisplay = false;
		string message;
		Infor();
		void writeToFile(string& message, const char* fileName);
		//get the local time
		static string Timer(/*only show date if it is false*/bool localTime = true);
		static string messageGener(const char* label,string errorClass, string errorFunc, string errorMessage);
	public:
		//向文件写入调试信息方法
		virtual void write(string errorClass, string errorFunc, string errorMessage) = 0;
		virtual void write(string message) = 0;//abstract
		virtual void write() = 0;
		//向控制台界面输出调试信息方法
		virtual void display(string message) = 0;
		virtual void display(string errorClass, string errorFunc, string errorMessage) = 0;
		virtual void display() = 0;
		void showTime();
		void noTime();
		//输出上次的调试信息到控制台
	};
 class DebugInfor :public Infor
	{
	private:
		DebugInfor();
	public:
		//向文件写入调试信息方法
		void write(string errorClass, string errorFunc, string errorMessage) override;
		void write(string message) override;
		void write() override;
		//向控制台界面输出调试信息方法
		void display(string message);
		//输出上次的调试信息到控制台
		void display(string errorClass, string errorFunc, string errorMessage) override;
		void display();
		static DebugInfor instance;
	};
 class ErrorInfor :public Infor
	{
	private:
		ErrorInfor();
	public:
		//向文件写入调试信息方法
		void write(string errorClass, string errorFunc, string errorMessage) override;
		void write(string message) override;
		void write() override;
		//向控制台界面输出调试信息方法
		void display(string message);
		//输出上次的调试信息到控制台
		void display(string errorClass, string errorFunc, string errorMessage) override;
		void display();
		static ErrorInfor instance;
	};
class RuntimeInfor :public Infor
	{
	private:
		RuntimeInfor();
	public:
		//向文件写入调试信息方法
		void write(string errorClass, string errorFunc, string errorMessage) override;
		void write(string message) override;
		void write() override;
		//向控制台界面输出调试信息方法
		void display(string message);
		//输出上次的调试信息到控制台
		void display(string errorClass, string errorFunc, string errorMessage) override;
		void display();
		static RuntimeInfor instance;
	};
class InforReader
{
	string date;
	string infor;
public:
	InforReader(string fileName);
	string getAll();
	string getDate();
	string getInfor();
};
}
#endif