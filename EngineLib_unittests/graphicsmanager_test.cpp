#include "pch.h"
#include "filesystem/resourcearchive.hpp"
#include "graphicsmanager.hpp"

TEST(initialize_test, test)
{
	GraphicsManager::initialize();
	GraphicsManager::teardown();
}
TEST(prepare_rendering_test, test)
{
	GraphicsManager::initialize();
	GraphicsManager::prepare_rendering();
	GraphicsManager::teardown();
}
TEST(load_texture_test, test)
{
	GraphicsManager::initialize();
	ResourceArchive ra("TestResources");
	ResourceFile* file = ra.get_item("Images\\19.jpg");

	SDL_Texture* text = GraphicsManager::load_texture(file);
	//id = GraphicsManager::load_texture(file);
	//id = GraphicsManager::load_texture(file);
	GraphicsManager::teardown();
}
