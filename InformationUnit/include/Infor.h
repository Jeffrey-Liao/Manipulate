#ifndef INFOR_H
#define INFOR_H

#include "common.h"
#include <format>
namespace liaoInfor
{
#define MESSAGEBREAK ""
#define DEBUGLABEL "[DEBUG]"
#define ERRORLABEL "|<ERROR>|"
#define RUNTIMELABEL "(INFOR)"
#define EXCEPTIONLABEL "|>EXCEPTION<|"
	/*信息处理基类
	* 声明了三个公用接口（write，display和printLastInfor）
	* 其分别负责输出信息到文件、输出信息到控制台、和将上次的信息输出到控制台*/
 class Infor
	{
	 string message;
	protected:
		explicit Infor();
		void writeToFile(string& message, const char* fileName);
		//get the local time
		static string Timer(/*only show date if it is false*/bool localTime = true);
	public:
		void update(const char* label, const  string errorClass, const  string errorFunc, const string errorMessage, bool timer = false);
		void update(string message);
		//向文件写入调试信息方法
		void write(const char* dir);
		//向控制台界面输出调试信息方法
		void display();
		//输出上次的调试信息到控制台
	};
 class DebugInfor :public Infor
	{
	private:
		DebugInfor();
	public:
		//向文件写入调试信息方法
		void update(const string errorClass, const string errorFunc, const  string errorMessage, bool timer = false);
		
		static DebugInfor instance;
	};
 class ErrorInfor :public Infor
	{
	private:
		ErrorInfor();
	public:
		//向文件写入调试信息方法
		void update(const string errorClass, const  string errorFunc, const string errorMessage, bool timer = false);
		static ErrorInfor instance;
	};
 class ExceptionInfor :public Infor
 {
 public:
	 ExceptionInfor();
	 //向文件写入调试信息方法
	 void update(const string exception, const string errorClass, const string errorFunc, const string errorMessage, bool timer = false);
 };
class RuntimeInfor :public Infor
	{
	private:
		RuntimeInfor();
	public:
		//向文件写入调试信息方法
		void update(const string errorClass, const string errorFunc, const  string errorMessage, bool timer = false);
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