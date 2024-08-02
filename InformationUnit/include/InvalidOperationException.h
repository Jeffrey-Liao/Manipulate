#ifndef INVALIDOPERATION
#define INVALIDOPERATION
#include"LiaoException.h"
namespace liaoInfor
{
	class InvalidOperationException :FatalException
	{
	public:
		InvalidOperationException(string className,string methodName,string errorMessage)
			:FatalException("InvalidOperation", className, methodName, errorMessage)
		{}
	};
}

#endif
