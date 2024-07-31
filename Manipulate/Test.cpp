#include "DataStructure.h"
using namespace liaoUtil;
int main()
{
	List<int>& test = *new LinkList<int>();
	List<int>& test2 = *new ArrayList<int>();
	test = { 1,2,3,4,5,6 };
	test.remove(3);
	test.first() = 3;
	cout<<std::format("class ID: {}\n", test.classID());
	test.get(4) = 114514;
	test2 = test;
	test.
	cout << std::format("test: {}\ntest2: {}\n", test.toString(),test2.toString());
	test2 = 3;
	cout <<std::format("short test2: {}", test2.toString()) ;
	delete& test;
	delete& test2;
}