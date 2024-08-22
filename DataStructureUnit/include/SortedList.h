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
		T value;
	private:
		static int upperDivide(const int val)
		{
			return val  == 1||val == 0 ? val : val / 2;
		}
		list::iterator rmove(list::iterator itor, int step)
		{
			for (int n = 0; n < step&&itor!= this->dataSource.end(); ++n)
				itor++;
			return itor;
		}
		list::iterator lmove(list::iterator itor, int step)
		{
			for (int n = 0; n < step && itor != this->dataSource.begin(); ++n)
				itor--;
			return itor;
		}
		void newValue(const T& value) override
		{
			if (!this->dataSource.empty())
			{
				if (value < *this->dataSource.begin())
					this->dataSource.push_front(value);
				else if (value > *(--this->dataSource.end()))
					this->dataSource.push_back(value);
				else
				{
					int pos = this->dataSource.size() / 2;
					auto itor = this->iterate(pos);
					while (itor != this->dataSource.end())
					{
						if (*itor <= value)
							itor = rmove(itor, pos == 0? 1 : pos / 2);
						else
							itor = lmove(itor, pos == 0 ? 1 : pos / 2);
						if (itor == this->dataSource.end())
						{
							this->dataSource.insert(itor, value);
							break;
						}
						else if( *itor > value && *(--itor) <= value)
						{
							++itor;
							this->dataSource.insert(itor, value);
							break;
						}
						pos /= 2;
					}
				}
			}
			else
				this->dataSource.push_back(value);
		}
		void newValueStable(const T& value)
		{
			bool complete = false;
			auto itor = this->dataSource.begin();
			if (!this->dataSource.empty())
			{
				while (itor != this->dataSource.end())
				{
					if (*itor > value)
					{
						this->dataSource.insert(itor, value);
						complete = true;
						break;
					}
					itor++;
				}
				if(!complete)
					this->dataSource.insert(itor, value);
			}
			else
				this->dataSource.insert(itor, value);
		}
		T& insert(const Index pos, const T& value)
		{
			return add(value);
		}
		T& insert(const Index pos, const T&& value)override
		{
			return add(value);
		}
		T& insert(const Index pos, const List& list)
		{
			return add(list);
		}
		T& insert(const Index pos, const  vector<T>& vec)
		{
			return add(vec);
		}
		T& insert(const Index pos, const list& list)
		{
			return add(list);
		}
		T& insert(const Index pos, const initializer_list<T>& ini)
		{
			return add(ini);
		}
		void swap(const Index pos1, const  Index pos2)
		{

		}
		void set(const Index pos, const T& value)
		{
		}
		void resize(const Index newSize)
		{
		}
		constexpr T& get(const Index pos)
		{
			this->emptyListCheck("get(Index)");
			return value = *this->iterate(pos);
		}
	public:
		SortedList()
			:LinkList()
		{}
		SortedList(int size)
			:LinkList(size)
		{}
		SortedList(const List& obj)
			:LinkList(obj)
		{}
		SortedList(const vector<T> & obj)
		{
			for (auto& var : obj)
				newValue(var);
		}
		SortedList(const initializer_list<T> ini)
		{
			for (auto& var : ini)
				newValue(var);
		}
		SortedList(const list& obj)
		{
			for (auto& var : obj)
				newValue(var);
		}
		constexpr string classID() const override
		{
			return "SortedList";
		}

		T& add(const T& data)override
		{
			newValue(data);
			return value;
		}
		T& add(const List& obj) override
		{
			this->LinkList::newValue(obj);
			return value;
		}
		T& add(const int number, const T& value)
		{
			for (int n = 0; n < number; ++n)
				newValue(value);
			return value;
		}
		T& add(const vector<T>& vec)
		{
			this->StdToStd( vec);
			return value;
		}
		T& add(const list& ls)
		{
			this->StdToStd( ls);
			return value;
		}
		T& add(const initializer_list<T>& ini)
		{
			this->StdToStd(ini);
			return value;
		}
		T& add(const T* arr, const int size)
		{
			for (int n = 0; n < size; ++n)
			{
				newValue(arr[n]);
			}
			return value;
		}
		T& add(T&& value)
		{
			newValue(value);
			return this->value;
		}
		T& add(const int number, T&& value) override
		{
			newValue(value);
			return this->value;
		}
		
		void assign(const vector<T>& vec)
		{
			this->dataSource.clear();
			this->StdToStd(vec);
		}
		void assign(const list& list)
		{
			this->dataSource.clear();
			this->StdToStd( list);
		}
		void assign(const initializer_list<T>& ini)
		{
			this->dataSource.clear();
			this->StdToStd( ini);
		}
		constexpr const  T& get(const Index index) const
		{
			this->emptyListCheck("get(Index)");
			this->value = *this->iterate(index);
			return this->value;
		}
		~SortedList()
		{
			this->dataSource.clear();
		}
	};
}

#endif