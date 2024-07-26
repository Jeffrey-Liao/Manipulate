#ifndef INVALID_ARGUMENT_H
#define INVALID_ARGUMENT_H
#include"LiaoException.h"
namespace liaoInfor
{
	class InvalidArgumentException :public CommonException
	{
	public:
		InvalidArgumentException(string className, string methodName, string message)
			:CommonException(className, methodName, message + " and no operation executed")
		{}
	};
}

#endif
