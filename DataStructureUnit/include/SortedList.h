#ifndef SORTEDLIST_H
#define SORTEDLIST_H
#include "LinkList.h"
namespace liaoUtil
{
	DYNAMIC
	class SortedList:public LinkList<T>
	{
		using list = list<T>;
		using List = List<T>;
		using LinkList = LinkList<T>;
	private:
		void newValue(const T& value) override
		{
			this->dataSource.insert(findPlace(value), value);
		}
		list::iterator findPlace(const T& value)
		{
			auto itor = this->iterate(this->dataSource.size() / 2);
			while (itor != this->dataSource.end())
			{

			}
			return itor;
		}
	public:
		SortedList()
			:LinkList()
		{}
		SortedList(int size)
			:LinkList(size)
		{}
		SortedList(List& obj)
			:LinkList(obj)
		{}
		SortedList(vector<T> & obj)
		{

		}
		SortedList(initializer_list<T> ini)
		{

		}
		SortedList(list& obj)
		{

		}
	};
}

#endif