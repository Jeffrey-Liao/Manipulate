#pragma once
#ifndef LISTOPER_H
#define LISTOPER_H
#include"Jnode.h"
namespace jeff
{
	DYNAMIC
	class ListOper
	{
		using LinkNode = LinkNode<T>;
	protected:
		int size;
	public:
		ListOper()
			:size(0)
		{}
		ListOper(int newSize)
			:size(newSize)
		{}
		int getSize()
		{
			return this->size;
		}
		virtual LinkNode& getHead() = 0;
		virtual LinkNode& getEnd() = 0;
		virtual T& get(unsigned int index) = 0;
		virtual void remove(unsigned int index) = 0;
		virtual void removeSubList(unsigned int Start, unsigned int End) = 0;
		virtual bool exist(T data) = 0;
		virtual void append(T newData) = 0;
		virtual void append(T* newDataList) = 0;
		virtual void insert(int pos, T newData) = 0;
		virtual void insert(int pos, T* newDataList) = 0;
		virtual void clear() = 0;
		virtual LinkNode& find(T data) = 0;
		virtual vector<LinkNode&> search(T data) = 0;
		virtual void sort() = 0;
		virtual LinkNode& operator[](unsigned int index) = 0;
		virtual LinkNode& operator+(T data) = 0;
		bool isEmpty()
		{
			return this->size == 0;
		}
	};

}
#endif