#pragma once
#include "component.hpp"
#include "collider.hpp"
class EnemyController : public Component
{
public:
	EnemyController(GameObject* owner) :Component(owner) {}
	void setup()override;
	void update()override;
private:
	float speed;
	Vector2D direction;
	Collider* collider;
};

