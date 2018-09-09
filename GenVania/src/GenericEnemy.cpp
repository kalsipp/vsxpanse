#include "GenericEnemy.hpp"
#include "components/spritecomponent.hpp"
#include "FileHandler.hpp"
#include "components/circlecollider.hpp"

void GenericEnemy::setup()
{
	m_name = "GenericEnemy";
	add_component<SpriteComponent>()->load_sprite_from_image(FileHandler::get_item("Images\\harvester.png"));
	add_component<CircleCollider>()->initialize(10, Vector2D());
}

