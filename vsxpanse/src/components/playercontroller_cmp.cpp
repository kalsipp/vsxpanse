#include "playercontroller_cmp.hpp"
#include "inputmanager.hpp"

PlayerControllerCmp::PlayerControllerCmp() :
	m_speed(1)
{
}

void PlayerControllerCmp::update()
{
	Vector2D movement;
	movement.y = InputManager::get_key(SDL_SCANCODE_W)*-m_speed;
	movement.y -= InputManager::get_key(SDL_SCANCODE_S)*-m_speed;
	movement.x = InputManager::get_key(SDL_SCANCODE_D)*m_speed;
	movement.x -= InputManager::get_key(SDL_SCANCODE_A)*m_speed;

	m_owner->transform().move(movement);
}