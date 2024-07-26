#ifndef ARRAYNODE_H
#define ARRAYNODE_H
#include "ListNode.h"
namespace liaoUtil
{
	using std::vector;
	using liaoInfor::InvalidOperationException;
	DYNAMIC
	class ArrayNode :public ListNode<T>
	{
		using ListNode = ListNode<T>;
		using vector = std::vector<T>;
		T pos;
		vector& dataSource;
	public:
		ArrayNode(vector& dataSource)
			:ListNode(),dataSource(dataSource)
		{}
		ArrayNode(ArrayNode& obj)
			:ListNode(obj),pos(obj.pos),dataSource(obj.dataSource)
		{}
		string classID() const override
		{
			return "ArrayNode";
		}
		ArrayNode& next() override
		{
			if(pos < dataSource.size())
				pos++;
			return *this;
		}
		ArrayNode& prev()override
		{
			if (pos >0)
				pos--;
			return *this;
		}
		ArrayNode& root()override
		{
			pos = 0;
			return *this;
		}
		ArrayNode& last()override
		{
			pos = dataSource.size()-1;
			return *this;
		}
		void set(T pos)
		{
			this->pos = pos;
		}
		size_t get()
		{
			return pos;
		}
		ArrayNode& link(const T& value)override
		{
			dataSource.insert(dataSource.begin() + pos + 1, value);
			pos++;
			return *this;
		}
		void unlink(bool keep = false) override
		{
			dataSource.erase(dataSource.begin()+pos+1);
		}
		bool isRoot()const override
		{
			return pos == 0;
		}
		bool isLast() const override
		{
			return pos == dataSource.size();
		}
		T& value()override
		{
			return dataSource[pos];
		}
		bool isEmpty()const override
		{
			return pos == 0 || pos == dataSource.size();
		}
		void cut()override
		{
			dataSource.erase(dataSource.begin()+pos + 1, dataSource.end());
		}
		void setNextNull()override
		{
			;
		}
		bool isNext(ListNode& obj) const override
		{
			return false;
		}
		bool isPrev(ListNode& obj)const override
		{
			return false;
		}
	};
}

#endif