#include "DataStructure.h"
#include "random"
#include <forward_list>
using namespace liaoUtil;
using namespace std;

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
		test.clear();
		vector<int> data = { 5,5,6,8,4,1,2,8,4,3,4,8,97,1,1,2,4,54,7 };
		test = data;
		cout << test.toString();
		return true;
	}
	static void Forward_ListTest()
	{
		
	}
};

int main()
{
	List<int>& obj = *new LiaoLinkList<int>();
	obj = { 1,2,3,4 };
	cout<<obj.equals({ 1,2,3,4 });
	delete& obj;
}