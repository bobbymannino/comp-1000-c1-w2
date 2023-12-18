#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace My01querydbunittest
{
	TEST_CLASS(My01querydbunittest)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			std::string name = "Bill";
			Assert::AreEqual(name, "Bill");
		}

		TEST_METHOD(TestMethod2) 
		{
			std::string name = "John";
			Assert::AreEqual(name, "Bill");
		}
	};
}
