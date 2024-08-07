#ifndef SET_H
#define SET_H
#include"List.h"
#include <set>
namespace liaoUtil
{
	using std::set;
	DYNAMIC
	/*
	*Set内的所有元素都不可以被修改
	引用返回值是基于List基类的实现
	实际上修改的是临时数据字段，对Set内的元素没有任何影响
	*/
	class Set:public List<T>
	{
		using List = List<T>;
		set<T> dataSource;
		T value;
	private:
		void allocate(int size)
		{
			//无法对set执行allocate操作;
		}
		void newValue(const T& value) override
		{
			dataSource.insert(value);
		}
		template<class Container>
		void StdToSet(Container& obj)
		{
			for (auto& val : obj)
				dataSource.insert(val);
		}
		set<T>::iterator iterate(int pos)
		{
			auto itor = dataSource.begin();
			int end = 0;
			bool dir = false;
			if ((dir = pos > dataSource.size() / 2) )
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
			return itor;
		}
		bool validPos(Index index)const override
		{
			return index < dataSource.size();
		}
		void free()override
		{
			dataSource.clear();
		}

		//不执行操作，默认返回第一个元素
		__declspec(deprecated("Please use add if you want to make a new element into a set.")) 
		T& insert(Index pos, T&& value)
		{
			return value;
		}
		//不执行操作，默认返回第一个元素
		T& insert(Index pos, T& value)
		{
			return value;
		}
		//不执行操作，默认返回第一个元素
		T& insert(Index pos, List& list)
		{
			return value;
		}
		//不执行操作，默认返回第一个元素
		T& insert(Index pos, vector<T>& vec)
		{
			return value;
		}
		//不执行操作，默认返回第一个元素
		T& insert(Index pos, list<T>& list)
		{
			return value;
		}
		//不执行操作，默认返回第一个元素
		T& insert(Index pos, initializer_list<T>& ini)
		{
			return value;
		}
		//不执行任何操作，因为set已经是排序好的了
		__declspec(deprecated("There is no need to sort a set.")) 
		void sort(void(*sortFunc)(List& _this) = NULL)
		{

		}
		//不会执行任何操作，因为set已经是有序的了
		__declspec(deprecated("You cannot swap data inside a set.")) 
			void swap(Index pos1, Index pos2)
		{

		}
		//不会执行任何操作，因为set已经是有序的了
		__declspec(deprecated("You cannot reverse this set"))
		virtual void reverse()
		{

		}
		//不会执行任何操作
		__declspec(deprecated("You cannot resize a set"))
		void resize(Index newSize)
		{
			allocate(newSize);
		}
	public:
		Set()
			:List(), value{}
		{}
		Set(size_t size)
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
		Set(set<T>& obj)
		{
			dataSource = obj;
		}
	public:
		string classID() const override
		{
			return "Set";
		}
		size_t size() const override
		{
			return dataSource.size();
		}
		bool isEmpty()
		{

			return dataSource.empty();
		}
		const T& first()
		{
			this->emptyListCheck("first()");
			value = *dataSource.begin();
			return value;
		}
		const T& last()
		{
			this->emptyListCheck("last()");
			value = *(--dataSource.end());
			return value;
		}
		T& add(const T&& value)
		{
			this->value = *dataSource.insert(value).first;
			return this->value;
		}
		T& add(const T& value)
		{
			this->value = *dataSource.insert(value).first;
			return this->value;
		}
		T& add(List& obj)
		{
			for (int n = 0; n < obj.size(); ++n)
			{
				dataSource.insert(obj[n]);
			}
			return value = obj[0];
		}
		//基于给定的右值填充number个新元素，返回第一个新元素的引用
		T& add(int number, T&& value)
		{
			for (int n = 0; n < number; ++n)
			{
				dataSource.insert(value);
			}
			return this->value = value;
		}
		//基于给定的左值填充number个新元素，返回第一个新元素的引用
		T& add(int number, T& value)
		{
			for (int n = 0; n < number; ++n)
			{
				dataSource.insert(value);
			}
			return this->value = value;
		}
		//添加vector内的全部元素到当前列表，返回第一个新元素的引用
		T& add(vector<T>& vec)
		{
			StdToSet(vec);
			return value= vec[0];
		}
		//添加list内的全部元素到当前列表，返回第一个新元素的引用
		T& add(list<T>& list)
		{
			StdToSet(list);
			return value= *list.begin();
		}
		//添加initializer内的全部元素到当前列表，返回第一个新元素的引用
		T& add(initializer_list<T>& ini)
		{
			StdToSet(ini);
			return value= *ini.begin();
		}
		//添加数组内的全部元素到当前列表，返回第一个新元素的引用（该函数默认给定的size是合法的）
		 T& add(T* arr, int size)
		{
			for (int n = 0; n < size; ++n)
			{
				dataSource.insert(arr[n]);
			}
			return value = arr[0];
		}
		 //移除指定位置的元素
		 void remove(Index pos)
		 {
			 this->emptyListCheck("remove(Index)");
			 this->outRangeCheck(pos, "remove(Index)");
			 dataSource.erase(iterate(pos));
		 }
		 //移除指定区间的元素
		 void remove(Index start, Index end)
		 {
			 this->emptyListCheck("remove(Index,Index)");
			 this->validIntervalCheck(start, end,"remove(Index,Index)");
			 dataSource.erase(iterate(start), iterate(end));
		 }
		 //移除第一个指定的元素
		void remove(T& data)
		 {
			this->emptyListCheck("remove(T&)");
			dataSource.erase(data);
		 }
		 //移除第一个指定的元素
		void remove(T&& data)
		{
			this->emptyListCheck("remove(T&&)");
			dataSource.erase(data);
		 }
		 //移除所有指定的元素
		void removeAll(T& data)
		{
			this->emptyListCheck("removeAll(T&)");
			dataSource.erase(data);
		 }
		 //移除第一个存在于initializer中的元素
		void remove(initializer_list<T>& ini)
		{
			this->emptyListCheck("remove(initializer_list<T>&)");
			for (auto& val : ini)
				dataSource.erase(val);
		 }
		 //移除第一个存在于List中的元素
		void remove(List& obj)
		{
			this->emptyListCheck("remove(List&)");
			for (int n = 0; n < obj.size(); ++n)
				dataSource.erase(obj[n]);
		 }
		 //移除第一个存在于vector中的元素
		void remove(vector<T>& vec)
		{
			this->emptyListCheck("remove(vector<T>&)");
			for (auto& val : vec)
				dataSource.erase(val);
		 }
		 //移除第一个存在于list中的元素
		void remove(list<T>& ls)
		{
			this->emptyListCheck("remove(list<T>&)");
			for (auto& val : ls)
				dataSource.erase(val);
		 }
		 //移除第一个存在于数组中的元素
		void remove(T* arr, int size)
		{
			this->emptyListCheck("remove(T*,int)");
			for (int n = 0; n < size; ++n)
				dataSource.erase(arr[n]);
		 }
		
		//获取指定位置的元素引用
		T& get(Index index)
		{
			this->emptyListCheck("get(int)");
			this->outRangeCheck(index, "get(int)");
			return value =*iterate(index);
		}
		size_t indexOf(T& data)const override
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
		//清空容器
		void clear()
		{
			dataSource.clear();
		}
		//比较容器
		bool equals(List& obj) const
		{
			if (dataSource.size() != obj.size())
				return false;
			else
			{
				int n = 0;
				for (auto& var : dataSource)
				{
					if (var != obj[n])
						return false;
					n++;
				}
				return true;
			}
		}
		//比较容器
		bool equals(vector<T>& vec) const
		{
			if (vec.size() != dataSource.size())
				return false;
			return std::equal(vec.begin(), vec.end(), dataSource.begin());
		}
		//比较容器
		bool equals(list<T>& list)const
		{
			if (list.size() != dataSource.size())
				return false;
			return std::equal(list.begin(), list.end(), dataSource.begin());
		}
		//比较容器
		bool equals(initializer_list<T>& ini)const
		{
			if (ini.size() != dataSource.size())
				return false;
			return std::equal(ini.begin(), ini.end(), dataSource.begin());
		}
		//比较容器
		bool equals(T* arr, int size)const
		{
			if (dataSource.size() != size)
				return false;
			int n = 0;
			for (auto& val : dataSource)
			{
				if (arr[n] != val)
					return false;
				++n;
			}
			return true;
		}
		vector<T> toVector() const
		{
			vector<T> result;
			for (auto& val : dataSource)
				result.push_back(val);
			return result;
		}
		bool isEmpty()const override
		{
			return dataSource.empty();
		}
		//检查当前容器是否包含指定的值
		bool contains(T&& value)const
		{
			return dataSource.contains(value);
		}
		//检查当前容器是否包含指定的值
		bool contains(T& value)const
		{
			return dataSource.contains(value);
		}
		//检查当前容器是否包含指定List内的全部元素
		bool contains(List& obj)const
		{
			for (int n = 0; n < obj.size(); ++n)
			{
				if (!dataSource.contains(obj[n]))
					return false;
			}
			return true;
		}
		//检查当前容器是否包含指定vector内的全部元素
		bool contains(vector<T>& vec)const
		{
			for (auto& val : vec)
			{
				if (!dataSource.contains(val))
					return false;
			}
			return true;
		}
		//检查当前容器是否包含指定list内的全部元素
		bool contains(list<T>& list)const
		{
			for (auto& val : list)
			{
				if (!dataSource.contains(val))
					return false;
			}
			return true;
		}
		//检查当前容器是否包含指定initializer内的全部元素
		bool contains(initializer_list<T>& ini)const
		{
			for (auto& val : ini)
			{
				if (!dataSource.contains(val))
					return false;
			}
			return true;
		}
		//将vector覆写到当前容器
		void assign(vector<T>& vec)
		{
			dataSource.clear();
			for (auto& val : vec)
				dataSource.insert(val);
		}
		//将list覆写到当前容器
		void assign(list<T>& list) 
		{
			dataSource.clear();
			for (auto& val : list)
				dataSource.insert(val);
		}
		//将initializer覆写到当前容器
		void assign(initializer_list<T>& ini)
		{
			dataSource.clear();
			for (auto& val : ini)
				dataSource.insert(val);
		}

		//将set内被选中的已有的元素删除，操作后重新插入
		virtual void apply(void(*operation)(T& value))
		{
			for (auto& val : dataSource)
			{
				value = val;
				dataSource.erase(value);
				operation(value);
				dataSource.insert(value);
			}
		}
		size_t count(T& data)const
		{
			return dataSource.count(data);
		}
		void subList(List& destination, Index start, Index end)
		{
			this->emptyListCheck("subList(List&,Index,Index)");
			this->validIntervalCheck(start, end, "subList(List&,Index,Index)");
			auto itor = iterate(start);
			for (int n = start; n < end; ++n, itor++)
				destination.add(*itor);
		}
		void copyFrom(List& obj)
		{
			dataSource.clear();
			for (int n = 0; n < obj.size(); ++n)
				dataSource.insert(obj[n]);
		}
		void copyTo(List& obj)
		{
			obj.resize(dataSource.size());
			int n = 0;
			for (auto& var : dataSource)
			{
				obj[n] = var;
				n++;
			}
		}
		void set(Index pos, T& value)
		{
			this->emptyListCheck("set(Index,T&)");
			dataSource.erase(iterate(pos));
			dataSource.insert(value);
		}
		~Set()
		{
			dataSource.clear();
		}

	};
}

#endif