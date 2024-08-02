#ifndef OUTOFRANGEEXCEPTION_H
#define OUTOFRANGEEXCEPTION_H
#include"LiaoException.h"
namespace liaoInfor
{
	class OutOfRangeException:public FatalException
	{
	public:
		OutOfRangeException(string className, string methodName)
			:FatalException("OutOfRange", className, methodName, "Given index out of range.")
		{}
	};
}
#endif