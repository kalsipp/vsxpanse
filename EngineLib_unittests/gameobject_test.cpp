#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "basics/rect.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#include "filesystem/resourcearchive.hpp"
#include "engine.hpp"
#define private public
#include "gameobject.hpp"
#include "components/spritecomponent.hpp"

namespace unittests
{
	TEST_CLASS(GameObject_test)
	{
	public:

		TEST_METHOD(create_gameobjects)
		{
			Engine::initialize();
			ResourceArchive x("TestResources");
			ResourceFile * img = x.get_item("Images\\19.jpg");	
			GameObject * g = Engine::add_gameobject<GameObject>();
			SpriteComponent * cmp = g->add_component<SpriteComponent>();
			cmp->load_sprite_from_image(img);
			Engine::teardown();
		}
	};
}