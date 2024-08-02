#pragma once
#ifndef ERRORS_H
#define ERRORS_H
#include "Infor.h"
#include<exception>
namespace liaoInfor
{
	/*
	* the basic class of Liao exception system
	* it contains 2 members:
	*>>the type of exception belong to (given by subclasses)
	* >>the error message (given by subclasses too)
	* it contains 2 methods:
	* >>display(): print error message to the console
	* >>error(): export error message to error.log file
	*/
	class LiaoException:std::runtime_error
	{
	protected:
		ExceptionInfor instance;
		LiaoException(string exceptionName, string className,string methodName,string message);
		//输出错误信息到控制台
	public:
		void display();
		void toFile(const char* fileName);
		~LiaoException();
	};
	class FatalException :public LiaoException
	{
	public: 
		FatalException(string className, string methodName, string message);
		FatalException(string exceptionName, string className, string methodName, string message);
		~FatalException();
	};
	class CommonException :public LiaoException
	{
	public:
		CommonException(string className, string methodName, string message);
		CommonException(string exceptionName, string className, string methodName, string message);
		~CommonException();
	};
}
#endif