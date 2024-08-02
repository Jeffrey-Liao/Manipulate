#ifndef ONELIST_H
#define ONELIST_H
#include "List.h"
#include<forward_list>
namespace liaoUtil
{
	DYNAMIC
	class OneList:public List<T>
	{
		using List = List<T>;
		using forward_list = std::forward_list<T>;
		forward_list dataSource;
	public:
		OneList()
			:List()
		{}
		OneList(int size)
			:List(size)
		{}
		OneList(List& obj)
			:List(obj)
		{}
	private:
		void allocate(int size)
		{

		}
		void newValue(const T& value)
		{

		}
	public:
		string classID() const override
		{
			return "OneList";
		}
	};
}
#endif
