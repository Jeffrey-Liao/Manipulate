#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include "Stack.h"
namespace jeff
{
	DYNAMIC
	class Queue:public LinerOper<T>
	{
		using LinkNode = LinkNode<T>;
	public:
		Queue() :LinerOper<T>()
		{}
		Queue(T* newDataList, int listSize)
			:LinerOper<T>(newDataList, listSize)
		{}
		void push(T newData)
		{
			if (this->Top == NULL)
				this->Top = this->Bottom = new LinkNode(newData);
			else
				this->Bottom = new LinkNode(this->Bottom, newData);
		}
		~Queue()
		{
			this->clear();
		}
	};
	DYNAMIC
	class StaticQueue:public StaticLinerOper<T>
	{
		int index;
	public:
		StaticQueue(int defaultSize) 
			:StaticLinerOper<T>(defaultSize), index(0)
		{}
		StaticQueue(T* newDataList, int listSize)
			:StaticLinerOper<T>(newDataList, listSize), index(0)
		{}
		T pop()
		{
			if (!this->isEmpty())
			{
				--this->eleSize;
				return this->list[index++ % this->size];
			}
			else
				return ASTYPE ZERO(sizeof(T)).Export();
		}
	};
}

#endif