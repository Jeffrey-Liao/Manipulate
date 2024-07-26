#ifndef LIST_H
#define LIST_H
#include "ListNode.h"
using std::list;
using std::vector;
using std::initializer_list;
using std::array;
namespace liaoUtil
{
	using namespace liaoInfor;
	using Index = unsigned int;
	DYNAMIC
	class List
	{
	public:
		List()
		{}
		List(int _size)
		{
			allocate(_size);
		}
		List(List& obj)
		{
			copyFrom(obj);
		}
	protected:
		using vector = std::vector<T>;
		using list = std::list<T>;
		using initializer_list = std::initializer_list<T>;
		virtual void allocate(int _size) = 0;

		virtual void newValue(const T& value) = 0;
		virtual void newValue(Index pos, const T& value) = 0;
		virtual void newValue(List& obj) = 0;

		virtual void delNode(const T& value) = 0;
		virtual void delNode(Index pos) = 0;

		virtual bool validPos(Index pos) const = 0;
		virtual void free() = 0;
		template<class Container>
		void stdCopy(Container& obj)
		{
			for (auto& var : obj)
			{
				newValue(var);
			}
		}
	public:
		virtual string classID() const
		{
			return "List";
		}
		virtual int size() const = 0;
		virtual bool isEmpty()const = 0;
		virtual T& first()= 0;
		virtual T& last()= 0;

		virtual T& add(T& data) = 0;
		virtual T& add(List& obj) = 0;
		virtual T& add(int number, T& value) = 0;
		virtual T& add(vector& vec) = 0;
		virtual T& add(list& list) = 0;
		virtual T& add(initializer_list& ini) = 0;
		virtual T& add(T* arr, int size) = 0;

		virtual void remove(Index pos) = 0;
		virtual void remove(Index start,Index end) = 0;
		virtual void remove(T& data) = 0;
		virtual void removeAll(T& data) = 0;
		virtual void remove(initializer_list& ini) = 0;
		virtual void remove(List& obj) = 0;
		virtual void remove(vector& vec) = 0;
		virtual void remove(list& ls) = 0;
		virtual void remove(T* arr, int size) = 0;

		virtual T& insert(Index pos, T& value) = 0;
		virtual T& insert(Index pos, List& list) = 0;
		virtual T& insert(Index pos, vector& vec) = 0;
		virtual T& insert(Index pos, list& list) = 0;
		virtual T& insert(Index pos, initializer_list& ini) = 0;

		virtual T& get(Index index) = 0;
		virtual int indexOf(T& data) const = 0;
		virtual void clear() = 0;

		virtual bool equals(List& obj) const = 0;
		virtual bool equals(vector& vec) const = 0;
		virtual bool equals(list& list)const = 0;
		virtual bool equals(initializer_list& ini)const = 0;
		virtual bool equals(T* arr, int size)const = 0;

		string toString()
		{
			string temp = "[";
			for (int n =0;n<this->size();++n)
			{
				temp += std::to_string(get(n));
				temp += ',';
			}
			temp[temp.size() - 1] = ']';
			return temp;
		}
		virtual vector toVector() const = 0;

		virtual bool contains(T& value)const = 0;
		virtual bool contains(List& obj)const = 0;
		virtual bool contains(vector& vec)const = 0;
		virtual bool contains(list& list)const = 0;
		virtual bool contains(initializer_list& ini)const = 0;

		//virtual void sort(void(*sortFunc)(List& _this) = NULL) = 0;
		virtual void apply(void(*operation)(T& value)) = 0;
		virtual int count(T& data)const = 0;

		virtual void subList(List& destination, Index start, Index end) = 0;
		virtual void copyFrom(List& obj) = 0;
		virtual void copyTo(List& obj) = 0;
		virtual void set(Index pos, T& value) = 0;
		virtual void swap(Index pos1, Index pos2) = 0;
		virtual void reverse() = 0;

		virtual void resize(Index newSize) = 0;
		T& operator[](int index)
		{
			return this->get(index);
		}
		void operator()(List& target, int start, int end)
		{
			this->subList(target, start, end);
		}
		T& operator+(T& data)
		{
			return this->add(data);
		}
		void operator-(T& data)
		{
			this->remove(data);
		}
		bool operator==(List& obj)
		{
			return this->equals(obj);
		}
		void operator=(int size)
		{
			resize(size);
		}
		void operator=(List& obj)
		{
			copyFrom(obj);
		}
	};
}

#endif