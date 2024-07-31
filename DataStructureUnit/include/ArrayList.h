#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "ArrayNode.h"
#include "List.h"

namespace liaoUtil
{
	DYNAMIC
	class ArrayList:public List<T>
	{
		using List = List<T>;
		vector<T> dataSource;
	private:
		void allocate(int size) override
		{
			dataSource.reserve(size);
		}
		void newValue(const T& value) override
		{
			dataSource.push_back(value);
		}
		void newValue(Index pos, const T& value)override
		{
			dataSource.insert(dataSource.begin()+pos, value);
		}
		void newValue(List& obj)
		{
			for (int n = 0; n < obj.size(); ++n)
			{
				dataSource.push_back(obj[n]);
			}
		}
		void delNode(const T& data) override
		{
			std::remove(dataSource.begin(), dataSource.end(), data);
		}
		void delNode(unsigned int pos) override
		{
			if (validPos(pos))
				dataSource.erase(dataSource.begin() + pos);
		}
		void inner_find(const T& data)
		{
			std::find(dataSource.begin(), dataSource.end(), data);
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
		bool validPos(Index pos)const override
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
		ArrayList(int size)
			:List(size)
		{
		}
		ArrayList(ArrayList& obj)
			:List(obj)
		{}
		ArrayList(vector<T>& obj)
		{
			dataSource = obj;
		}
		ArrayList(initializer_list<T> ini)
		{
			this->stdCopy(ini);
		}
		ArrayList(list<T>& obj)
		{
			this->stdCopy(obj);
		}
	public:
		string classID() const override
		{
			return "ArrayList";
		}
		int size()const override
		{
			return dataSource.size();
		}
		bool isEmpty() const override
		{
			return dataSource.empty();
		}
		T& first()override
		{
			return dataSource[0];
		}
		T& last() override
		{
			return dataSource[dataSource.size() - 1];
		}
		T& add(T& data)override
		{
			newValue(data);
			return last();
		}
		T& add(List& obj)override
		{
			newValue(obj);
			int index = dataSource.size() - obj.size() - 1;
			return dataSource[index];
		}
		T& add(int number, T& value)override
		{
			for (int n = 0; n < number; ++n)
				newValue(value);
			int index = dataSource.size() - number - 1;
			return dataSource[index];
		}
		T& add(vector<T>& vec)override
		{
			this->stdCopy(vec);
			int index = dataSource.size() - vec.size() - 1;
			return dataSource[index];
		}
		T& add(list<T>& ls)override
		{
			this->stdCopy(ls);
			int index = dataSource.size() - ls.size() - 1;
			return dataSource[index];
		}
		T& add(initializer_list<T>& ini)override
		{
			this->stdCopy(ini);
			int index = dataSource.size() - ini.size() - 1;
			return dataSource[index];
		}
		T& add(T* arr, int size)override
		{
			
			for (int n = 0; n < size; ++n)
				newValue(arr[n]);
			int index = dataSource.size() - size - 1;
			return dataSource[index];
		}
		void remove(Index pos)override
		{
			delNode(pos);
		}
		void remove(Index start, Index end)override
		{
			if(start<end)
				dataSource.erase(dataSource.begin() + start, dataSource.begin() + end);
		}
		void remove(T& value)override
		{
			delNode(value);
		}
		void removeAll(T& data)override
		{
			while (std::remove(dataSource.begin(), dataSource.end(), data) != dataSource.end());
		}
		void remove(initializer_list<T>& ini)override
		{
			for (auto& var : ini)
				std::remove(dataSource.begin(), dataSource.end(), var);
		}
		void remove(List& obj)
		{
			for (int n = 0; n < obj.size(); ++n)
				std::remove(dataSource.begin(), dataSource.end(), obj[n]);
		}
		void remove(vector<T>& vec)override
		{
			for (auto& var : vec)
				std::remove(dataSource.begin(), dataSource.end(), var);
		}
		void remove(list<T>& ls)override
		{
			for (auto& var : ls)
				std::remove(dataSource.begin(), dataSource.end(), var);
		}
		void remove(T* arr, int size)override
		{
			for (int n = 0; n < size; ++n)
				std::remove(dataSource.begin(), dataSource.end(), arr[n]);
		}

		T& insert(Index pos, T& value)override
		{
			newValue(pos, value);
			return dataSource[pos];
		}
		T& insert(Index pos, List& list)override
		{
			dataSource.reserve(list.size());
			for (int n = 0; n < list.size(); ++n)
				newValue(pos+n, list[n]);
			return dataSource[pos];
		}
		T& insert(Index pos, vector<T>& vec)override
		{
			dataSource.reserve(vec.size());
			dataSource.insert(dataSource.begin() + pos, vec.begin(), vec.end());
			return dataSource[pos];
		}
		T& insert(Index pos, list<T>& list)override
		{
			dataSource.reserve(list.size());
			dataSource.insert(dataSource.begin() + pos, list.begin(), list.end());
			return dataSource[pos];
		}
		T& insert(Index pos, initializer_list<T>& ini)override
		{
			dataSource.reserve(ini.size());
			dataSource.insert(dataSource.begin() + pos, ini.begin(), ini.end());
			return dataSource[pos];
		}
		T& get(Index index)override
		{
			return dataSource[index];
		}
		int indexOf(T& data)const override
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
		void clear()override
		{
			dataSource.clear();
		}
		bool equals(List& obj) const override
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
		bool equals(vector<T>& vec) const override
		{
			return dataSource == vec;
		}
		bool equals(list<T>& list)const override
		{
			return std::equal(dataSource.begin(),dataSource.end(), list.begin());
		}
		bool equals(initializer_list<T>& ini)const override
		{
			return std::equal(dataSource.begin(), dataSource.end(), ini.begin());
		}
		bool equals(T* arr, int size)const override
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
		void assign(vector<T>& vec)
		{
			dataSource = vec;
		}
		void assign(list<T>& list)
		{
			dataSource.resize(list.size());
			std::copy(list.begin(), list.end(), dataSource.begin());
		}
		void assign(initializer_list<T>& ini)
		{
			dataSource.resize(ini.size());
			std::copy(ini.begin(), ini.end(), dataSource.begin());
		}
		vector<T> toVector()const override
		{
			return dataSource;
		}
		bool contains(T& value)const override
		{
			for (auto& var : dataSource)
				if (var == value)
					return true;
			return false;
		}
		bool contains(List& obj)const override
		{
			for (int n = 0; n < obj.size(); ++n)
			{
				for (auto& var : dataSource)
					if (var != obj[n])
						return false;
			}
			return true;
		}
		bool contains(vector<T>& vec)const override
		{
			for (int n = 0; n < vec.size(); ++n)
			{
				for (auto& var : dataSource)
					if (var != vec[n])
						return false;
			}
			return true;
		}
		bool contains(list<T>& list)const override
		{
			for (auto& var2: list)
			{
				for (auto& var : dataSource)
					if (var != var2)
						return false;
			}
			return true;
		}
		bool contains(initializer_list<T>& ini)const override
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
		* void sort(void(*sortFunc)(List& _this) = NULL)override 
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
		void subList(List& destination,Index start, Index end) override
		{
			for (int n = start; n <= end; ++n)
				destination.add(dataSource[n]);
		}
		void copyFrom(List& obj) override
		{
			if (obj.size() > size())
				dataSource.resize(obj.size());
			else
				dataSource.resize(obj.size());
			for (int n = 0; n < dataSource.capacity(); ++n)
				dataSource[n] = obj[n];
		}
		void copyTo(List& obj) override
		{
			obj.resize(size());
			for (int n = 0; n < size(); ++n)
				obj[n] = dataSource[n];
		}
		void set(Index pos, T& value)override
		{
			dataSource[pos] = value;
		}
		void swap(Index pos1, Index pos2)override
		{
			std::swap(dataSource[pos1], dataSource[pos2]);
		}
		void reverse()override
		{
			std::reverse(dataSource.begin(), dataSource.end());
		}
		void resize(Index newSize)override
		{
			dataSource.resize(newSize);
		}
	};
}
#endif
