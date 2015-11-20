#include "stdafx.h"
#include "CppUnitTest.h"

#include "../dllmain.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest3
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethodNew)
		{
			// TODO: Your test code here
			char out[50], fun[50] = "";
			int outSize = 50;
			RVExtension(out, outSize, fun);
			Assert::AreEqual(out, "Hello World!!");
		}

	};
}