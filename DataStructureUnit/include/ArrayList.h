#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "List.h"
namespace liaoUtil
{
	DYNAMIC
	class ArrayList:public List<T>
	{
		using List = List<T>;
		vector<T> dataSource;
	protected:
		void allocate(size_t size) override
		{
			dataSource.reserve(size);
		}
		void newValue(const T& value)override
		{ 
			dataSource.push_back(value);
		}
		void newValue(List& obj)
		{
			for (int n = 0; n < obj.size(); ++n)
			{
				dataSource.push_back(obj[n]);
			}
		}
		int inner_findIndex(const T& data)
		{
			auto var = dataSource.begin();
			int n =0;
			while (var != dataSource.end())
			{
				if (data == *var)
					return n;
				++n;
				var++;
			}
			return -1;
		}
		bool validPos(const Index pos)const override
		{
			return pos < dataSource.size()&& pos >=0;
		}
		void free()
		{
			dataSource.clear();
		}
	public:
		ArrayList()
			:List()
		{}
		ArrayList(const size_t size)
			:List(size)
		{}
		ArrayList(const List& obj)
			:List(obj)
		{}
		ArrayList(const vector<T>& obj)
		{
			dataSource = obj;
		}
		ArrayList(const initializer_list<T> ini)
		{
			this->StdToStd(ini);
		}
		ArrayList(const list<T>& obj)
		{
			this->StdToStd(obj);
		}
	public:
		constexpr string classID() const override
		{
			return "ArrayList";
		}
		constexpr size_t size()const override
		{
			return dataSource.size();
		}
		constexpr bool isEmpty() const override
		{
			return dataSource.empty();
		}
		constexpr const T& first()const override
		{
			this->emptyListCheck("first()");
			return dataSource[0];
		}
		constexpr const T& last() const override
		{
			this->emptyListCheck("last()");
			return dataSource[dataSource.size() - 1];
		}
		T& add(const T& data)override
		{
			dataSource.push_back(data);
			return dataSource[dataSource.size() - 1];
		}
		T& add(const List& obj)override
		{
			newValue(obj);
			int index = dataSource.size() - obj.size() - 1;
			return dataSource[index];
		}
		T& add(const int number, const T& value)override
		{
			for (int n = 0; n < number; ++n)
				dataSource.push_back(value);
			int index = dataSource.size() - number - 1;
			return dataSource[index];
		}
		T& add(const int number, T&& value) override
		{
			return dataSource.emplace_back(value);
		}
		T& add(const vector<T>& vec)override
		{
			this->StdToStd( vec);
			int index = dataSource.size() - vec.size() - 1;
			return dataSource[index];
		}
		T& add(const list<T>& ls)override
		{
			this->StdToStd( ls);
			int index = dataSource.size() - ls.size() - 1;
			return dataSource[index];
		}
		T& add(const initializer_list<T>& ini)override
		{
			this->StdToStd( ini);
			int index = dataSource.size() - ini.size() - 1;
			return dataSource[index];
		}
		T& add(const T* arr, const int size)override
		{
			for (int n = 0; n < size; ++n)
				dataSource.push_back(arr[n]);
			int index = dataSource.size() - size - 1;
			return dataSource[index];
		}
		T& add(T&& value)
		{
			return dataSource.emplace_back(value);
		}
		void remove(const Index pos) throw() override
		{
			this->emptyListCheck("remove(Index)");
			this->outRangeCheck(pos,"remove(Index)");
			dataSource.erase(dataSource.begin() + pos);
		}
		void remove(const Index start, const Index end)throw()override
		{
			this->emptyListCheck("remove(Index,Index)");
			this->validIntervalCheck(start, end,"remove(Index,Index)");
			dataSource.erase(dataSource.begin() + start, dataSource.begin() + end);
		}
		void remove(const T& value)override
		{
			this->emptyListCheck("remove(T&)");
			dataSource.erase(std::remove(dataSource.begin(),dataSource.end(),value));
		}
		void remove( T&& value)override
		{
			this->emptyListCheck("remove(T&&)");
			dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), value));
		}
		void removeAll(const T& data)override
		{
			this->emptyListCheck("removeAll(T&)");
			for (auto itor = std::remove(dataSource.begin(), dataSource.end(), data); itor != dataSource.end();dataSource.erase(itor));
		}
		void remove(const initializer_list<T>& ini)override
		{
			this->emptyListCheck("remove(initializer_list<T>&)");
			for (auto& var : ini)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), var));
		}
		void remove(const List& obj)
		{
			this->emptyListCheck("remove(List&)");
			for (int n = 0; n < obj.size(); ++n)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), obj[n]));
		}
		void remove(const vector<T>& vec)override
		{
			this->emptyListCheck("remove(vector<T>&)");
			for (auto& var : vec)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), var));
		}
		void remove(const list<T>& ls)override
		{
			this->emptyListCheck("remove(list<T>&)");
			for (auto& var : ls)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), var));
		}
		void remove(const T* arr, const int size)override
		{
			this->emptyListCheck("remove(T*,int)");
			for (int n = 0; n < size; ++n)
				dataSource.erase(std::remove(dataSource.begin(), dataSource.end(), arr[n]));
		}

		T& insert(const Index pos, const T& value) throw()override
		{
			this->outRangeCheck(pos, "insert(Index,T&)");
			dataSource.insert(dataSource.begin() + pos, value);
			return dataSource[pos];
		}
		T& insert(const Index pos, T&& value)throw()override
		{
			this->outRangeCheck(pos, "insert(Index,T&&)");
			dataSource.insert(dataSource.begin() + pos, value);
			return dataSource[pos];	
		}
		T& insert(const Index pos, const List& list)throw()override
		{
			this->outRangeCheck(pos, "insert(Index,List&)");
			dataSource.reserve(list.size());
			for (int n = 0; n < list.size(); ++n)
				dataSource.insert(dataSource.begin() + pos, list[n]);
			return dataSource[pos];
		}
		T& insert(const Index pos, const vector<T>& vec)throw()override
		{
			this->outRangeCheck(pos, "insert(Index,vector&)");
			dataSource.reserve(vec.size());
			dataSource.insert(dataSource.begin() + pos, vec.begin(), vec.end());
			return dataSource[pos];
		}
		T& insert(const Index pos, const list<T>& list)throw()override
		{
				this->outRangeCheck(pos, "insert(Index,list&)");
				dataSource.reserve(list.size());
				dataSource.insert(dataSource.begin() + pos, list.begin(), list.end());
				return dataSource[pos];
		}
		T& insert(const Index pos, const initializer_list<T>& ini)throw()override
		{
				this->outRangeCheck(pos, "insert(Index,initializer_list&)");
				dataSource.reserve(ini.size());
				dataSource.insert(dataSource.begin() + pos, ini.begin(), ini.end());
				return dataSource[pos];
		}
		constexpr T& get(const Index index)throw()override
		{
			this->emptyListCheck("get(Index)");
			this->outRangeCheck(index, "get(Index)");
			return dataSource[index];
		}
		constexpr size_t indexOf(const T& data) const override
		{
			int n = 0;
			for (auto& var : dataSource)
			{
				if (var == data)
					return n;
				n++;
			}
			return -1;
		}
		constexpr void clear()override
		{
			dataSource.clear();
		}
		constexpr bool equals(const List& obj) const override
		{
			if (dataSource.size() != obj.size())
				return false;
			else
			{
				for (int n = 0; n < dataSource.size(); ++n)
					if (dataSource[n] != obj[n])
						return false;
				return true;
			}
		}
		constexpr bool equals(const vector<T>& vec) const override
		{
			return dataSource == vec;
		}
		constexpr bool equals(const list<T>& list)const override
		{
			return std::equal(dataSource.begin(),dataSource.end(), list.begin());
		}
		constexpr bool equals(const initializer_list<T>& ini)const override
		{
			return std::equal(dataSource.begin(), dataSource.end(), ini.begin());
		}
		constexpr bool equals(const T* arr, const int size)const override
		{
			if (dataSource.size() != size)
				return false;
			else
			{
				for (int n = 0; n < size; ++n)
					if (dataSource[n] != arr[n])
						return false;
				return true;
			}
		}
		constexpr void assign(const vector<T>& vec)
		{
			dataSource = vec;
		}
		constexpr void assign(const list<T>& list)
		{
			dataSource.resize(list.size());
			std::copy(list.begin(), list.end(), dataSource.begin());
		}
		constexpr void assign(const initializer_list<T>& ini)
		{
			dataSource.resize(ini.size());
			std::copy(ini.begin(), ini.end(), dataSource.begin());
		}
		constexpr vector<T> toVector()const override
		{
			return dataSource;
		}
		constexpr bool contains(T&& value)const override
		{
			return std::find(dataSource.begin(), dataSource.end(), value) != dataSource.end();
		}
		constexpr bool contains(const T& value)const override
		{
			return std::find(dataSource.begin(), dataSource.end(), value) != dataSource.end();
		}
		constexpr bool contains(const List& obj)const override
		{
			for (int n = 0; n < obj.size(); ++n)
			{
				for (auto& var : dataSource)
					if (var != obj[n])
						return false;
			}
			return true;
		}
		constexpr bool contains(const vector<T>& vec)const override
		{
			for (int n = 0; n < vec.size(); ++n)
			{
				for (auto& var : dataSource)
					if (var != vec[n])
						return false;
			}
			return true;
		}
		constexpr bool contains(const list<T>& list)const override
		{
			for (auto& var2: list)
			{
				for (auto& var : dataSource)
					if (var != var2)
						return false;
			}
			return true;
		}
		constexpr bool contains(const initializer_list<T>& ini)const override
		{
			for (auto& var2 : ini)
			{
				for (auto& var : dataSource)
					if (var != var2)
						return false;
			}
			return true;
		 }
		void sort(void(*sortFunc)(List& _this) = NULL) throw()override 
		{
			this->emptyListCheck("sort(sortFunc*)");
			if (sortFunc != NULL)
				sortFunc(*this);
			else
				std::sort(dataSource.begin(), dataSource.end());
		}
		
		void apply(void(*operation)(T& value)) override
		{
			for (auto& var : dataSource)
				operation(var);
		}
		constexpr size_t count(const T& data)const override
		{
			return std::count(dataSource.begin(), dataSource.end(), data);
		}
		void subList(List& destination, const Index start, const Index end)throw() override
		{
			this->validIntervalCheck(start, end, "subList(List&,Index,Index)");
			for (int n = start; n <= end; ++n)
				destination.add(dataSource[n]);
		}
		constexpr void copyFrom(const List& obj) override
		{
			if (obj.size() > size())
				dataSource.resize(obj.size());
			else
				dataSource.resize(obj.size());
			for (int n = 0; n < dataSource.capacity(); ++n)
				dataSource[n] = obj[n];
		}
		constexpr void copyTo(List& obj) override
		{
			obj.resize(size());
			for (int n = 0; n < size(); ++n)
				obj[n] = dataSource[n];
		}
		constexpr void set(const Index pos, const T& value)throw()override
		{
			this->outRangeCheck(pos, "set(Index,T&)");
			dataSource[pos] = value;
		}
		constexpr void swap(const Index pos1, const Index pos2) throw()override
		{
			this->outRangeCheck(pos1,"swap");
			this->outRangeCheck(pos2, "swap");
				std::swap(dataSource[pos1], dataSource[pos2]);
		}
		constexpr void reverse() throw()override
		{
			this->emptyListCheck("reverse()");
			std::reverse(dataSource.begin(), dataSource.end());
		}
		constexpr void resize(const Index newSize)override
		{
			dataSource.resize(newSize);
		}
		~ArrayList() override
		{
			dataSource.clear();
		}
	};
}
#endif
