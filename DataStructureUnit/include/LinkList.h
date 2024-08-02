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
		using List = List<T>;
	protected:
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
	protected:
		void allocate(int _size) override
		{
			dataSource.resize(dataSource.size() + _size);
		}
		void newValue(const T& value)override
		{
			dataSource.push_back(value);
		}
		void newValue(const T&& value)
		{
			dataSource.push_back(value);
		}
		void newValue(List& obj)
		{
			for (int n = 0; n < obj.size(); ++n)
				newValue(obj[n]);
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
			int end = 0;
			auto itor = dataSource.begin();
			if (pos > (dataSource.size()/2))
				itor = dataSource.end(),end = dataSource.size()-pos;
			else
				itor = dataSource.begin(),end = pos;
			for (int n = 0; n < end&&pos>0; ++n)
			{
				if (pos > (dataSource.size() / 2))
					itor--;
				else
					itor++;
			}
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
		virtual string classID() const override
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
		const T& first()override
		{
			return *dataSource.begin();
		}
		const T& last()override
		{
			return *(--dataSource.end());
		}

		virtual T& add(const T& data)override
		{
			newValue(data);
			return *(--dataSource.end());
		}
		virtual T& add(List& obj) override
		{
			newValue(obj);
			return *iterate(dataSource.size()-obj.size());
		}
		virtual T& add(int number, T& value)
		{
			for (int n = 0; n < number; ++n)
				newValue(value);
			return *iterate(dataSource.size()-number);
		}
		virtual T& add(vector<T>& vec)
		{
			this->StdToStd(dataSource,vec);
			return *iterate(dataSource.size() - vec.size());
		}
		virtual T& add(list<T>& ls)
		{
			this->StdToStd(dataSource, ls);
			return *iterate(dataSource.size() - ls.size());
		}
		virtual T& add(initializer_list<T>& ini)
		{
			this->StdToStd(dataSource, ini);
			return* iterate(dataSource.size() - ini.size());
		}
		virtual T& add(T* arr, int size)
		{
			for (int n = 0; n < size; ++n)
			{
				newValue(arr[n]);
			}
			return *iterate(dataSource.size() - size );
		}
		virtual T& add(const T&& value)
		{
			newValue(value);
			return *(--dataSource.end());
		}
		virtual T& add(int number, T&& value) override
		{
			newValue(value);
			return * (--dataSource.end());
		}
		void remove(Index pos)
		{
			dataSource.erase(iterate(pos));
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
		virtual T& insert(Index pos, T& value)
		{
			return *dataSource.insert(iterate(pos), value);
		}
		virtual T& insert(Index pos, T&& value)override
		{
			return *dataSource.insert(iterate(pos), value);
		}
		virtual T& insert(Index pos, List& list)
		{
			for (int n = 0; n < list.size(); ++n)
				dataSource.insert(iterate(pos+n), list[n]);
			return *iterate(pos);
		}
		virtual T& insert(Index pos, vector<T>& vec)
		{
			dataSource.insert(iterate(pos), vec.begin(), vec.end());
			return *iterate(pos);
		}
		virtual T& insert(Index pos, list<T>& list)
		{
			dataSource.insert(iterate(pos), list.begin(), list.end());
			return *iterate(pos);
		}
		virtual T& insert(Index pos, initializer_list<T>& ini)
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
		virtual void assign(vector<T>& vec)
		{
			dataSource.resize(vec.size());
			std::copy(vec.begin(), vec.end(), dataSource.begin());
		}
		virtual void assign(list<T>& list)
		{
			dataSource = list;
		}
		virtual void assign(initializer_list<T>& ini)
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
		virtual void set(Index pos, T& value)
		{
			*iterate(pos) = value;
		}
		virtual void swap(Index pos1, Index pos2)
		{
			std::swap(*iterate(pos1), *iterate(pos2));
		}
		void reverse()
		{
			std::reverse(dataSource.begin(), dataSource.end());
		}
		virtual void resize(Index newSize)
		{
			allocate(newSize);
		}
	};
	class LiaoLinkList
	{

	};
}

#endif