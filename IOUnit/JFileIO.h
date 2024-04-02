#ifndef JFILE_H
#define JFILE_H
#include"JMacro.h"
class FileIO
{
	fstream file;
public:
	FileIO(string fileName)
	{
		file.open(fileName, ios::in | ios::out);
	}
};
static FileIO fileIO;
#endif