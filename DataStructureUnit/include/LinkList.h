#ifndef LINKLIST_H
#define LINKLIST_H
#include "List.h"
#include"LinkNode.h"
namespace liaoUtil
{
	//=std::list
	DYNAMIC
	class LinkList :public List<T>
	{
		using ListNode = ListNode<T>;
		using List = List<T>;
		using LinkNodeStd = LinkNodeStd<T>;
		list<T> dataSource;
	public:
		LinkList()
			:List()
		{}
		LinkList(int _size)
			:List(_size)
		{}
		LinkList(List& obj)
			:List(obj)
		{}
		LinkList(LinkList& obj)
			:List(obj)
		{}
		LinkList(vector<T>& obj)
		{
			this->StdToStd(dataSource,obj);
		}
		LinkList(initializer_list<T> ini)
		{
			this->StdToStd(dataSource, ini);
		}
		LinkList(list<T>& obj)
		{
			dataSource = obj;
		}
	private:
		void allocate(int _size) override
		{
			dataSource.resize(dataSource.size() + _size);
		}
		
		void newValue(List& obj)
		{
			for (int n = 0; n < obj.size(); ++n)
				dataSource.push_back(obj[n]);
		}
		int inner_findIndex(const T& value)const 
		{
			auto itor = dataSource.begin();
			int n = 0;
			while (itor != dataSource.end())
			{
				if (*itor == value)
					return n;
				++itor;
				++n;
			}
			return -1;
		}
		list<T>::iterator iterate(int pos, list<T>::iterator itor)
		{
			for (int n = 0; n < pos; ++n)
				++itor;
			return itor;
		}
		list<T>::iterator riterate(int pos, list<T>::iterator itor)
		{
			for (int n = 0; n < pos; ++n)
				--itor;
			return itor;
		}
		bool validPos(Index pos)const override
		{
			return pos < dataSource.size()&&pos>=0;
		}
		void free() override
		{
			dataSource.clear();
		}
	public:
		string classID() const override
		{
			return "LinkList";
		}
		int size() const override
		{
			return dataSource.size();
		}
		bool isEmpty() const override
		{
			return dataSource.empty();
		}
		T& first()override
		{
			return *dataSource.begin();
		}
		T& last()override
		{
			return *(--dataSource.end());
		}

		T& add(T& data)override
		{
			dataSource.push_back(data);
			return last();
		}
		T& add(List& obj) override
		{
			newValue(obj);
			return *riterate(obj.size(),dataSource.end());
		}
		T& add(int number, T& value)
		{
			for (int n = 0; n < number; ++n)
				dataSource.push_back(value);
			return *riterate(number,dataSource.end());
		}
		T& add(vector<T>& vec)
		{
			this->StdToStd(dataSource,vec);
			return *riterate( vec.size(), dataSource.end());
		}
		T& add(list<T>& ls)
		{
			this->StdToStd(dataSource, ls);
			return *riterate(ls.size(),dataSource.end());
		}
		T& add(initializer_list<T>& ini)
		{
			this->StdToStd(dataSource, ini);
			return* riterate(ini.size(), dataSource.end());
		}
		T& add(T* arr, int size)
		{
			for (int n = 0; n < size; ++n)
			{
				dataSource.push_back(arr[n]);
			}
			return *riterate(size ,dataSource.end());
		}
		T& add(const T&& value)
		{
			return dataSource.emplace_back(value);
		}
		T& add(int number, T&& value) override
		{
			return dataSource.emplace_back(value);
		}
		void remove(Index pos)
		{
			dataSource.erase(iterate(pos, dataSource.begin()));
		}
		void remove(Index start, Index end)
		{
			if (start < end && validPos(start) && validPos(end))
			{
				auto itor1 = dataSource.begin(), itor2 = dataSource.begin(),itor = dataSource.begin();
				for (int n = 0; n < dataSource.size(); ++n,itor++)
				{
					if (n == start)
						itor1 = itor;
					if (n == end)
					{
						itor2 = itor;
						break;
					}
				}
				dataSource.erase(itor1, itor2);
			}
		}
		void remove(T& data)
		{
			dataSource.remove(data);
		}
		void remove(T&& value)override
		{
			dataSource.remove(value);
		}
		void removeAll(T& data)
		{
			for (auto itor = std::remove(dataSource.begin(), dataSource.end(), data); itor != dataSource.end(); dataSource.erase(itor));
		}
		void remove(initializer_list<T>& ini)
		{
			for (auto& var : ini)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), var));
		}
		void remove(List& obj)
		{
			for(int n =0;n<obj.size();++n)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), obj[n]));
		}
		void remove(vector<T>& vec)
		{
			for (auto& var : vec)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), var));
		}
		void remove(list<T>& ls) 
		{
			for (auto& var : ls)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), var));
		}
		void remove(T* arr, int size)
		{
			for (int n = 0; n < size; ++n)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), arr[n]));
		}
		T& insert(Index pos, T& value)
		{
			return *dataSource.insert(iterate(pos,dataSource.begin()), value);
		}
		T& insert(Index pos, T&& value)override
		{
			return *dataSource.insert(iterate(pos,dataSource.begin()), value);
		}
		T& insert(Index pos, List& list)
		{
			for (int n = 0; n < list.size(); ++n)
				dataSource.insert(iterate(pos, dataSource.begin()), list[n]);
			return *iterate(pos,dataSource.begin());
		}
		T& insert(Index pos, vector<T>& vec)
		{
			dataSource.insert(iterate(pos, dataSource.begin()), vec.begin(), vec.end());
			return *iterate(pos, dataSource.begin());
		}
		T& insert(Index pos, list<T>& list)
		{
			dataSource.insert(iterate(pos, dataSource.begin()), list.begin(), list.end());
			return *iterate(pos, dataSource.begin());
		}
		T& insert(Index pos, initializer_list<T>& ini)
		{
			dataSource.insert(iterate(pos, dataSource.begin()),ini.begin(), ini.end());
			return *iterate(pos, dataSource.begin());
		}
		T& get(Index index)
		{
			return *iterate(index, dataSource.begin());
		}
		int indexOf(T& data) const override
		{
			return inner_findIndex(data);
		}
		void clear()
		{
			dataSource.clear();
		}
		bool equals(List& obj) const
		{
			if (obj.size() != dataSource.size())
				return false;
			auto itor = dataSource.begin();
			for (int n = 0; n < obj.size(); ++n)
			{
				if (*itor != obj[n])
					return false;
			}
			return true;
		}
		bool equals(vector<T>& vec) const
		{
			return std::equal(dataSource.begin(), dataSource.end(), vec.begin());
		}
		bool equals(list<T>& list)const
		{
			return dataSource == list;
		}
		bool equals(initializer_list<T>& ini)const
		{
			return std::equal(dataSource.begin(), dataSource.end(), ini.begin());
		}
		bool equals(T* arr, int size)const
		{
			if (dataSource.size() != size)
				return false;
			auto itor = dataSource.begin();
			for (int n = 0; n < size; ++n)
			{
				if (arr[n] != *itor)
					return false;
			}
			return true;
		}
		void assign(vector<T>& vec)
		{
			dataSource.resize(vec.size());
			std::copy(vec.begin(), vec.end(), dataSource.begin());
		}
		void assign(list<T>& list)
		{
			dataSource = list;
		}
		void assign(initializer_list<T>& ini)
		{
			dataSource.resize(ini.size());
			std::copy(ini.begin(), ini.end(), dataSource.begin());
		}
		vector<T> toVector() const
		{
			vector temp(dataSource.begin(), dataSource.end());
			return temp;
		}
		bool contains(T&& value)const
		{
			return std::find(dataSource.begin(), dataSource.end(), value) != dataSource.end();
		}
		bool contains(T& value)const
		{
			return std::find(dataSource.begin(), dataSource.end(), value) != dataSource.end();
		}
		bool contains(List& obj)const
		{
			for (int n = 0; n < obj.size(); ++n)
			{
				for (auto& var : dataSource)
					if (var != obj[n])
						return false;
			}
			return true;
		}
		bool contains(vector<T>& vec)const
		{
			for (int n = 0; n < vec.size(); ++n)
			{
				for (auto& var : dataSource)
					if (var != vec[n])
						return false;
			}
			return true;
		}
		bool contains(list<T>& list)const
		{
			for (auto& var2 : list)
			{
				for (auto& var : dataSource)
					if (var != var2)
						return false;
			}
			return true;
		}
		bool contains(initializer_list<T>& ini)const
		{
			for (auto& var2 : ini)
			{
				for (auto& var : dataSource)
					if (var != var2)
						return false;
			}
			return true;
		}
		void sort(void(*sortFunc)(List& _this) = NULL)override
		{
			if (sortFunc != NULL)
				sortFunc(*this);
			else
				dataSource.sort();
		}

		void apply(void(*operation)(T& value)) override
		{
			for (auto& var : dataSource)
				operation(var);
		}
		int count(T& data)const override
		{
			return std::count(dataSource.begin(), dataSource.end(), data);
		}
		void subList(List& destination, Index start, Index end) override
		{
			for (int n = start; n <= end; ++n)
				destination.add(*iterate(n, dataSource.begin()));
		}
		void copyFrom(List& obj) override
		{
			dataSource.resize(obj.size());
			for (int n = 0; n < size(); ++n)
				*iterate(n, dataSource.begin()) = obj[n];
		}
		void copyTo(List& obj) override
		{
			obj.resize(size());
			for (int n = 0; n < size(); ++n)
				obj[n] = *iterate(n, dataSource.begin());
		}
		void set(Index pos, T& value)
		{
			*iterate(pos, dataSource.begin()) = value;
		}
		void swap(Index pos1, Index pos2)
		{
			std::swap(*iterate(pos1, dataSource.begin()), *iterate(pos2, dataSource.begin()));
		}
		void reverse()
		{
			std::reverse(dataSource.begin(), dataSource.end());
		}
		void resize(Index newSize)
		{
			allocate(newSize);
		}
	};
	class LiaoLinkList
	{

	};
}

#endif