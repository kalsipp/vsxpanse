#include "pch.h"
#include "filesystem/resourcearchive.hpp"
#include "engine.hpp"
#include "gameobject.hpp"
#include "components/spritecomponent.hpp"


TEST(gameobject, create_gameobjects)
{
	Engine::initialize();
	ResourceArchive x("TestResources");
	ResourceFile * img = x.get_item("Images\\19.jpg");	
	GameObject * g = Engine::add_gameobject<GameObject>();
	SpriteComponent * cmp = g->add_component<SpriteComponent>();
	cmp->load_sprite_from_image(img);
	Engine::teardown();
}
