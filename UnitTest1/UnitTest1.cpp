#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\Zver\Desktop\lab\SElab\Project1\task.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(calculate_test)
	{
	public:
		
		TEST_METHOD(find_y_test1)
		{
			int x = -5;
			int n = 1;
			int expected = 3;

			int actual = find_y(x, n);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(find_y_test2)
		{
			int x = 11.5;
			int n = 4;
			int expected = 0.00135;

			int actual = find_y(x, n);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(checkValidParams_1)
		{
			int n = -5;
			try
			{
				checkValidParams(n); 
				Assert::Fail(); 
			}
			catch (const std::runtime_error& e) 
			{
				Assert::IsTrue(true); 
			}
			catch (...) 
			{
				Assert::Fail(); 
			}
		}
		TEST_METHOD(checkValidParams_2)
		{
			int n = 6; 
			try
			{
				checkValidParams(n); 
				Assert::IsTrue(true);
			}
			catch (const std::runtime_error& e) 
			{
				Assert::Fail(); 
			}
			catch (...) 
			{
				Assert::Fail(); 
			}
		}
	};
}
