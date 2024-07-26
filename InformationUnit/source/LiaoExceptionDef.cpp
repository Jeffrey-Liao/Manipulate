#include "../include/LiaoException.h"
#include <cstdlib>
namespace liaoInfor
{
#pragma region LiaoException
	LiaoException::LiaoException(string type, string className, string methodName, string message)
	{
		errorMessage = "[" + type + " :: Exception]" + "(Thrown by : " + className + ")'s function: " + "{" + methodName + "}:  " + message;
	}
	void LiaoException::debug()
	{
		DebugInfor::instance.write(errorMessage);
	}
	void LiaoException::display()
	{
		ErrorInfor::instance.display(this->errorMessage);
	}
	void LiaoException::error()
	{
		ErrorInfor::instance.write(this->errorMessage);
	}
	LiaoException::~LiaoException()
	{}
#pragma endregion
#pragma region FatalException
	FatalException::FatalException(string className, string methodName, string message)
		:LiaoException("Fatal", className, methodName, message)
	{
		this->error();
		this->display();
		abort();
	}
	FatalException::~FatalException()
	{

	}
#pragma endregion
#pragma region CommonException
	CommonException::CommonException(string className, string methodName, string message)
		:LiaoException("Common", className, methodName, message)
	{
		this->display();
	}
	CommonException::~CommonException()
	{}
#pragma endregion
#pragma region DebugException
	DebugException::DebugException(string className, string methodName, string message)
		:LiaoException("Debug",className,methodName,message)
	{
		this->debug();
	}
	DebugException::~DebugException()
	{}
#pragma endregion

}
