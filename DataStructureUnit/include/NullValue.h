#ifndef NULLVALUE
#define NULLVALUE
#include"common.h"
namespace liaoUtil
{
	class NullValue
	{
		size_t byteLen;
		char* ptr;
	private:
		NullValue()
			:ptr(NULL), byteLen(0)
		{}
		bool having();
		void free();
	public:
		void reserve(int size);
		void* get(int size = 0);
		~NullValue();
	};
}
#endif
