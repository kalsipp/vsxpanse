#include "GenericBullet.hpp"
#include "FileHandler.hpp"

GenericBullet::GenericBullet(GAMEOBJECT_ID id) :GameObject(id) 
{
	m_spritecomponent = add_component<SpriteComponent>();
	m_spritecomponent->load_sprite_from_image(FileHandler::get_item("Images//resource.png"));
	m_bulletcomponent = add_component<BulletComponent>();
	m_collider = add_component<CircleCollider>();
	m_collider->initialize(5, Vector2D());
	m_name = "GenericBullet";
}

void GenericBullet::setup()
{
}

