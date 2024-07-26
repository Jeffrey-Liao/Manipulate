#pragma once
#ifndef ERRORS_H
#define ERRORS_H
#include "Infor.h"
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
	class LiaoException
	{
		string ExceptionType;
		string errorMessage;
	protected:
		LiaoException(string type, string className,string methodName,string message);
		//输出错误信息到控制台
	public:
		void display();
		void error();
		void debug();
		~LiaoException();
	};
	class FatalException :public LiaoException
	{
	public: 
		FatalException(string className, string methodName, string message);
		~FatalException();
	};
	class CommonException :public LiaoException
	{
	public:
		CommonException(string className, string methodName, string message);
		~CommonException();
	};
	class DebugException :public LiaoException
	{
	public:
		DebugException(string className, string methodName, string message);
		~DebugException();
	};
}
#endif