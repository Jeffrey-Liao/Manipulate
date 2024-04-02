#include "LiaoException.h"
namespace liao
{
	LiaoException::LiaoException(string className, string methodName, string message, int line)
	{
		errorMessage = "(" + className + ")" + " " + "{" + methodName + "}:" + " " + message;
		if (line > 0)
		{
			errorMessage+= " in line " + STD to_string(line);
		}
	}
	void LiaoException::display()
	{
		ErrorInfor::instance.display(this->errorMessage);
	}
	void LiaoException::tofile()
	{
		ErrorInfor::instance.write(this->errorMessage);
	}
	LiaoException::~LiaoException()
	{
		tofile();
	}
}
