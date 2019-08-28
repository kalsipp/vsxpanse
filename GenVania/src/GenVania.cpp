#include "engine.hpp"
#include "Player.hpp"
#include "GenericEnemy.hpp"
#include "FIleHandler.hpp"
#include "GenericBullet.hpp"
#undef main


void set_up_gameobjects()
{
	Engine::add_gameobject<Player>()->setup();
	GenericEnemy * enemy = Engine::add_gameobject<GenericEnemy>();
	enemy->setup();
	enemy->transform().set_position(Vector2D(100, 100));
	for (int i = 0; i < 0; ++i)
	{
		GenericEnemy* bull = Engine::add_gameobject<GenericEnemy>();
		bull->setup();
		Vector2D pos = Vector2D(helpers::random_int(0, 600), helpers::random_int(0, 600));
		bull->transform().set_position(pos);
	}
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

