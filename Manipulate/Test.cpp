#include "DataStructure.h"
using namespace liaoUtil;
using namespace std;
class UnitTest
{
public:
	static bool SortedListTest()
	{
		List<int>& test = *new SortedList<int>();
		cout << format("class ID: {}\n", test.classID());
		test.add(1);
		test.add(5);
		test.add(2);
		test.add(9);
		test.add(7);
		test.add(6);
		test.add(8);
		test.add(10);
		test.add(3);
		cout << test.toString();
		return true;
	}
};
int main()
{
	UnitTest::SortedListTest();
}