#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#include "filesystem/resourcearchive.hpp"
#define private public
#include "engine.hpp"
#include "engine.cpp"
#include "gameobject.hpp"


namespace unittests
{
	TEST_CLASS(GameObject_test)
	{
	public:

		TEST_METHOD(initialize)
		{
			Engine::initialize();
		}
	};
}