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
		LinkNode(const T&& value)
			:Node(value), _next(NULL), _prev(NULL)
		{}
		LinkNode(const T& value)
			:Node(value), _next(NULL), _prev(NULL)
		{}
		LinkNode(LinkNode&obj)
			:Node(obj), _next(obj._next), _prev(obj._prev)
		{}
		LinkNode(LinkNode* father)
			:_prev(father),_next(NULL), Node()
		{
			if (father)
				father->_next = this;
		}
		LinkNode(LinkNode* father, const T&& value)
			:_prev(father),_next(NULL), Node(value)
		{
			if (father)
				father->_next = this;
		}
		LinkNode(LinkNode* father, const T& value)
			:_prev(father), _next(NULL), Node(value)
		{
			if (father)
				father->_next = this;
		}
		LinkNode(LinkNode* father,LinkNode* son)
			:_prev(father), _next(son), Node()
		{
			if (father)
				father->_next = this;
			if (son)
				son->_prev = this;
		}
		LinkNode(LinkNode* father, LinkNode* son, const T& value)
			:_prev(father), _next(son), Node(value)
		{
			if (father)
				father->_next = this;
			if (son)
				son->_prev = this;
		}
		LinkNode(LinkNode* father, LinkNode* son,const T&& value)
			:_prev(father),_next(son), Node(value)
		{
			if (father)
				father->_next = this;
			if (son)
				son->_prev = this;
		}
	public:
		LinkNode& next()
		{
			return *this->_next;
		}
		LinkNode& prev()
		{
			return *this->_prev;
		}
		bool isFirst()
		{
			return _prev == NULL;
		}
		bool isLast()
		{
			return _next == NULL;
		}
		bool isSingle()
		{
			return isFirst() && isLast();
		}
		T unlink()
		{
			T value = _next->value();
			if (_next)
				delete _next;
		}
		LinkNode& link(LinkNode& node)
		{
			if (!isSingle())
			{
				node._prev->_next = node._next;
				node._next->_prev = node._prev;
			}
			this->_next = &node;
			node._prev = this;
			return *this->_next;
		}
		LinkNode& link(T& value)
		{
			this->_next = new LinkNode(this, value);
			return *this->_next;
		}
		bool isPrev(LinkNode& node)
		{
			return this->_prev == &node;
		}
		bool isPrev(T& value)
		{
			return this->_prev->value() == value;
		}
		bool isNext(LinkNode& node)
		{
			return this->_next == &node;
		}
		bool isNext(T& value)
		{
			return this->_next->value() == value;
		}
		~LinkNode()
		{
			if (_next)
			{
				_next->_prev = _prev;
			}
			if (_prev)
			{
				_prev->_next = _next;
			}
		}
	};
}
#endif
