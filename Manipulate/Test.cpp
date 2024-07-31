#include "DataStructure.h"
using namespace liaoUtil;
void get(int && val)
{
	cout << std::move(val);
}
int main()
{
	List<int>& test = *new LinkList<int>();
	List<int>& test2 = *new ArrayList<int>();
	vector<int> testv;
	testv.push_back(3);
	test = { 1,2,3,4,5,6 };
	test.add(313);
	test.remove(3);
	test.first() = 3;
	cout<<std::format("class ID: {}\n", test.classID());
	test.get(4) = 114514;
	test2 = test;
	test.sort();
	cout << std::format("test: {}\ntest2: {}\n", test.toString(),test2.toString());
	test2 = 3;
	cout <<std::format("short test2: {}", test2.toString()) ;
	delete& test;
	delete& test2;
}