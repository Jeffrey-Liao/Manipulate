#include "../include/LiaoException.h"
#include <cstdlib>
namespace liaoInfor
{
#pragma region LiaoException
	LiaoException::LiaoException(string exceptionName, string className, string methodName, string message)
		:runtime_error(message)
	{
		instance.update(exceptionName, className, methodName, message);
	}
	void LiaoException::display()
	{
		instance.display();
	}
	void LiaoException::toFile(const char* fileName)
	{
		instance.write(fileName);
	}
	LiaoException::~LiaoException()
	{}
#pragma endregion
#pragma region FatalException
	FatalException::FatalException(string className, string methodName, string message)
		:LiaoException("Fatal", className, methodName, message)
	{
		this->display();
		instance.write("log.log");
		abort();
	}
	FatalException::FatalException(string exceptionName, string className, string methodName, string message)
		:LiaoException(exceptionName,className,methodName,message)
	{
		this->display();
		instance.write("log.log");
		abort();
	}
	FatalException::~FatalException()
	{}
#pragma endregion
#pragma region CommonException
	CommonException::CommonException(string className, string methodName, string message)
		:LiaoException("Common", className, methodName, message)
	{
		this->display();
	}
	CommonException::CommonException(string exceptionName,string className, string methodName, string message)
		:LiaoException(exceptionName, className, methodName, message)
	{
		this->display();
	}
	CommonException::~CommonException()
	{}
#pragma endregion

}
