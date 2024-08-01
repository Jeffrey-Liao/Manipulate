#ifndef LINKNODE_H
#define LINKNODE_H
#include"Node.h"
namespace liaoUtil
{
	using liaoInfor::InvalidOperationException;
	DYNAMIC
	class LinkNode:public Node<T>
	{
		using Node = Node<T>;
		LinkNode* _next;
		LinkNode* _prev;
	public:
		LinkNode()
			:Node(),_next(NULL),_prev(NULL)
		{}
		LinkNode(T&& value)
			:Node(value), _next(NULL), _prev(NULL)
		{}
		LinkNode(T& value)
			:Node(value), _next(NULL), _prev(NULL)
		{}
		LinkNode(LinkNode&obj)
			:Node(obj), _next(obj._next), _prev(obj._prev)
		{}
		LinkNode(LinkNode* father)
			:_prev(father), Node()
		{
			if (father)
				father->_next = this;
		}
		LinkNode(LinkNode* father,T&& value)
			:_prev(father), Node(value)
		{
			if (father)
				father->_next = this;
		}
		LinkNode(LinkNode* father, T& value)
			:_prev(father), Node(value)
		{
			if (father)
				father->_next = this;
		}
		LinkNode(LinkNode* father,LinkNode* son)
			:_prev(father), Node()
		{
			if (father)
				father->_next = this;
			if (son)
				son->_prev = this;
		}
		LinkNode(LinkNode* father, LinkNode* son, T& value)
			:_prev(father), Node(value)
		{
			if (father)
				father->_next = this;
			if (son)
				son->_prev = this;
		}
		LinkNode(LinkNode* father, LinkNode* son, T&& value)
			:_prev(father), Node(value)
		{
			if (father)
				father->_next = this;
			if (son)
				son->_prev = this;
		}
	public:

	};
}
#endif
