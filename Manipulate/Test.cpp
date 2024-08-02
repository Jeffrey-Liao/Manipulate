#include "DataStructure.h"
#include "random"
#include <forward_list>
using namespace liaoUtil;
using namespace std;
class UnitTest
{
public:
	static void ArrayListTest()
	{
		try
		{
			ArrayList<int> test;
			test.remove(5);
		}
		catch (LiaoException* e)
		{
			delete e;
		}
	}
	static bool SortedListTest()
	{
		std::default_random_engine generator(std::random_device{}());

		// 创建一个均匀分布，范围为 [0, 99]
		std::uniform_int_distribution<int> distribution(0, 99);

		
		List<int>& test = *new SortedList<int>();
		cout << format("class ID: {}\n", test.classID());
		for (int n = 0; n < 100; ++n)
			test.add(distribution(generator));
		test.remove(30);
		cout << test.toString();
		return true;
	}
	static void Forward_ListTest()
	{
		try
		{
			throw new InvalidOperationException("UnitTest", "Forward_ListTest", "Test Case");
		}
		catch(LiaoException* e)
		{
		}
	}
};
int main()
{
	UnitTest::ArrayListTest();
}