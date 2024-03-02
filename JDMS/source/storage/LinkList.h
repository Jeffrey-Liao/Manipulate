#pragma once
#ifndef LINK_H
#define LINK_H
#include "Jnode.h"
namespace jeff
{
	DYNAMICS
	class LinkListOpers
	{
	protected:
		using LinkNode = LinkNode<T>;
		T2* Head;
		T2* End;
		int size;
		pair<T2*, int> lastPos;
		virtual void append()
		{
			if (this->Head == NULL)
				this->Head = this->End = new T2(ASTYPE ZERO(sizeof(T)).Export());
			else
				this->End = new T2(this->End, ASTYPE ZERO(sizeof(T)).Export());
			++this->size;
		}
	public:
		LinkListOpers()
			:size(0),Head(NULL), End(NULL), lastPos(NULL, -1)
		{}
		LinkListOpers(const int newSize)
			:size(newSize), Head(NULL), End(NULL),lastPos(NULL, -1)
		{}
		int getSize()
		{
			return size;
		}
		bool isEmpty()
		{
			return this->size == 0;
		}
		T2& getHead()
		{
			return *this->Head;
		}
		T2& getEnd()
		{
			return *this->Head;
		}
		T2& append(T newData)
		{
			if (this->isEmpty())
				this->End = this->Head = new T2(newData);
			else
				this->End = new T2(this->End, newData);
			this->size++;
			return *this->End;
		}
		void append(T* newDataList, int listSize)
		{
			for (int n = 0; n < listSize; ++n)
			{
				this->append(newDataList[n]);
			}
		}
		void clear()
		{
			T2* temp = NULL;
			while (this->Head != NULL)
			{
				temp = this->Head;
				if (&(this->Head->getNext()) == ZERO.Export())
					break;
				else
					this->Head = &this->Head->getNext();
				delete temp;
			}
			this->Head = this->End = NULL;
			this->size = 0;
		}
		void allocate(unsigned int newSize)
		{
			for (unsigned int n = 0; n < newSize; ++n)
				this->append();
		}
		virtual void remove(unsigned int index) = 0;
		virtual T2& insert(unsigned int index, T newData) = 0;
		virtual T& get(unsigned int index) = 0;
		virtual T2& getNode(unsigned int index) = 0;
		virtual bool exist(T existData) = 0;
		virtual int find(T existData) = 0;
		virtual vector<T2> search(T existData) = 0;
		virtual T& operator[](unsigned int index) = 0;
		virtual T2& operator+(T2& newNode) = 0;
		virtual T2& operator+(T newData) = 0;
		virtual void operator-(unsigned int index) = 0;
		virtual T2& operator() (unsigned int index, T newData) = 0;
	};
	DYNAMIC
	class LinkList:public LinkListOpers<T, LinkNode<T>>
	{
		using LinkNode = LinkNode<T>;

		pair<LinkNode*, int> lastPos;
		void append()
		{
			if (this->Head == NULL)
				this->Head = this->End = new LinkNode(ASTYPE ZERO(sizeof(T)).Export());
			else
				this->End = new LinkNode(this->End, ASTYPE ZERO(sizeof(T)).Export());
			++this->size;
		}
		LinkNode* getFather(int index)
		{
			LinkNode* father = this->Head;
			for (int n = 0; n <= index - 1; n++)
				father = &father->getNext();
			return father;
		}
	public:
		LinkList()
			:lastPos(NULL, -1)
		{}
		LinkList(int defaultSize)
			:LinkListOpers<T, LinkNode>(defaultSize)
		{
			this->allocate(defaultSize);
		}
		LinkList(int defaultSize, T defaultValue)
		:LinkListOpers<T, LinkNode>(defaultSize)
		{
			for (int n = 0; n < defaultSize; ++n)
				this->append(defaultValue);
		}
		LinkList(T* newDataList,int size)
		{
			this->append(newDataList, size);
		}
		LinkList(LinkList& Obj)
			:LinkListOpers<T, LinkNode>(Obj.size)
		{
			for (int n = 0; n < this->size; ++n)
				this->append(Obj.get(n));
		}
		LinkNode& append(T newData)
		{
			if (this->isEmpty())
				this->End = this->Head = new LinkNode(newData);
			else
				this->End = new LinkNode(this->End, newData);
			this->size++;
			return *this->End;
		}
		void append(T* newDataList, int listSize)
		{
			for (int n = 0; n < listSize; ++n)
			{
				append(newDataList[n]);
			}
		}
		LinkNode & getNode(unsigned int index)
		{
			if (index == this->size - 1)
				return *this->End;
			if (index == this->lastPos.second)
				return *this->lastPos.first;
			else if (index < this->size)
			{
				LinkNode* temp = this->Head;
				unsigned int n = 0;
				if (this->lastPos.second != 0 && this->lastPos.second < index)
				{
					temp = this->lastPos.first;
					n = this->lastPos.second;
				}
				for (; n < index; n++)
					temp = &temp->getNext();
				this->lastPos = make_pair(temp, n);
				return *temp;
			}
			else
			{
				string error = "index overflow. The given index is (" + to_string(index) + "). But the size of list was (" + to_string(this->size) + ").";
				throw new  LiaoException("LinkNode","getNode",error);
				return ASLINKNODE ZERO(sizeof(LinkNode)).Export();
			}

		}
		void remove(unsigned int index)
		{
			--this->size;
			if (index < this->size)
			{
				LinkNode* father =getFather(index), * temp = NULL;
				temp = &father->getNext();
				father->link(temp->getNext());
				delete temp;
			}
		}
		void allocate(unsigned int newSize)
		{
			for (unsigned int n = 0; n < newSize; ++n)
				append();
		}
		LinkNode& insert(unsigned int index, T newData)
		{
			if (index < this->size)
			{
				LinkNode* father = getFather(index);
				return *(new LinkNode(father, &father->getNext(),newData));
			}
			else
			{
				string error = "index overflow. The given index is (" + to_string(index) + "). But the size of list was (" + to_string(this->size) + ").";
				throw new  LiaoException("LinkList","insert",error);
				return ASLINKNODE ZERO(sizeof(LinkNode)).Export();
			}
		}
		T& get(unsigned int index)
		{
			return getNode(index).get();
		}
		bool exist(T existData)
		{
			LinkNode* temp = this->Head;
			while (temp != NULL)
			{
				if (temp->compare(existData))
					return true;
				temp = &temp->getNext();
			}
			return false;
		}
		bool exist(T& existData)
		{
			LinkNode* temp = this->Head;
			while (temp != NULL)
			{
				if (temp->compare(existData))
					return true;
				temp = &temp->getNext();
			}
			return false;
		}
		int find(T existData)
		{
			LinkNode* temp = this->Head;
			for (int n = 0; n < this->size; ++n)
			{
				if (*temp == existData)
					return n;
				temp = &temp->getNext();
			}
			return -1;
		}
		int find( T& existData)
		{
			LinkNode* temp = this->Head;
			for (int n = 0; n < this->size; ++n)
			{
				if (*temp == existData)
					return n;
				temp = &temp->getNext();
			}
			return -1;
		}
		vector<LinkNode> search(T existData)
		{
			vector<LinkNode> tempList;
			LinkNode* temp = this->Head;
			for (int n = 0; n < this->size; ++n)
			{
				if (*temp == existData)
					tempList.push_back(*temp);
				temp = &temp->getNext();
			}
			return tempList;
		}
		void sort(void (*sortMethod)(LinkList&))
		{
			sortMethod(*this);
		}
		T& operator[](unsigned int index)
		{
			return this->get(index);
		}
		LinkNode& operator+(LinkNode& newNode)
		{
			this->End->link(newNode);
			this->End = &newNode;
			return *this->End;
		}
		LinkNode& operator+(T newData)
		{
			 return this->append(newData);
		}
		 void operator-(unsigned int index)
		 {
			 this->remove(index);
		 }
		 LinkNode& operator() (unsigned int index,T newData)
		 {
			return this->insert(index, newData);
		 }
		~LinkList()
		{
			this->clear();
		}
	};
	DYNAMIC
	class DoubleLinkList:public LinkListOpers<T,DoubleLinkNode<T>>
	{
		using DoubleLinkNode = DoubleLinkNode<T>;
	public:
		DoubleLinkList()
			:LinkListOpers<T,DoubleLinkNode>()
		{}
		DoubleLinkList(int defaultSize, T defaultValue)
			:LinkListOpers<T, DoubleLinkNode>(defaultSize)
		{
			for (int n = 0; n < defaultSize; ++n)
				this->append(defaultValue);
		}
		DoubleLinkList(T* newDataList, int size)
		{
			this->append(newDataList, size);
		}
		DoubleLinkList(const initializer_list<T>& newDataList)
		{
			for (auto& newData:newDataList)
			{
				this->append(newData);
			}
		}
		DoubleLinkList(DoubleLinkList& Obj)
			:LinkListOpers<T, DoubleLinkNode>(Obj.size)
		{
			for (int n = 0; n < this->size; ++n)
				this->append(Obj.get(n));
		}
		DoubleLinkNode& getNode(unsigned int index)
		{
			if (index == this->size - 1)
				return *this->End;
			if (index == this->lastPos.second)
				return *this->lastPos.first;
			else if (index < this->size)
			{
				DoubleLinkNode* temp = this->Head;
				int n = 0,tempIndex = index;
				bool reverse = false;
				if (this->lastPos.first != NULL && this->lastPos.second < index)
					temp = this->lastPos.first, n = this->lastPos.second;
				else if (this->lastPos.first != NULL && this->lastPos.second > index && this->lastPos.second - index < index)
					temp = this->lastPos.first, tempIndex = this->lastPos.second - index, reverse = true;
				for (; n < tempIndex; ++n)
				{
					if (reverse)
						temp = &temp->getPrev();
					else
						temp = &temp->getNext();
				}
				this->lastPos.first = temp;
				this->lastPos.second = index;
				return *temp;
			}
			else
			{
				string error = "index overflow. The given index is ("+ to_string(index)+"). But the size of list was ("+to_string(this->size)+").";
				throw new  LiaoException("DoubleLinkList","getNode", error);
				return ASDOUBLENODE ZERO(sizeof(DoubleLinkNode)).Export();
			}
		}
		void remove(unsigned int index)
		{
			if (index < this->size)
				delete &getNode(index);
		}
		DoubleLinkNode& insert(unsigned int index, T newData)
		{
			if (index < this->size)
			{
				DoubleLinkNode* temp = &this->getNode(index).getPrev(), * newNode = new DoubleLinkNode(temp, &temp->getNext(), newData);
				return *newNode;
			}
			else
			{
				string error = "index overflow. The given index is (" + to_string(index) + "). But the size of list was (" + to_string(this->size) + ").";
				throw new  LiaoException("DoubleLinkList","insert", error);
				return ASDOUBLENODE JNULL;
			}

		}
		void sort(void (*sortMethod)(DoubleLinkList&))
		{
			sortMethod(*this);
		}
		int find(T existData)
		{
			DoubleLinkNode* begin = this->Head,*end = this->End;
			for (int n = 0; n < this->size; ++n)
			{
				if (begin->get() == existData)
					return n;
				if (end->get() == existData)
					return this->size - n;
				begin = &begin->getNext();
				end = &end->getPrev();
			}
			return -1;
		}
		bool exist(T existData)
		{
			return find(existData) != -1;
		}
		T& get(unsigned int index)
		{
			if (index < this->size)
				return getNode(index).get();
			else
			{
				string error = "index overflow. The given index is (" + to_string(index) + "). But the size of list was (" + to_string(this->size) + ").";
				throw new  LiaoException("DoubleLinkList","get",error);
				return ASTYPE JNULL;
			}

		}
		vector<DoubleLinkNode> search(T existData)
		{
			vector<DoubleLinkNode> tempList;
			DoubleLinkNode* begin = this->Head,*end = this->End;
			for (int n = 0; n < (this->size/2+1); ++n)
			{
				if (begin->get() == existData)
					tempList.push_back(*begin);
				if(end->get() == existData)
					tempList.push_back(*end);
				begin = &begin->getNext();
				end = &end->getPrev();
			}
			return tempList;
		}
		T& operator[](unsigned int index)
		{
			return this->get(index);
		}
		DoubleLinkNode& operator+(DoubleLinkNode& newNode)
		{
			this->End->link(newNode);
			this->End = &this->End->getNext();
			return *this->End;
		}
		DoubleLinkNode& operator+(T newData)
		{
			return this->append(newData);
		}
		void operator-(unsigned int index)
		{
			this->remove(index);
		}
		DoubleLinkNode& operator() (unsigned int index, T newData)
		{
			return this->insert(index, newData);
		}
	};
}
#endif