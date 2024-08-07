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
		constexpr bool isFirst()const
		{
			return _prev == NULL;
		}
		constexpr bool isLast()const
		{
			return _next == NULL;
		}
		constexpr bool isSingle()const
		{
			return isFirst() && isLast();
		}
		T unlink()
		{
			T value = _next->value();
			if (_next)
				delete _next;
		}
		void unlinkAll()
		{
			LinkNode* temp = this->_next,* del;
			this->_next = NULL;
			while (temp != NULL)
			{
				del = temp;
				temp = &temp->next();
				delete del;
			}
		}
		constexpr LinkNode& link(LinkNode& node)
		{
			if (!isSingle())
			{
				node._prev->_next = node._next;
				node._next->_prev = node._prev;
			}
			if (_next)
			{
				this->_next->_prev = &node;
			}
			node._next = _next;
			this->_next = &node;
			node._prev = this;
			return *this->_next;
		}
		constexpr LinkNode& link(T& value)
		{
			this->_next = new LinkNode(this, this->_next,value);
			return *this->_next;
		}
		constexpr LinkNode& linkPrev(LinkNode& node)
		{
			if (!isSingle())
			{
				node._prev->_next = node._next;
				node._next->_prev = node._prev;
			}
			if (_prev)
			{
				_prev->_next = &node;
			}
			node._prev = _prev;
			this->_prev = &node;
			node._next = this;
			return *this->_prev;
		}
		constexpr LinkNode& linkPrev(T& value)
		{
			this->_prev = new LinkNode(this->_prev, this, value);
			return *this->_prev;
		}
		constexpr bool isPrev(LinkNode& node)const
		{
			return this->_prev == &node;
		}
		constexpr bool isPrev(T& value)const
		{
			return this->_prev->value() == value;
		}
		constexpr bool isNext(LinkNode& node)const
		{
			return this->_next == &node;
		}
		constexpr bool isNext(T& value)const
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
