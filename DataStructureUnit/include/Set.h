#ifndef SET_H
#define SET_H
#include"List.h"
#include <set>
namespace liaoUtil
{
	using std::set;
	DYNAMIC
	class Set:public List<T>
	{
		using List = List<T>;
		using set = set<T>;
		set dataSource;
		T value;
	private:
		void allocate(int size)
		{
			//无法对set执行allocate操作;
		}
		bool validPos(Index pos)
		{
			return pos < dataSource.size();
		}
		template<class Container>
		void StdToSet(Container& obj)
		{
			for (auto& val : obj)
				dataSource.insert(val);
		}
		set::iterator iterate(int pos)
		{
			set::iterator itor;
			int end = 0;
			bool dir = false;
			if ((dir = pos > dataSource.size()) / 2)
			{
				itor = dataSource.end();
				end = dataSource.size() - pos+1;
			}
			else
			{
				itor = dataSource.begin();
				end = pos;
			}
			for (int n = 0; n < end; ++n)
			{
				if (dir)
					++itor;
				else
					--itor;
			}

		}
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
		Set(vector<T>& obj)
		{
			this->StdToSet(obj);
		}
		Set(initializer_list<T> ini)
		{
			this->StdToSet(ini);
		}
		Set(list<T>& ls)
		{
			this->StdToSet(ls);
		}
		Set(set& obj)
		{
			dataSource = obj;
		}
	public:

	};
}

#endif