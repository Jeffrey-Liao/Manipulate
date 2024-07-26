#ifndef LISTNODE_H
#define LISTNODE_H
#include"common.h"
#include"Exceptions.h"
namespace liaoUtil
{
	DYNAMIC
	class ListNode
	{
	protected:
		ListNode()
		{ }
		ListNode(ListNode& Obj)
		{}
	public:
		virtual string classID() const
		{
			return "ListNode";
		}
		virtual ListNode& next() = 0;
		virtual ListNode& prev() = 0;
		virtual ListNode& root() = 0;
		virtual ListNode& last() = 0;
		virtual ListNode& link(const T& data) = 0;
		virtual T& value() = 0;
		virtual void unlink(bool keep = false)=0;
		virtual bool isRoot()const = 0;
		virtual bool isLast() const = 0;
		virtual bool isNext(ListNode&) const = 0;
		virtual bool isPrev(ListNode&)const = 0;
		virtual bool isEmpty() const = 0;
		virtual void cut() = 0;
		virtual void setNextNull() = 0;
	};
}
#endif