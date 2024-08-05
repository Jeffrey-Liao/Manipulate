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
			this->StdToStd(obj);
		}
		LinkList(initializer_list<T> ini)
		{
			this->StdToStd( ini);
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
		constexpr bool validPos(Index pos)const override
		{
			return pos < dataSource.size()&&pos>=0;
		}
		constexpr void free() override
		{
			dataSource.clear();
		}
	public:
		virtual string classID() const override
		{
			return "LinkList";
		}
		constexpr int size() const override
		{
			return dataSource.size();
		}
		constexpr bool isEmpty() const override
		{
			return dataSource.empty();
		}
		constexpr const T& first()override
		{
			this->emptyListCheck("first()");
			return *dataSource.begin();
		}
		constexpr const T& last()override
		{
			this->emptyListCheck("last()");
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
			this->StdToStd(vec);
			return *iterate(dataSource.size() - vec.size());
		}
		virtual T& add(list<T>& ls)
		{
			this->StdToStd( ls);
			return *iterate(dataSource.size() - ls.size());
		}
		virtual T& add(initializer_list<T>& ini)
		{
			this->StdToStd(ini);
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
		void remove(Index pos)throw()
		{
			this->emptyListCheck("remove(Index)");
			this->outRangeCheck(pos,"remove(Index)");
			dataSource.erase(iterate(pos));
		}
		void remove(Index start, Index end)throw()
		{
			this->emptyListCheck("remove(Index,Index)");
			this->validIntervalCheck(start, end,"remove(Index,Index)");
			auto itor1 = dataSource.begin(), itor2 = dataSource.begin(), itor = dataSource.begin();
			for (int n = 0; n < dataSource.size(); ++n, itor++)
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
		void remove(T& data)throw()
		{
			this->emptyListCheck("remove(T&)");
			dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), data));
		}
		void remove(T&& value)throw()override
		{
			this->emptyListCheck("remove(T&&)");
			dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), value));
		}
		void removeAll(T& data)throw()
		{
			this->emptyListCheck("removeAll(T&)");
			dataSource.remove(data);
		}
		void remove(initializer_list<T>& ini)
		{
			this->emptyListCheck("removeAll(initializer_list<T>&)");
			for (auto& var : ini)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), var));
		}
		void remove(List& obj)
		{
			this->emptyListCheck("removeAll(List&)");
			for(int n =0;n<obj.size();++n)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), obj[n]));
		}
		void remove(vector<T>& vec)
		{
			this->emptyListCheck("removeAll(vector<T>&)");
			for (auto& var : vec)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), var));
		}
		void remove(list<T>& ls) 
		{
			this->emptyListCheck("removeAll(list<T>&)");
			for (auto& var : ls)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), var));
		}
		void remove(T* arr, int size)
		{
			this->emptyListCheck("removeAll(T*,int)");
			for (int n = 0; n < size; ++n)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), arr[n]));
		}
		virtual T& insert(Index pos, T& value)
		{
			this->outRangeCheck(pos,"insert(Index,T&)");
			return *dataSource.insert(iterate(pos), value);
		}
		virtual T& insert(Index pos, T&& value)override
		{
			this->outRangeCheck(pos, "insert(Index,T&&)");
			return *dataSource.insert(iterate(pos), value);
		}
		virtual T& insert(Index pos, List& list)
		{
			this->outRangeCheck(pos, "insert(Index,List&)");
			for (int n = 0; n < list.size(); ++n)
				dataSource.insert(iterate(pos+n), list[n]);
			return *iterate(pos);
		}
		virtual T& insert(Index pos, vector<T>& vec)
		{
			this->outRangeCheck(pos, "insert(Index,vector<T>&)");
			dataSource.insert(iterate(pos), vec.begin(), vec.end());
			return *iterate(pos);
		}
		virtual T& insert(Index pos, list<T>& list)
		{
			this->outRangeCheck(pos, "insert(Index,vector<T>&)");
			dataSource.insert(iterate(pos), list.begin(), list.end());
			return *iterate(pos);
		}
		virtual T& insert(Index pos, initializer_list<T>& ini)
		{
			this->outRangeCheck(pos, "insert(Index,vector<T>&)");
			dataSource.insert(iterate(pos),ini.begin(), ini.end());
			return *iterate(pos);
		}
		constexpr T& get(Index index)
		{
			this->outRangeCheck(index,"get(Index)");
			return *iterate(index);
		}
		int indexOf(T& data) const override
		{
			return inner_findIndex(data);
		}
		constexpr void clear()
		{
			dataSource.clear();
		}
		constexpr bool equals(List& obj) const
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
		constexpr bool equals(vector<T>& vec) const
		{
			return std::equal(dataSource.begin(), dataSource.end(), vec.begin());
		}
		constexpr bool equals(list<T>& list)const
		{
			return dataSource == list;
		}
		constexpr bool equals(initializer_list<T>& ini)const
		{
			return std::equal(dataSource.begin(), dataSource.end(), ini.begin());
		}
		constexpr bool equals(T* arr, int size)const
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
		constexpr virtual void assign(vector<T>& vec)
		{
			dataSource.resize(vec.size());
			std::copy(vec.begin(), vec.end(), dataSource.begin());
		}
		constexpr virtual void assign(list<T>& list)
		{
			dataSource = list;
		}
		constexpr virtual void assign(initializer_list<T>& ini)
		{
			dataSource.resize(ini.size());
			std::copy(ini.begin(), ini.end(), dataSource.begin());
		}
		vector<T> toVector() const
		{
			vector temp(dataSource.begin(), dataSource.end());
			return temp;
		}
		constexpr bool contains(T&& value)const
		{
			return std::find(dataSource.begin(), dataSource.end(), value) != dataSource.end();
		}
		constexpr bool contains(T& value)const
		{
			return std::find(dataSource.begin(), dataSource.end(), value) != dataSource.end();
		}
		constexpr bool contains(List& obj)const
		{
			for (int n = 0; n < obj.size(); ++n)
			{
				for (auto& var : dataSource)
					if (var != obj[n])
						return false;
			}
			return true;
		}
		constexpr bool contains(vector<T>& vec)const
		{
			for (int n = 0; n < vec.size(); ++n)
			{
				for (auto& var : dataSource)
					if (var != vec[n])
						return false;
			}
			return true;
		}
		constexpr bool contains(list<T>& list)const
		{
			for (auto& var2 : list)
			{
				for (auto& var : dataSource)
					if (var != var2)
						return false;
			}
			return true;
		}
		constexpr bool contains(initializer_list<T>& ini)const
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
			this->emptyListCheck("sort(sortFunc*)");
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
		constexpr int count(T& data)const override
		{
			return std::count(dataSource.begin(), dataSource.end(), data);
		}
		void subList(List& destination, Index start, Index end) override
		{
			this->emptyListCheck("subList(List&)");
			this->validIntervalCheck(start, end, "subList(List&)");
			for (int n = start; n <= end; ++n)
				destination.add(*iterate(n));
		}
		constexpr void copyFrom(List& obj) override
		{
			dataSource.resize(obj.size());
			for (int n = 0; n < size(); ++n)
				*iterate(n) = obj[n];
		}
		constexpr void copyTo(List& obj) override
		{
			obj.resize(size());
			for (int n = 0; n < size(); ++n)
				obj[n] = *iterate(n);
		}
		constexpr virtual void set(Index pos, T& value)
		{
			this->outRangeCheck(pos, "set(Index,T&)");
			*iterate(pos) = value;
		}
		constexpr virtual void swap(Index pos1, Index pos2)
		{
			this->outRangeCheck(pos1, "swap(Index,Index)");
			this->outRangeCheck(pos2, "swap(Index,Index)");
			std::swap(*iterate(pos1), *iterate(pos2));
		}
		constexpr void reverse()
		{
			std::reverse(dataSource.begin(), dataSource.end());
		}
		constexpr virtual void resize(Index newSize)
		{
			allocate(newSize);
		}
		virtual ~LinkList() override
		{
			dataSource.clear();
		}
	};
	DYNAMIC
		//
	class LiaoLinkList:public List<T>
	{
		using LinkNode = LinkNode<T>;
		using List = List<T>;
		LinkNode* head;
		int _size;
	private:
		LinkNode* end()
		{
			if (head == NULL)
				return NULL;
			else if (head->isSingle())
				return head;
			else
				return &head->prev();
		}
		void newValue(const T& value)
		{
			LinkNode* ptr = end();
			if (ptr)
				ptr->link(*new LinkNode(ptr,head,value));
		}
		void newValue(const T&& value)
		{
			LinkNode* ptr = end();
			if (ptr)
				ptr->link(*new LinkNode(ptr, head, value));
		}
		void newValue()
		{
			LinkNode* ptr = end();
			if (ptr)
				ptr->link(*new LinkNode(ptr, head));
		}
		void allocate(int size)
		{
			for (int n = 0; n < size; ++n)
				newValue();
		}
		bool validPos(Index pos)
		{
			return pos<_size && pos >0;
		}
		void free()
		{
			LinkNode* del = head;
			for (int n = 0; n < _size; ++n)
			{
				head = &head->next();
				delete del;
				del = head;
			}
			head = NULL;
			_size = 0;
		}
	public:
		LiaoLinkList()
			:List(), head(NULL), _size{}
		{}
		LiaoLinkList(int size)
			:List(size),head(NULL), _size{size}
		{}
		LiaoLinkList(List& obj)
			:List(obj),head(NULL), _size{}
		{}
		LiaoLinkList(vector<T>& vec)
		{
			this->StdToStd(vec);
		}
		LiaoLinkList(list<T> ls)
		{
			this->StdToStd(ls);
		}
		LiaoLinkList(initializer_list<T>& ini)
		{
			this->StdToStd(ini);
		}
		constexpr string classID()const override
		{
			return "LiaoLinkList";
		}
		constexpr int size()
		{
			return _size;
		}
		constexpr bool isEmpty()
		{
			return _size == 0 || head == NULL;
		}
	};
}

#endif