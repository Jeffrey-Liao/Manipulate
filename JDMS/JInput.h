#pragma once
#ifndef JINPUT_H
#define JINPUT_H
#include "JUi.h"
class JInput
{
	bool control;
	string cmdCache;
	string inputCache;
	char key;
public:
	void input()
	{
		for (int index = 0; key != ESC;)
		{
			key = _getch();

		}
	}
};
#endif