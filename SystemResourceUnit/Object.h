#ifndef OBJECTRECLAIM_H
#define OBJECTRECLAIM_H
#include"common.h"
DYNAMIC
class Object
{
	static T& newObject()
	{
		return new T();
	}
	static void delObject(T& obj)
	{
		delete obj;
		&obj = NULL;
	}
};
#endif