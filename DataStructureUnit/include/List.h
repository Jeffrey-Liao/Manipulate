#ifndef LIST_H
#define LIST_H
#include"common.h"
#include"Exceptions.h"
using std::list;
using std::vector;
using std::initializer_list;
using std::array;
namespace liaoUtil
{
	using namespace liaoInfor;
	using Index = size_t;
	DYNAMIC
	class List
	{
	protected:
		//基础构造函数，什么都不做
		explicit constexpr List()
		{}
		/*
		* 基于初始大小的构造函数
		* 调用各实际容器实现的allocate以分配初始大小的内存
		*/
		explicit constexpr List(size_t _size)
		{
			allocate(_size);
		}
		/*
		* 拷贝构造函数
		* 调用各实际容器实现的copyFrom实现拷贝操作
		*/
		explicit constexpr List(const List& obj)
		{
			copyFrom(obj);
		}
	protected:
		constexpr void emptyListCheck(const char* functionName)const
		{
			if (isEmpty())
				throw new EmptyContainerException(classID(), functionName);
		}
		constexpr void outRangeCheck(Index index, const char* functionName)const
		{
			if (!validPos(index))
				throw new OutOfRangeException(classID(), functionName);
		}
		constexpr void validIntervalCheck(Index start, Index end, const char* functionName)const
		{
			if (start > end)
				throw new InvalidOperationException(classID(), functionName, "Given interval is invalid because start index is bigger than end index");
			outRangeCheck(start,functionName);
			outRangeCheck(end,functionName);
		}
		using vector = std::vector<T>;
		using list = std::list<T>;
		using initializer_list = std::initializer_list<T>;
		/*
		* 容器自定义的分配方法
		* 可以指导基类基于初始值初始化的构造方法
		*/
		virtual void allocate(const size_t _size) = 0;
		/*
		* 根据给定值引用创建一个新元素
		*/
		virtual void newValue(const T& value) = 0;
		/*
		* 根据给定值引用和给定位置创建一个新元素
		*/
		//virtual void newValue(Index pos, const T& value) = 0;
		/*
		* 根据给定列表引用创建一个新元素
		*/
		//virtual void newValue(List& obj) = 0;
		/*
		* 根据给定位置删除一个已有元素
		* （如果没有该元素将会抛出InvalidOperationException）
		*/
		//virtual void delNode(const T& value) = 0;
		/*
		* 根据给定位置删除一个已有元素
		* （如果没有该元素将会抛出InvalidOperationException）
		*/
		//virtual void delNode(Index pos) = 0;
		/*
		* 判断当前索引是否访问超限
		*/
		virtual bool validPos(Index pos) const = 0;
		/*
		* 清空当前容器
		*/
		virtual void free() = 0;
		template<class Container>
		/*
		* 拷贝其他std容器内的值到当前容器
		* （尤其适用于非std内核实现的容器）
		*/
		void StdToStd(const Container& obj)
		{
			for (auto& var : obj)
				newValue(var);
		}
	public:
		//当前classID
		virtual string classID() const
		{
			return "List";
		}
		//当前容器大小
		virtual size_t size() const = 0;
		//当前容器是否为空
		virtual bool isEmpty()const = 0;
		//获取当前容器的第一个元素的引用
		virtual const T& first() const = 0;
		//获取当前容器最后一个元素的引用
		virtual const T& last() const = 0;
		//获取当前容器的第一个元素的引用
		virtual T& first() = 0;
		//获取当前容器最后一个元素的引用
		virtual T& last()= 0;

		//根据给定的右值新增一个元素，返回新元素的引用
		virtual T& add(T&& value) = 0;
		//根据给定的左值新增一个元素，返回新元素的引用
		virtual T& add(const T& value) = 0;
		//根据给定的List抽象对象新增多个元素，返回第一个新元素的引用
		virtual T& add(const List& obj) = 0;
		//基于给定的右值填充number个新元素，返回第一个新元素的引用
		virtual T& add(const int number, T&& value) = 0;
		//基于给定的左值填充number个新元素，返回第一个新元素的引用
		virtual T& add(const int number,const  T& value) = 0;
		//添加vector内的全部元素到当前列表，返回第一个新元素的引用
		virtual T& add(const vector& vec) = 0;
		//添加list内的全部元素到当前列表，返回第一个新元素的引用
		virtual T& add(const list& list) = 0;
		//添加initializer内的全部元素到当前列表，返回第一个新元素的引用
		virtual T& add(const initializer_list& ini) = 0;
		//添加数组内的全部元素到当前列表，返回第一个新元素的引用（该函数默认给定的size是合法的）
		virtual T& add(const T* arr, const int size) = 0;
		//User promise the given container had operator[] and size function to take size of container.
		template<class Container>
		T& add(const Container& obj)
		{
			T* result = NULL;
			for (int n = 0; n < obj.size(); ++n)
			{
				if (n == 0)
					result = this->add(obj[n]);
				else
					this->add(obj[n]);
			}
			return *result;
		}
		//移除指定位置的元素
		virtual void remove(const Index pos) = 0;
		//移除指定区间的元素
		virtual void remove(const Index start, const Index end) = 0;
		//移除第一个指定的元素
		virtual void remove(const T& data) = 0;
		//移除第一个指定的元素
		virtual void remove(T&& data) = 0;
		//移除所有指定的元素
		virtual void removeAll(const T& data) = 0;
		//移除第一个存在于initializer中的元素
		virtual void remove(const initializer_list& ini) = 0;
		//移除第一个存在于List中的元素
		virtual void remove(const List& obj) = 0;
		//移除第一个存在于vector中的元素
		virtual void remove(const vector& vec) = 0;
		//移除第一个存在于list中的元素
		virtual void remove(const	list& ls) = 0;
		//移除第一个存在于数组中的元素
		virtual void remove(const T* arr, const int size) = 0;

		//在指定位置插入一个元素
		virtual T& insert(const Index pos, T&& value) = 0;
		//在指定位置插入一个元素
		virtual T& insert(const Index pos, const T& value) = 0;
		//在指定位置插入一个List
		virtual T& insert(const Index pos, const List& list) = 0;
		//在指定位置插入一个vector
		virtual T& insert(const Index pos,const vector& vec) = 0;
		//在指定位置插入一个list
		virtual T& insert(const Index pos, const list& list) = 0;
		//在指定位置插入一个initializer
		virtual T& insert(const Index pos, const initializer_list& ini) = 0;

		//获取指定位置的元素引用
		virtual T& get(const Index index) = 0;
		virtual const T& get(const Index index) const = 0;
		//获取指定元素的索引
		virtual size_t indexOf(const T& data) const = 0;
		//清空容器
		virtual void clear() = 0;

		//比较容器
		virtual bool equals(const List& obj) const = 0;
		//比较容器
		virtual bool equals(const vector& vec) const = 0;
		//比较容器
		virtual bool equals(const list& list)const = 0;
		//比较容器
		virtual bool equals(const initializer_list& ini)const = 0;
		//比较容器
		virtual bool equals(const T* arr, const  int size)const = 0;

		//将当前数组转为[value1,value2,...]格式的字符串，如果为空则为[]
		string toString()
		{
			if (size() > 0)
			{
				string temp = "[";
				for (int n = 0; n < this->size(); ++n)
				{
					temp += std::to_string(get(n));
					temp += ',';
				}
				temp[temp.size() - 1] = ']';
				return temp;
			}
			else
				return "[]";
		}
		//将当前的容器转化为vector类型
		virtual vector toVector() const = 0;

		//检查当前容器是否包含指定的值
		virtual bool contains(const T&& value)const = 0;
		//检查当前容器是否包含指定的值
		virtual bool contains(const T& value)const = 0;
		//检查当前容器是否包含指定List内的全部元素
		virtual bool contains(const List& obj)const = 0;
		//检查当前容器是否包含指定vector内的全部元素
		virtual bool contains(const vector& vec)const = 0;
		//检查当前容器是否包含指定list内的全部元素
		virtual bool contains(const list& list)const = 0;
		//检查当前容器是否包含指定initializer内的全部元素
		virtual bool contains(const initializer_list& ini)const = 0;

		//将vector覆写到当前容器
		virtual void assign(const vector& vec) = 0;
		//将list覆写到当前容器
		virtual void assign(const list& list) = 0;
		//将initializer覆写到当前容器
		virtual void assign(const initializer_list& ini) = 0;
		virtual void sort(void(*sortFunc)(List& _this) = NULL) = 0;
		virtual void apply(void(*operation)(T& value)) = 0;
		virtual size_t count(const T& data)const = 0;

		virtual void subList(List& destination,const Index start,const Index end) = 0;
		virtual void copyFrom(const List& obj) = 0;
		virtual void copyTo(List& obj) = 0;
		virtual void set(const Index pos,const T& value) = 0;
		virtual void swap(const Index pos1, const  Index pos2) = 0;
		virtual void reverse() = 0;

		virtual void resize(const Index newSize) = 0;
		T& operator[](const Index index)
		{
			return this->get(index);
		}
		T& operator[](const Index index) const
		{
			return this->get(index);
		}
		void operator()(List& target, const Index start, const  Index end)
		{
			this->subList(target, start, end);
		}
		T& operator+(const T& data)
		{
			return this->add(data);
		}
		void operator-(const T& data)
		{
			this->remove(data);
		}
		bool operator==(const List& obj)
		{
			return this->equals(obj);
		}
		void operator=(const size_t size)
		{
			resize(size);
		}
		void operator=(const List& obj)
		{
			copyFrom(obj);
		}
		void operator=(const initializer_list& ini)
		{
			assign(ini);
		}
		void operator=(const list& ls)
		{
			assign(ls);
		}
		void operator=(const vector vec)
		{
			assign(vec);
		}
		virtual ~List()
		{
		}
	};
}

#endif