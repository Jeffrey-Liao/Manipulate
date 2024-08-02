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
		int size;
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
			dataSource.resize(size);
		}
		void newValue(const T& value)
		{
			dataSource.push_front(value);
		}
		forward_list::iterator iterate(int pos)
		{
			pos = pos - dataSource.max_size() - 1;
			pos = pos >= 0 ? pos : pos * -1;
			auto itor = dataSource.begin();
			for (int n = 0; n < pos; ++n)
				itor++;
			return itor;
		}
		bool validPos(Index pos)
		{
			return pos < dataSource.max_size();
		}
		void free()
		{
			dataSource.clear();
		}
	public:
		string classID() const override
		{
			return "OneList";
		}

	};
}
#endif
