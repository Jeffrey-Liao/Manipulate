#pragma once
#include "ListOpers.h"
#ifndef STACK_H
#define STACK_H
namespace jeff
{
	DYNAMIC
	class LinerOper
	{
	protected:
		using LinkNode = LinkNode<T>;
		LinkNode* Top;
		LinkNode* Bottom;
		int size;
	public:
		LinerOper()
			:size(0), Top(NULL), Bottom(NULL)
		{}
		LinerOper(T* newDataList, int listSize)
			:size(listSize)
		{
			for (int n = 0; n < this->size; ++n)
			{
				if (this->Top == NULL)
					this->Top = this->Bottom = new LinkNode(newDataList[n]);
				else
					this->Top = new LinkNode(this->Top, newDataList[n]);
			}
		}
		virtual void push(T newData) = 0;
		int getSize()
		{
			return this->size;
		}
		bool isEmpty()
		{
			return this->size == 0;
		}
		T& getTop()
		{
			return this->Top->get();
		}
		LinkNode& getTopNode()
		{
			return *this->Top;
		}
		T pop()
		{
			if (!isEmpty())
			{
				LinkNode* temp = this->Top;
				this->Top = &this->Top->getNext();
				T result = temp->get();
				delete temp;
				--this->size;
				if (this->Top == NULL)
					this->Bottom = this->Top;
				return result;
			}
			else
				return ASTYPE ZERO(sizeof(T)).Export();
		}
		void clear()
		{
			while (this->Top == NULL)
			{
				LinkNode* temp = this->Top;
				this->Top = &this->Top->getNext();
				delete temp;
			}
			this->Bottom = this->Top;
		}
	};
	DYNAMIC
	class Stack:public LinerOper<T>
	{
		using LinkNode = LinkNode<T>;
	public:
		Stack():LinerOper<T>()
		{}
		Stack(T* newDataList, int listSize):LinerOper<T>(newDataList,listSize)
		{}
		void push(T newData)
		{
			if (this->Top == NULL)
				this->Top = this->Bottom = new LinkNode(newData);
			else
				this->Top = new LinkNode(NULL,this->Top, newData);
			++this->size;
		}
		~Stack()
		{
			this->clear();
		}
	};
	DYNAMIC
	class StaticLinerOper
	{
		using LinkNode = LinkNode<T>;
	protected:
		T* list;
		const int size;
		int eleSize;
		void overFlow()
		{
			throw ("Structure OverFlow");
		}
		void underFlow()
		{
			throw ("Structure UnderFlow");
		}
	public:
		StaticLinerOper(int newSize)
			:size(newSize),eleSize(0)
		{
			list = new T[size];
		}
		StaticLinerOper(T* dataList,int newSize)
			:size(newSize), eleSize(0)
		{
			list = new T[size];
			ARRAYASSIGN(list, dataList, size);
		}
		int getSize()
		{
			return this->size;
		}
		int count()
		{
			return this->eleSize;
		}
		bool isEmpty()
		{
			return this->eleSize == 0;
		}
		bool isFull()
		{
			return this->eleSize == this->size;
		}
		void push(T newData)
		{
			if (!this->isFull())
				this->list[this->eleSize++] = newData;
		}
		virtual T pop() = 0;
		T getTop()
		{
			return this->list[0];
		}
		void clear()
		{
			eleSize = 0;
		}
		~StaticLinerOper()
		{
			delete this->list;
			this->eleSize = 0;
		}
	};
	DYNAMIC
	class StaticStack:public StaticLinerOper<T>
	{
		using LinkNode = LinkNode<T>;
	public:
		StaticStack(int defaultSize):StaticLinerOper<T>(defaultSize)
		{}
		StaticStack(T* newDataList,int listSize)
			:StaticLinerOper<T>(newDataList, listSize)
		{}
		T pop()
		{
			if (!this->isEmpty())
				return this->list[--this->eleSize];
			else
				return ASTYPE ZERO(sizeof(T)).Export();
		}
	};
}
#endif