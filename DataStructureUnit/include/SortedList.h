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
		static int upperDivide(int val)
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
						if (*itor > value && *(--itor) <= value)
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
			for (auto& var : obj)
				newValue(var);
		}
		SortedList(initializer_list<T> ini)
		{
			for (auto& var : ini)
				newValue(var);
		}
		SortedList(list& obj)
		{
			for (auto& var : obj)
				newValue(var);
		}
		string classID() const override
		{
			return "SortedList";
		}

		T& add(const T& data)override
		{
			newValue(data);
			return value;
		}
		T& add(List& obj) override
		{
			this->LinkList::newValue(obj);
			return value;
		}
		T& add(int number, T& value)
		{
			for (int n = 0; n < number; ++n)
				newValue(value);
			return value;
		}
		T& add(vector<T>& vec)
		{
			this->StdToStd(this->dataSource, vec);
			return value;
		}
		T& add(list& ls)
		{
			this->StdToStd(this->dataSource, ls);
			return value;
		}
		T& add(initializer_list<T>& ini)
		{
			this->StdToStd(this->dataSource, ini);
			return value;
		}
		T& add(T* arr, int size)
		{
			for (int n = 0; n < size; ++n)
			{
				newValue(arr[n]);
			}
			return value;
		}
		T& add(const T&& value)
		{
			newValue(value);
			return this->value;
		}
		T& add(int number, T&& value) override
		{
			newValue(value);
			return this->value;
		}
		T& insert(Index pos, T& value)
		{
			*this->dataSource.insert(this->iterate(pos), value);
			return value;
		}
		T& insert(Index pos, T&& value)override
		{
			*this->dataSource.insert(this->iterate(pos), value);
			return this->value;
		}
		T& insert(Index pos, List& list)
		{
			for (int n = 0; n < list.size(); ++n)
				this->dataSource.insert(this->iterate(pos + n), list[n]);
			return this->value;
		}
		T& insert(Index pos, vector<T>& vec)
		{
			this->dataSource.insert(this->iterate(pos), vec.begin(), vec.end());
			return this->value;
		}
		T& insert(Index pos, list& list)
		{
			this->dataSource.insert(this->iterate(pos), list.begin(), list.end());
			return this->value;
		}
		T& insert(Index pos, initializer_list<T>& ini)
		{
			this->dataSource.insert(this->iterate(pos), ini.begin(), ini.end());
			return this->value;
		}
		T& get(Index index)
		{
			this->value = *this->iterate(index);
			return this->value;
		}
		void assign(vector<T>& vec)
		{
			this->dataSource.clear();
			this->StdToStd(this->dataSource, vec);
		}
		void assign(list& list)
		{
			this->dataSource.clear();
			this->StdToStd(this->dataSource, list);
		}
		void assign(initializer_list<T>& ini)
		{
			this->dataSource.clear();
			this->StdToStd(this->dataSource, ini);
		}
	};
}

#endif