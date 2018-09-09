#pragma once
#include "component.hpp"

class BulletComponent:public Component
{
public:
	BulletComponent(GameObject * owner) :Component(owner) {}
	void update()override;
	void fire(const Vector2D & direction, float speed);
private:
	Vector2D m_direction;
	float m_speed = 0;
};