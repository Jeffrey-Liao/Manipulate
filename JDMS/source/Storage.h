#pragma once
#ifndef STORAGE_H
#define STORAGE_H
#include <set>
#include "JMacro.h"
#include"storage/LinkList.h"
using namespace jeff;
class StorageUnit
{
	multiset<DyType> storage;
public:

};
enum class Types
{
	Empty,
	Int1,
	Int2,
	Int4,
	Int8,
	Float4,
	Float8,
	Char,
	String
};
class DyType
{
	void* data;
	onebyte type;
private:
	void spaceRemove();
	DYNAMIC
	Types convert(T data);
public:
	DyType();
	DYNAMIC
	DyType(T data);
	DyType(Types& newType);
	void setType(Types newType);
	bool sameType(DyType& Obj);

	bool operator ==(const DyType& Obj);
	bool operator <(const DyType& Obj);
	bool operator >(const DyType& Obj);
	const DyType operator+(const DyType& Obj);
	const DyType operator-(const DyType& Obj);
	const DyType operator*(const DyType& Obj);
	const DyType operator/(const DyType& Obj);
	const DyType& operator+=(const DyType& Obj);
	const DyType& operator-=(const DyType& Obj);
	const DyType& operator*=(const DyType& Obj);
	const DyType& operator/=(const DyType& Obj);
	DYNAMIC
	bool operator==(T data);
	DYNAMIC
	void operator=(T data);
};
class Attribute;
class Record
{
	int key;
	vector<DyType*> record;

};
class Attribute
{

};

class Table
{

};
#endif