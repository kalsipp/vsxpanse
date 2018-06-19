#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "filesystem/resourcearchive.hpp"
#define private public
#include "graphicsmanager.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittests
{
	TEST_CLASS(graphicsmanager_test)
	{
	public:

		TEST_METHOD(initialize_test)
		{
			GraphicsManager::initialize();
			GraphicsManager::teardown();
		}
		TEST_METHOD(prepare_rendering_test)
		{
			GraphicsManager::initialize();
			GraphicsManager::prepare_rendering();
			GraphicsManager::teardown();
		}
		TEST_METHOD(load_texture_test)
		{
			GraphicsManager::initialize();
			ResourceArchive ra("TestResources");
			ResourceFile * file = ra.get_item("Images\\19.jpg");

			SDL_Texture * text = GraphicsManager::load_texture(file);
			//id = GraphicsManager::load_texture(file);
			//id = GraphicsManager::load_texture(file);
			GraphicsManager::teardown();
		}






	};
}