#pragma once
#ifndef SORT_H
#define SORT_H
#include"JMacros.h"
#include "LinkList.h"
namespace jeff
{
	class JeffSort
	{
		DYNAMIC
		static void partition(T& list,int begin,int end)
		{
			if (end>begin)
			{
				auto& pivot = list[end];
				int  i = begin;
				for (int j = begin; j <= end - 1; j++)
				{
					if (list[j] < pivot)
					{
						list[i].swap(list[j]);
						i++;
					}
				}
				list[i].swap(pivot);
				partition(list, begin, i-1);
				partition(list, i + 1, end);
			}
		}
		DYNAMIC
		static void merge(T* aStart,T* bStart,int size)
		{
			if (size > 0)
			{
				for (int n = 0, a = 0, b = 0; n < size * 2; ++n)
				{
					if (a < size)
					{

					}
				}
			}
			else
				throw new Exception("JeffSort", "merge", "cannot merge two empty lists.");
		}
	public:
		static JeffSort jeffSort;
		DYNAMIC
		static void insertSort(T & list)
		{
			for (int n = 0; n < (list.getSize()-1); ++n)
			{
				for (int i = n+1; i > 0; --i)
				{
					auto& temp1 = list[i - 1], & temp2 = list[i];
					if (i != 0 && temp1 > temp2)
						temp1.swap(temp2);
				}
			}
		}
		DYNAMIC
		static void mergeSort(T& list)
		{
			for (int segment = 2; segment < list.getSize(); segment += segment)
			{
				for (int i = 0; i < list.getSize();i+=segment)
				{
					for (int n = i;n<i+segment;++n)
					{
					}
				}
			
			}
		}
		
		DYNAMIC
		static void quickSort(T& list)
		{
			partition(list, 0, list.getSize()-1);
		}
		DYNAMIC
		static void heapSort(T& list)
		{
			for (int n = 0;;)
			{

			}
		}
	};
	JeffSort JeffSort::jeffSort;
}

#endif