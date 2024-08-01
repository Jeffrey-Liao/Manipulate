#include "DataStructure.h"
#include "random"
using namespace liaoUtil;
using namespace std;
class UnitTest
{
public:
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
};
int main()
{
	UnitTest::SortedListTest();
}