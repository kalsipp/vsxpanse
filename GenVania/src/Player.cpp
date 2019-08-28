#include "Player.hpp"
#include "PlayerController.hpp"
#include "components/spritecomponent.hpp"
#include "components/circlecollider.hpp"
#include "FileHandler.hpp"
#include "components/textcomponent.hpp"
#include "components/polygoncollider.hpp"

Player::Player(GAMEOBJECT_ID id):GameObject(id)
{
}

void Player::setup()
{
	m_name = "Player";
	add_component<PlayerController>();
	add_component<SpriteComponent>()->load_sprite_from_image(FileHandler::get_item("Images\\player.png"));
	//add_component<CircleCollider>()->initialize(10, Vector2D());
	add_component<PolygonCollider>()->initialize(
		{ 
			Vector2D(0,0), 
			Vector2D(10,20), 
			Vector2D(40, 40),
			Vector2D(60, 20),
			Vector2D(70, 0),
			Vector2D(60, -10),
			Vector2D(40, -20),
			Vector2D(20, -10),
		});
	add_component<TextComponent>()->initialize(FileHandler::get_item("Fonts\\calibri.ttf"));
}
