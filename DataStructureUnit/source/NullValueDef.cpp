#include"NullValue.h"
namespace liaoUtil
{
	bool NullValue::having()
	{
		return ptr != NULL;
	}
	void NullValue::reserve(int newSize)
	{
		if (newSize > byteLen)
		{
			byteLen = newSize;
			if (ptr)
				delete ptr;
			ptr = new char[byteLen];
			for (int n = 0; n < byteLen; ++n)
				ptr[n] = 0;
		}
	}
	void NullValue::free()
	{
		if (ptr)
			delete ptr;
		ptr = NULL;
		byteLen = 0;
	}
	void* NullValue::get(int size)
	{
		if(size != 0)
			reserve(size);
		return ptr;
	}
}