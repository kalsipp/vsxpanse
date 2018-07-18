#pragma once
#include "../collider.hpp"
class BasicSquareCollider:public Collider{
public:
	void update()override;
	std::vector<std::weak_ptr<GameObject>> get_colliding_objects();
private:
	std::vector<std::weak_ptr<GameObject>> m_colliding_objects;
	Vector2D m_offset;
	Vector2D m_size;
};