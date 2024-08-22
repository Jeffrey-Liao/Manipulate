#ifndef NODE_H
#define NODE_H
#include"common.h"
#include"LiaoException.h"
#include"InvalidOperationException.h"
namespace liaoUtil
{
	DYNAMIC
		class Node
	{
		TYPE data;
	protected:
		Node()
			:data{}
		{ }
		Node(const T& newData) : data(newData)
		{}
		Node(const Node& Obj)
		{
			this->data = Obj.data;
		}
	public:
		virtual string classID() const
		{
			return "Node";
		}
		void assign(Node& data)
		{
			this->data = data.value();
		}
		void assign(const T data)
		{
			this->data = data;
		}
		void assignRef(const T& data)
		{
			this->data = data;
		}
		TYPE& value()
		{
			return data;
		}
		const TYPE& value() const 
		{
			return data;
		}
		constexpr bool compare(Node& data)const
		{
			return this->data == data.value();
		}
		constexpr bool compare(T& data)const
		{
			return this->data == data;
		}
		void swap(Node& obj)
		{
			TYPE tempData = obj.data;
			obj.data = this->data;
			this->data = tempData;
		}
		void cloneTo(Node& obj)const
		{
			obj.data = data;
		}
		bool operator>(Node& obj)
		{
			return data > obj.value();
		}
		bool operator<(Node& obj)
		{
			return data <  obj.value();
		}
		bool operator>=(Node& obj)
		{
			return data >= obj.value();
		}
		bool operator<=(Node& obj)
		{
			return data <= obj.value();
		}
		bool operator==(Node& obj)
		{
			return data == obj.value();
		}
		T& operator=(Node& obj)
		{
			assign(obj);
			return value();
		}
	};
}
#endif