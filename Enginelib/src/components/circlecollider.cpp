#include "circlecollider.hpp"
#include "../physxengine.hpp"


void CircleCollider::initialize(double radius, const Vector2D & offset)
{
	m_radius = radius;
	m_offset = offset;
}

Vector2D CircleCollider::position()const
{
	const double x = owner().transform().get_position().x + m_offset.x;
	const double y = owner().transform().get_position().y + m_offset.y;
	return Vector2D(x, y); 
}

constexpr
double CircleCollider::radius()const
{
	return m_radius;
}

bool CircleCollider::collides_with(const CircleCollider * other)
{
	const Vector2D my_pos = position();
	const Vector2D other_pos = other->position();
	const Vector2D diff = (my_pos - other_pos);
	const double distance = diff.magnitude_squared();
	const double my_radius = radius();
	const double other_radius = other->radius();
	const double radius_sum = (my_radius + other_radius)*(my_radius + other_radius);
	return distance < radius_sum;
}

void CircleCollider::register_collider()
{
	PhysxEngine::register_circlecollider(this);
}

void CircleCollider::unregister_collider()
{
	PhysxEngine::unregister_circlecollider(this);
}
