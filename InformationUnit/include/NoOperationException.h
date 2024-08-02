#ifndef NOOPERATIONEXCEPTION_H
#define NOOPERATIONEXCEPTION_H
#include "LiaoException.h"
namespace liaoInfor
{
	class NoOperationException :public CommonException
	{
	public:
		NoOperationException(string className, string methodName)
			:CommonException(className,methodName,"The class do not support this operation and program not run any operation to current container.")
		{}
	};
}

#endif
