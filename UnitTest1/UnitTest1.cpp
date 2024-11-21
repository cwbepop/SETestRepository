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
			int expected = 135;
			//0.00135
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
		TEST_METHOD(TestOutputToConsole)
		{
			//input
			double a = 1, b = 3, h = 0.5;
			int n = 4;
			ostringstream capturedOutput;
			streambuf* origCout = cout.rdbuf(capturedOutput.rdbuf());
	
			outputToConsole(a, b, h, n);

			cout.rdbuf(origCout);

			string expectedOutput =
				"|x = 1| y = 1|\n"
				"|x = 1.5| y = 0.64|\n"
				"|x = 2| y = 0.390625|\n"
				"|x = 2.5| y = 0.237954|\n"
				"|x = 3| y = 0.147929|\n";
			Assert::AreEqual(expectedOutput, capturedOutput.str());
		}
		TEST_METHOD(TestOutputToFile)
		{
			// input
			double a = 1.0, b = 3.0, h = 0.5;
			int n = 4;
			string fileName = "test_output.txt";

			outputToFile(a, b, h, n, fileName);
			ifstream infile(fileName);
			Assert::IsTrue(infile.is_open(), L"Output file not created.");

			stringstream buffer;
			buffer << infile.rdbuf();
			infile.close();

			string actualOutput = buffer.str();
			string expectedOutput =
				"|x = 1| y = 1|\n"
				"|x = 1.5| y = 0.64|\n"
				"|x = 2| y = 0.390625|\n"
				"|x = 2.5| y = 0.237954|\n"
				"|x = 3| y = 0.147929|\n";

			Assert::AreEqual(expectedOutput, actualOutput);
			remove(fileName.c_str());
		}
		TEST_METHOD(TestInputFromFile_ValidFile)
		{
			ofstream testFile("test1.txt");
			testFile << "1.0 2.0 0.5 4\n";
			testFile.close();

			double a, b, h;
			int n;
			// simulate input
			istringstream simulatedInput("test1.txt\n");
			streambuf* origCin = cin.rdbuf(simulatedInput.rdbuf());

			ostringstream capturedOutput;
			streambuf* origCout = cout.rdbuf(capturedOutput.rdbuf());

			inputFromFile(a, b, h, n);

			cin.rdbuf(origCin);
			cout.rdbuf(origCout);
			Assert::AreEqual(1.0, a, 0.0001);
			Assert::AreEqual(2.0, b, 0.0001);
			Assert::AreEqual(0.5, h, 0.0001);
			Assert::AreEqual(4, n);

			remove("test1.txt");
		}

	};
}
