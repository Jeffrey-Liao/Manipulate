#include "../InforUnit/LiaoException.h"
#include "../DataUnit/LinkList.h"
#include "../UserUnit/User.h"
using namespace liao;
class TestData
{
public:
	bool operator==(const TestData& obj)
	{
		return true;
	}
	bool operator<(const TestData& obj)
	{
		return true;
	}
	bool operator>(const TestData& obj)
	{
		return true;
	}
	TestData operator =(const TestData& obj)
	{
		return *this;
	}
};
class UnitTest
{
public:
	static void InforTest()
	{
		DebugInfor::instance.write( "TestDebug");
		DebugInfor::instance.printLastInfor();
		ErrorInfor::instance.write( "TestError");
		ErrorInfor::instance.printLastInfor();
		RuntimeInfor::instance.write("TestRuntime");
		RuntimeInfor::instance.printLastInfor();
		InforReader reader(DEBUGFILE);
		cout<<reader.getDate() << "\n";
		cout<<reader.getInfor() << "\n";
	}
	static void LiaoExceptionTest()
	{
		try {
			throw new LiaoException("Test", "LiaoException", "TestException", 18);
		}
		catch (FatalException* e1)
		{
			e1->display();
			delete e1;
		}
		catch (LiaoException* e2)
		{
			e2->display();
			delete e2;
			exit(COMMONFATALERROR);
		}
	}
	static  void LinkListTest()
	{
		LinkList<TestData> test;
		TestData t1, t2;
		test.append(t1);
		test.append(t2);
	}
};
int main()
{
	UnitTest::InforTest();
	UnitTest::LiaoExceptionTest();
	UnitTest::LinkListTest();
	return 0;
}