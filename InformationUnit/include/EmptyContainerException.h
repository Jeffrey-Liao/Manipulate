#ifndef EMPTYCONTAINEREXCEPTION_H
#define EMPTYCONTAINEREXCEPTION_H
#include"LiaoException.h"
namespace liaoInfor
{
	class EmptyContainerException : public CommonException
	{
		EmptyContainerException(string className, string methodName)
			:CommonException("EmptyContainer",className,methodName,"You cannot do this operation to an empty container")
		{}
	};
}
#endif
