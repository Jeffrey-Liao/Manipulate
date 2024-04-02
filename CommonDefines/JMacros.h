#pragma once
#include <string>
#include<stdio.h>
#include <conio.h>
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <vector>
#ifndef MARCRO_H
#define MARCRO_H
namespace liao
{
	using namespace std;
	using onebyte = char;
#define BYTELEN 8
#define CHAR2INT 48
	///TYPE NAME
#define INT4NAME typeid(int).name()
#define INT2NAME typeid(short int).name()
#define INT1NAME typeid(onebyte).name()
#define INT8NAME typeid(long long).name()
#define CHARNAME typeid(char).name()
#define FLOATNAME typeid(float).name()
#define DOUBLENAME typeid(double).name()
#define STRINGNAME typeid(std::string).name()
#define BOOLNAME typeid(bool).name()

#define ARLEN (x)  (sizeof(x))
#define DYNAMIC template<class T>
#define DYNAMICS template<class T, class T2>
#define DYNAMICSIZE template<class T ,int newSize>
#define ASBOOL *(bool*)
#define ASTYPE *(T*)
#define BOOLP (bool*)
#define TYPEP (TYPE*)
#define ASINT4 *(int*)
#define ASINT1 *(char*)
#define ASINT2 *(short int*)
#define ASINT8 *(long long* )
#define ASCHAR *(char*)
#define ASFLOAT *(float*)
#define ASDOUBLE *(double*)
#define ASSTRING *(string*)
#define ASNODE *(Node*)
#define ASSTUINF *(StuInfor*)
#define ASCHAIN *(Chain*)
#define INDTYPE unsigned int
//int pointer
#define I4P (int*)
//short pointer
#define I2P (short int*)
//byte pointer
#define I1P (char* )
//long pointer
#define I8P (long long*)
//char pointer
#define CP (char*)
//float pointer
#define FP (float*)
//double pointer
#define DP (double*)
//template pointer
#define TP (TYPE* )
//Calculation

#define ARRAYASSIGN(x,y,size)for(int n = 0;n<size;++n)x[n]=y[n]
#define ISODD(x) x%2!=0
#define ISEVEN (x) x%2==0
#define MCLEAR(x , size) for(int n =0;n<size;++n)x[n] = '\0';
	class EMPTY
	{
		void* Space;
	public:
		EMPTY() :Space(NULL)
		{}
		
		EMPTY(int newSize)
		{
			Space = new char[newSize];
			MCLEAR((CP Space), newSize);
		}
		const void* const Export()
		{
			return Space;
		}
		void* Allocate(int size, bool reclaim = true)
		{
			if (Space == NULL)
			{
				Space = new char[size];
				MCLEAR((CP Space), size);
			}
			else if (Space != NULL && size > _msize(Space))
			{
				delete[] Space;
				Space = NULL;
			}
			else
				return this;
			Space = new char[size];
			MCLEAR((CP Space), size);
			return this;
		}
		EMPTY& operator() (int newSize)
		{
			if (Space == NULL)
			{
				Space = new char[newSize];
				MCLEAR((CP Space), newSize);
			}
			else if (Space != NULL && newSize > _msize(Space))
			{
				delete[] Space;
				Space = NULL;
			}
			else
				return *this;
			Space = new char[newSize];
			MCLEAR((CP Space), newSize);
			return *this;
		}
		~EMPTY()
		{
			delete[] Space;
		}
	};
	static EMPTY ZERO;
}
#endif