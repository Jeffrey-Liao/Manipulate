#pragma once
#include "../debugInfor.h"
#include "JMacros.h"
#ifndef JNODE_H
#define JNODE_H
#define ASLINKNODE *(LinkNode*)
#define ASDOUBLENODE *(DoubleLinkNode*)
#define ASNODE *(Node*)
#define JNULL ZERO.Export()
namespace jeff
{
	DYNAMIC
	class NodeOper
	{
	public:
		virtual bool compare(const T) = 0;
		virtual bool greater(const T) = 0;
		virtual bool less(const T) = 0;
		virtual T assign(const T) = 0;
		virtual T& get() = 0;
		virtual T operator =(const T Obj) = 0;
		virtual bool operator ==(const T Obj) = 0;
		virtual bool operator>(const T Obj) = 0;
		virtual bool operator< (const T Obj) = 0;
		T& notfound()
		{
			return ASTYPE ZERO(sizeof(T)).Export();
		}
	};
	DYNAMIC
	class LinkNodeOper
	{
	public:
		virtual T& getNext() = 0;
		virtual const T& link(T&) = 0;
		virtual void unlink() = 0;
		virtual bool last() = 0;
		T& getNode(int distance)
		{
			T* temp = this;
			for (int n = 0; n < distance && temp != NULL; ++n)
				temp = temp->next;
			if (temp)
				return temp;
			else
			{
				throw new LiaoException("LinkNode","getNode" , " method index overflow");
				return ASTYPE ZERO(sizeof(T)).Export();
			}

		}
		virtual int distance(T&) = 0;
		void operator+(T& Obj)
		{
			this->link(Obj);
		}
		T& notfound()
		{
			return ASTYPE ZERO(sizeof(T)).Export();
		}
	};
	DYNAMIC
	class DoubleLinkNodeOper :public LinkNodeOper<T>
	{
	public:
		virtual bool first() = 0;
		virtual const T& getPrev() = 0;
		virtual void swap(T&) = 0;
		virtual const T& link(T&) = 0;
		virtual bool unique() = 0;
	};
	template <class T>
	class Node:public NodeOper<T>
	{
	protected:
		T data;
	public:
		Node(){data = ASTYPE ZERO(sizeof(T)).Export();}
		Node(const T& newData) : data(newData)
		{}
		Node(const Node& Obj)
		{
			this->data = Obj.data;
		}
		bool compare(const T existData)
		{
			return data == existData;
		}
		bool compare(const Node& existNode)
		{
			return this->compare(existNode.data);
		}
		bool greater(const T existData)
		{
			return this->data > existData;
		}
		bool greater(const Node& existNode)
		{
			return this->greater(existNode.data);
		}
		T assign(const T newData)
		{
			return this->data = newData;
		}
		T assign(const Node& newNode)
		{
			this->data = newNode.data;
			return this->data;
		}
		T& get()
		{
			return this->data;
		}
		bool less(const T existData)
		{
			return this->data < existData;
		}
		bool less(const Node& existNode)
		{
			return this->less(existNode.data);
		}
		T operator = (const T Obj)
		{
			return this->assign(Obj);
		}
		T operator =(const Node& Obj)
		{
			return this->assign(Obj);
		}
		bool operator ==(const T Obj)
		{
			return this->compare(Obj);
		}
		bool operator ==(const Node& Obj)
		{
			return this->compare(Obj);
		}
		bool operator>(const T Obj)
		{
			return this->greater(Obj);
		}
		bool operator>(const Node& Obj)
		{
			return this->greater(Obj);
		}
		bool operator< (const T Obj)
		{
			return this->less(Obj);
		}
		bool operator< (const Node& Obj)
		{
			return this->less(Obj);
		}
	};
	DYNAMIC
	class LinkNode:public Node<T> ,public LinkNodeOper<LinkNode<T>>
	{
		LinkNode* next;
	public:
		LinkNode() :next(NULL)
		{}
		//with Default Number
		LinkNode(const T newData) : next(NULL), Node<T>(newData)
		{}
		//with father Node
		LinkNode(LinkNode* father) : next(NULL), Node<T>()
		{
			if (father != NULL)
				father->next = this;
		}
		LinkNode(LinkNode* father, const T newData) :next(NULL)
		{
			if (father != NULL)
				father->next = this;
			this->data = newData;
		}
		LinkNode(LinkNode* father, LinkNode* Son, const T newData) :next(Son), Node<T>(newData)
		{
			if (father != NULL)
				father->next = this;
		}
		//Assign Function
		 LinkNode(const LinkNode& existNode) 
			:Node<T>(existNode.data), next(existNode.next)
		{}
		LinkNode& link(LinkNode& newNext)
		{
			if(this->next == NULL)
				this->next = &newNext;
			else
			{
				newNext.next = this->next;
				this->next = &newNext;
			}
			return *this;
		}
		
		void unlink()
		{
			LinkNode* temp = next->next;
			delete this->next;
			this->next = temp;
		}
		void swap(LinkNode& existNode)
		{
			auto temp = this->data;
			this->data = existNode.data;
			existNode.data = temp;
		}
		LinkNode& notfound()
		{
			return *(LinkNode*) ZERO(sizeof(LinkNode)).Export();
		}
		LinkNode& getNext()
		{
			if (this->next)
				return *this->next;
			else
				return notfound();
		}
		bool last()
		{
			return this->next == NULL;
		}
		int distance(LinkNode& Pos)
		{
			int result = 0;
			for (int n = 0; this->next != NULL; ++n)
			{
				if (this == &Pos)
				{
					result = n;
					break;
				}
			}
			return result;
		}
		LinkNode& operator=(LinkNode& Obj)
		{
			this->data = Obj.data;
			return *this;
		}
	};
	DYNAMIC
	class DoubleLinkNode :public Node<T>, public DoubleLinkNodeOper<DoubleLinkNode<T>>
	{
		DoubleLinkNode* prev;
		DoubleLinkNode* next;
	public:
		DoubleLinkNode()
			:prev(NULL),next(NULL)
		{}
		//with Default Number
		DoubleLinkNode(const T newData) : prev(NULL),next(NULL), Node<T>(newData)
		{}
		//with father Node
		DoubleLinkNode(DoubleLinkNode* father) : prev(father),next(NULL), Node<T>()
		{
			if (father != NULL)
				father->next = this;
		}
		DoubleLinkNode(DoubleLinkNode* father, const T newData):prev(father),next(NULL)
		{
			if (father != NULL)
				father->next = this;
			this->data = newData;
		}
		DoubleLinkNode(DoubleLinkNode* father, DoubleLinkNode* Son, const T newData) :prev(father),next(Son), Node<T>(newData)
		{
			if (father != NULL)
				father->next = this;
			if (Son != NULL)
				Son->prev = this;
		}
		//Assign Function
		DoubleLinkNode(const DoubleLinkNode& existNode)
			:Node<T>(existNode.data), prev(existNode.prev), next(existNode.next)
		{}
		DoubleLinkNode& getPrev()
		{
			return *this->prev;
		}
		DoubleLinkNode& getNext()
		{
			return *this->next;
		}
		const DoubleLinkNode& link(DoubleLinkNode& newNode)
		{
			if (this->next)
			{
				this->next->prev = &newNode;
				newNode.next = this->next;
			}
			newNode.prev = this;
			this->next = &newNode;
			return *this->next;
		}
		void unlink()
		{
			if (this->next)
			{
				DoubleLinkNode* temp = this->next->next;
				delete this->next;
				this->next = temp;
				if (temp)
					temp->prev = this;
			}
		}
		bool first()
		{
			return this->prev == NULL;
		}
		bool last()
		{
			return this->next == NULL;
		}
		void swap(DoubleLinkNode& existNode)
		{
			auto temp = this->data;
			this->data = existNode.data;
			existNode.data = temp;
		}
		void insertSwap(DoubleLinkNode& existNode)
		{
			DoubleLinkNode* tempNext = this->next,*tempPrev = existNode.prev;
			this->next  = &existNode;
			existNode.prev = this;
			if (tempPrev && existNode.next)
			{
				tempPrev->next = existNode.next;
				existNode.next->prev = tempPrev;
			}
			if(tempNext && existNode.next)
			{
				tempNext->prev = existNode;
				existNode.next = tempNext;
			}
		}
		int distance(DoubleLinkNode& existNode)
		{
			DoubleLinkNode* temp = this;
			for (int n = 0; temp != NULL; ++n)
			{
				if (temp != &existNode)
					return n;
				temp = temp->next;
			}
			return -1;
		}
		bool unique()
		{
			return this->prev == NULL && this->next == NULL;
		}
		~DoubleLinkNode()
		{
			if (this->prev)
				this->prev->next = this->next;
			if (this->next)
				this->next->prev = this->prev;
		}
	};
	DYNAMIC
	void nodeSwap(T& node1, T& node2)
	{
		auto temp = node1.get();
		node1 = node2;
		node2.assign(temp);
	}
	DYNAMIC
	class TreeNodeOper:public Node<T>
	{
		TreeNodeOper* prev;
		TreeNodeOper* left, * right;
	public:

	};
}


#endif