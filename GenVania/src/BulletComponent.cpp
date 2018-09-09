#include "BulletComponent.hpp"

void BulletComponent::update()
{
	m_owner->transform().move(m_direction * m_speed);
}

void BulletComponent::fire(const Vector2D & direction, float speed)
{
	m_direction = direction;
	m_speed = speed;
}
