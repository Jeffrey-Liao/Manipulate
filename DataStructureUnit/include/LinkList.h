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
			this->stdCopy(obj);
		}
		LinkList(initializer_list<T> ini)
		{
			this->stdCopy(ini);
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
		void newValue(const T& value)override
		{
			dataSource.push_back(value);
		}
		void newValue(Index pos, const T& value)override
		{
			if (this->validPos(pos))
			{
				dataSource.insert(iterate(pos), value);
			}
		}
		void newValue(List& obj)override
		{
			for (int n = 0; n < obj.size(); ++n)
				newValue(obj[n]);
		}
		void delNode(const T& value)override
		{
			std::remove(dataSource.begin(),dataSource.end(),value);
		}
		void delNode(Index pos)override
		{
			if (validPos(pos))
				dataSource.erase(iterate(pos));
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
		list<T>::iterator iterate(int pos)
		{
			static auto itor = dataSource.begin();
			static int last = 0;
			if (last > pos)
				itor = dataSource.begin(),last = 0;
			for (int n = last; n < pos; ++n)
				++itor;
			last = pos;
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
			newValue(data);
			return *(--dataSource.end());
		}
		T& add(List& obj) override
		{
			newValue(obj);
			return *iterate(dataSource.size() - obj.size()-1);
		}
		T& add(int number, T& value)
		{
			for (int n = 0; n < number; ++n)
				newValue(value);
			return *iterate(dataSource.size()-number-1);
		}
		T& add(vector<T>& vec)
		{
			this->stdCopy(vec);
			return *iterate(dataSource.size() - vec.size() - 1);
		}
		T& add(list<T>& ls)
		{
			this->stdCopy(ls);
			return *iterate(dataSource.size() - ls.size() - 1);
		}
		T& add(initializer_list<T>& ini)
		{
			this->stdCopy(ini);
			return *iterate(dataSource.size() - ini.size() - 1);
		}
		T& add(T* arr, int size)
		{
			for (int n = 0; n < size; ++n)
			{
				newValue(arr[n]);
			}
			return *iterate(dataSource.size() - size - 1);
		}
		void remove(Index pos)
		{
			delNode(pos);
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
			delNode(data);
		}
		void removeAll(T& data)
		{
			while (std::remove(dataSource.begin(), dataSource.end(), data) != dataSource.end());
		}
		void remove(initializer_list<T>& ini)
		{
			for (auto& var : ini)
				std::remove(dataSource.begin(), dataSource.end(), var);
		}
		void remove(List& obj)
		{
			for(int n =0;n<obj.size();++n)
				std::remove(dataSource.begin(), dataSource.end(), obj[n]);
		}
		void remove(vector<T>& vec)
		{
			for (auto& var : vec)
				std::remove(dataSource.begin(), dataSource.end(), var);
		}
		void remove(list<T>& ls) 
		{
			for (auto& var : ls)
				std::remove(dataSource.begin(), dataSource.end(), var);
		}
		void remove(T* arr, int size)
		{
			for (int n = 0; n < size; ++n)
				std::remove(dataSource.begin(), dataSource.end(), arr[n]);
		}
		T& insert(Index pos, T& value)
		{
			return *dataSource.insert(iterate(pos), value);
		}
		T& insert(Index pos, List& list)
		{
			for (int n = 0; n < list.size(); ++n)
				newValue(n + pos, list[n]);
			return *iterate(pos);
		}
		T& insert(Index pos, vector<T>& vec)
		{
			dataSource.insert(iterate(pos), vec.begin(), vec.end());
			return *iterate(pos);
		}
		T& insert(Index pos, list<T>& list)
		{
			dataSource.insert(iterate(pos), list.begin(), list.end());
			return *iterate(pos);
		}
		T& insert(Index pos, initializer_list<T>& ini)
		{
			dataSource.insert(iterate(pos),ini.begin(), ini.end());
			return *iterate(pos);
		}
		T& get(Index index)
		{
			return *iterate(index);
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
		vector<T> toVector() const
		{
			vector temp(dataSource.begin(), dataSource.end());
			return temp;
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
		/*
		* 		void sort(void(*sortFunc)(List& _this) = NULL)override
		{
			if (sortFunc != NULL)
				sortFunc(*this);
			else
				std::sort(dataSource.begin(), dataSource.end());
		}
		*/

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
				destination.add(*iterate(n));
		}
		void copyFrom(List& obj) override
		{
			dataSource.resize(obj.size());
			for (int n = 0; n < size(); ++n)
				*iterate(n) = obj[n];
		}
		void copyTo(List& obj) override
		{
			obj.resize(size());
			for (int n = 0; n < size(); ++n)
				obj[n] = *iterate(n);
		}
		void set(Index pos, T& value)
		{
			*iterate(pos) = value;
		}
		void swap(Index pos1, Index pos2)
		{
			std::swap(*iterate(pos1), *iterate(pos2));
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