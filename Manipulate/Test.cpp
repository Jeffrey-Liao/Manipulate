#include "DataStructure.h"
using namespace liaoUtil;
int main()
{
	List<int>& test = *new LinkList<int>();
	List<int>& test2 = *new ArrayList<int>();
	for (int n = 0; n < 10; ++n)
	{
		test.add(n);
		test2.add(n);
	}
	test.remove(3);
	test2.remove(4);
	cout << "test:" << test.toString() << "\n test2:" << test2.toString();
	delete& test;
	delete& test2;
}