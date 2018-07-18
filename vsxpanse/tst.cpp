#include "CppUnitTest.h"
#include "resourcemanager.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GardenVexor_unittest
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			ResourceManager::initialize();
		}

	};
}