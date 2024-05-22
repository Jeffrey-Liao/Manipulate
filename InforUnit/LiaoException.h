#pragma once
#ifndef ERRORS_H
#define ERRORS_H
#include "Infor.h"
namespace liao
{
	class LiaoException
	{
		string errorMessage;
	public:
		LiaoException(string className,string methodName,string message, int line = 0);
		//输出错误信息到控制台
		void display();
		void tofile();
		~LiaoException();
	};
	class FatalException :public LiaoException
	{
	public: 
		FatalException(string className, string methodName, string message, int line = 0);
	};
}
#endif