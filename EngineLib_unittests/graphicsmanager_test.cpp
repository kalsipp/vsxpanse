#include "pch.h"
#include "filesystem/resourcearchive.hpp"
#include "graphicsmanager.hpp"

TEST(graphicsmanager, initialize)
{
	GraphicsManager::initialize();
	GraphicsManager::teardown();
}
TEST(graphicsmanager, prepare_rendering)
{
	GraphicsManager::initialize();
	GraphicsManager::prepare_rendering();
	GraphicsManager::teardown();
}
TEST(graphicsmanager, load_texture_test)
{
	GraphicsManager::initialize();
	ResourceArchive ra("TestResources");
	ResourceFile* file = ra.get_item("Images\\19.jpg");

	SDL_Texture* text = GraphicsManager::load_texture(file);
	//id = GraphicsManager::load_texture(file);
	//id = GraphicsManager::load_texture(file);
	GraphicsManager::teardown();
}
