#ifndef SET_H
#define SET_H
#include"List.h"
#include <set>
namespace liaoUtil
{
	using std::set;
	DYNAMIC
	class Set
	{
		set<T> dataSource;
	private:
	public:
		Set()
			:List()
		{}
		Set(int size)
			:List(size)
		{}
		Set(List& obj)
			:List(obj)
		{}
	public:
	};
}

#endif