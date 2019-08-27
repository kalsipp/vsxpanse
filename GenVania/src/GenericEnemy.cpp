#include "GenericEnemy.hpp"
#include "components/spritecomponent.hpp"
#include "FileHandler.hpp"
#include "components/circlecollider.hpp"
#include "components/polygoncollider.hpp"
#include "..//EnemyController.hpp"
void GenericEnemy::setup()
{
	m_name = "GenericEnemy";
	add_component<SpriteComponent>()->load_sprite_from_image(FileHandler::get_item("Images\\harvester.png"));
	add_component<PolygonCollider>()->initialize(
		{
			Vector2D(0,0),
			Vector2D(10,20),
			Vector2D(40, 40),
			Vector2D(60, 20),
			Vector2D(70, 0),
			Vector2D(60, -10),
			Vector2D(40, -20),
			Vector2D(20, -10)
		});

	add_component<EnemyController>()->setup();
	//add_component<CircleCollider>()->initialize(10, Vector2D());
}

