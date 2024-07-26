#ifndef LINKNODE_H
#define LINKNODE_H
#include"ListNode.h"
#include"Node.h"
namespace liaoUtil
{
	using liaoInfor::InvalidOperationException;
	DYNAMIC
	class LinkNode:public ListNode<T>,public Node<T>
	{
		using ListNode = ListNode<T>;
		using Node = Node<T>;
		LinkNode* _next;
		LinkNode* _prev;
	private:
		LinkNode& prev() override
		{
			throw new InvalidOperationException("LinkNode", "prev", "Cannot get prev node for link node.");
		}
		LinkNode& root() override
		{
			throw new InvalidOperationException("LinkNode", "root", "Cannot get root node for link node.");
		}
	public:
		LinkNode()
			:ListNode(),_next(NULL)
		{}
		LinkNode(const T& data)
			:Node(data),_next(NULL)
		{}
		LinkNode(LinkNode& obj)
			:ListNode(obj),_next(obj._next)
		{}
		LinkNode(LinkNode* father)
			:_next(NULL)
		{
			father->_next = this;
		}
		LinkNode(LinkNode* father,const T& data)
			:Node(data),_next(NULL)
		{
			father->_next = this;
		}
		LinkNode(LinkNode* father, LinkNode* son)
			:ListNode(), _next(son)
		{
			father->_next = this;
		}
		LinkNode(LinkNode* father, LinkNode* son, const T& data)
			:Node(data), _next(son)
		{
			father->_next = this;
		}
		string classID() const override
		{
			return "LinkNode";
		}
		LinkNode& next()override
		{
			return *_next;
		}
		LinkNode& last() override
		{
			if (this->_next != NULL)
			{
				LinkNode* result = this->_next;
				while (result->_next != NULL)
					result = result->_next;
				return *result;
			}
			else
				return *this;
		}
		LinkNode& link(const T& data)override
		{
			if (_next)
				_next = new LinkNode(this, _next, data);
			else
				_next = new LinkNode(this, data);
			return *_next;
		}
		void unlink(bool keep = false) override
		{
			if (keep)
			{
				LinkNode* temp = this->_next;
				this->_next = _next->_next;
				delete temp;
			}
			else
			{
				delete this->_next;
				this->_next = NULL;
			}
		}
		bool isRoot()const override
		{
			return false;
		}
		ListNode& take(LinkNode& node)
		{
			this->_next = &node;
			return *this->_next;
		}
		bool isLast()const override
		{
			return _next == NULL;
		}
		bool isNext(ListNode& obj) const override
		{
			return _next == &obj;
		}
		bool isPrev(ListNode& obj)const override
		{
			return &obj.next() == _next;
		}
		bool isEmpty() const override
		{
			return _next == NULL;
		}
		T& value() override
		{
			return this->Node::value();
		}
		void cut() override
		{
			LinkNode* ptr = this->_next,*del = ptr;
			while (ptr != NULL)
			{
				ptr = &ptr->next();
				delete del;
				del = ptr;
			}
			this->_next = NULL;
		}
		void cloneTo(LinkNode& obj)
		{
			obj.assign(this->value());
		}
		void setNextNull() override
		{
			if (this->_next)
				delete this->_next;
			this->_next = NULL;
		}
	};
	DYNAMIC
	class LinkNodeStd :public ListNode<T>
	{
		using ListNode = ListNode<T>;
		using list = list<T>;
		list& dataSource;
		list::iterator itor;
		void relocate()
		{
			itor = dataSource.end();
			itor--;
		}
	public:
		LinkNodeStd(list& dataSource)
			:ListNode(),dataSource(dataSource)
		{}
		LinkNodeStd(LinkNodeStd& obj)
			:ListNode(),dataSource(obj.dataSource),itor(obj.itor)
		{}

		string classID() const override
		{
			return "LinkNode(std)";
		}
		LinkNodeStd& next()override
		{
			if (itor != dataSource.end())
				itor++;
			return *this;
		}
		LinkNodeStd& prev()override
		{
			if (itor != dataSource.begin())
				itor--;
			return *this;
		}
		LinkNodeStd& root()override
		{
			itor = dataSource.begin();
			return *this;
		}
		LinkNodeStd& last()override
		{
			relocate();
			return *this;
		}
		T& value() override
		{
			return *itor;
		}
		LinkNodeStd& link(const T& value)override
		{
			dataSource.push_back(value);
			relocate();
			return *this;
		}
		void unlink(bool keep = false)override
		{
			if (keep)
				dataSource.erase(itor++);
			else
				this->cut();
		}
		void set(list::iterator itor)
		{
			this->itor =itor;
		}
		 list::iterator& get()
		{
			return itor;
		}
		bool isRoot()const override
		{
			return itor == dataSource.begin();
		}
		bool isLast()const override
		{
			return --dataSource.end() == itor;
		}
		bool isNext(ListNode& node)const override
		{
			return false;
		}
		bool isPrev(ListNode& node)const override
		{
			return false;
		}
		bool isEmpty()const override
		{
			return isRoot() || isLast();
		}
		void cut()
		{
			;
		}
		void setNextNull()
		{
			cut();
		}
	};
}
#endif
