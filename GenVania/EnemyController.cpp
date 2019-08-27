#include "EnemyController.hpp"

void EnemyController::setup()
{
	speed = (float)helpers::random_int(100, 200);
	speed /= 100;
	direction = Vector2D(helpers::random_int(-100, 100), helpers::random_int(-100, 100)).normalized();
	collider = m_owner->get_component<Collider>();
}

void EnemyController::update()
{
	const std::vector<Collision>& colls = collider->get_collisions();
	Vector2D sum_vector;
	for (int i = 0; i < colls.size(); ++i)
	{
		Vector2D my_pos = owner().transform().get_position();
		Vector2D other_pos = colls[i].m_other_collidee->owner().transform().get_position();
		Vector2D diff = my_pos - other_pos;
		sum_vector += diff;
	}
	if (sum_vector.magnitude_squared() > 0)
	{
		direction = sum_vector.normalized();
	}

	if (owner().transform().get_position().x < 0)
	{
		direction.x = 1;
	}
	else if (owner().transform().get_position().x > 600)
	{
		direction.x = -1;
	}
	if (owner().transform().get_position().y < 0)
	{
		direction.y = 1;
	}
	else if (owner().transform().get_position().y > 600)
	{
		direction.y = -1;
	}
	direction = direction.normalized();

	m_owner->transform().move(direction * speed);
	m_owner->transform().rotate(1);
}
