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
		virtual void allocate(int _size) = 0;

		virtual void newValue(const T& value) = 0;
		virtual void newValue(Index pos, const T& value) = 0;
		virtual void newValue(List& obj) = 0;

		virtual void delNode(const T& value) = 0;
		virtual void delNode(Index pos) = 0;

		virtual bool validPos(Index pos) const = 0;
		virtual void free() = 0;
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