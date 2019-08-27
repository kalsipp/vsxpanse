#include "PlayerController.hpp"
#include "inputmanager.hpp"
#include "engine.hpp"
#include "GenericBullet.hpp"

void PlayerController::setup()
{
	m_speed = 1;
	m_text_comp = owner().get_component<TextComponent>();
	ASSERT(m_text_comp, "textcomp is null");
	m_collider = owner().get_component<Collider>();
	ASSERT(m_collider, "collcomp is null");
}
void PlayerController::update()
{
	Vector2D movement;
	movement.y = InputManager::get_key(SDL_SCANCODE_W)*-m_speed;
	movement.y -= InputManager::get_key(SDL_SCANCODE_S)*-m_speed;
	movement.x = InputManager::get_key(SDL_SCANCODE_D)*m_speed;
	movement.x -= InputManager::get_key(SDL_SCANCODE_A)*m_speed;
	m_owner->transform().move(movement);

	if (InputManager::get_key_down(SDL_SCANCODE_K))
	{
		GenericBullet * new_bullet = Engine::add_gameobject<GenericBullet>();
		new_bullet->transform().set_position(m_owner->transform().get_position());
		BulletComponent * comp = new_bullet->get_component<BulletComponent>();
		comp->fire(Vector2D(1, 0), 2);
	}

	std::vector<Collision> colls = m_collider->get_collisions();
	std::cout << colls.size() << std::endl;

}
