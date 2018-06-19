#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include <fstream>
#include <windows.h>

#include <chrono>
#include "filesystem/zipwrap.hpp"
#define private public
#include "filesystem/resourcearchive.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::chrono;

namespace unittests
{

	/*-------------------------------------------------------
		Tests.
	---------------------------------------------------------*/
	TEST_CLASS(ResourceArchive_test)
	{
	public:
		TEST_METHOD(constructor_test)
		{
			ResourceArchive archive("TestResources");
		}
		TEST_METHOD(get_item_test)
		{
			ResourceArchive archive("TestResources");
			std::string path_to_file = "Fonts\\calibri.ttf";
			ResourceFile * file = archive.get_item(path_to_file);
			Assert::IsNotNull(file);
		}
		TEST_METHOD(free_item_test)
		{
			ResourceArchive archive("TestResources");
			std::string path_to_file = "Fonts\\calibri.ttf";
			ResourceFile * file;
			for (int i = 0; i < 5; ++i)
			{
				file = archive.get_item(path_to_file);
				archive.free_item(path_to_file);
			}

		}
	};
}
