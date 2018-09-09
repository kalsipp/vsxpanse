#pragma once
#include "../collider.hpp"
class BasicSquareCollider:public Collider{
public:
	void collision_step()override;
	std::vector<GameObject*> get_colliding_objects();
private:
	std::vector<GameObject*> m_colliding_objects;
	Vector2D m_offset;
	Vector2D m_size;
};