#include "engine.hpp"
#include "Player.hpp"
#include "GenericEnemy.hpp"
#include "FileHandler.hpp"
#include "GenericBullet.hpp"
#include "Rotator.hpp"
#undef main


void set_up_gameobjects()
{
	Engine::add_gameobject<Player>()->setup();
	for (int i = 0; i < 300; ++i)
	{
		GenericEnemy* bull = Engine::add_gameobject<GenericEnemy>();
		bull->setup();
		Vector2D pos = Vector2D(helpers::random_int(0, 600), helpers::random_int(0, 600));
		bull->transform().set_position(pos);
	}
	//Engine::add_gameobject<Rotator>()->setup();
}

int main()
{
	Engine::initialize();
	FileHandler::initialize("Resources");
	Engine::register_scene("tmp", set_up_gameobjects);
	Engine::load_scene("tmp");
	Engine::start();
	Engine::teardown();
	return 0;
}

