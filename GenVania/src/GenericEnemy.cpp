#include "GenericEnemy.hpp"
#include "components/spritecomponent.hpp"
#include "FileHandler.hpp"
#include "components/circlecollider.hpp"
#include "components/polygoncollider.hpp"

void GenericEnemy::setup()
{
	m_name = "GenericEnemy";
	add_component<SpriteComponent>()->load_sprite_from_image(FileHandler::get_item("Images\\harvester.png"));
	add_component<PolygonCollider>()->initialize({ Vector2D(0,0), Vector2D(10,10), Vector2D(20, 0) });
	//add_component<CircleCollider>()->initialize(10, Vector2D());
}

