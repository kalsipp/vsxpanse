#pragma once
#include "component.hpp"

class GameObject;

class Collider;
struct Collision {
public:
	Collision(const Collider* other_collidee, const Vector2D& collision_direction, const Vector2D& point_of_collision)
	:	m_other_collidee(other_collidee), 
		m_collision_direction(collision_direction),
		m_point_of_collision(point_of_collision){}
	Collision(const Collider* other_collidee) :m_other_collidee(other_collidee) {}
	const Collider* m_other_collidee;
	const Vector2D m_collision_direction;
	const Vector2D m_point_of_collision;
	bool operator==(const Collision & other)const;
};

class Collider: public Component {
public:
	Collider(GameObject*owner) :Component(owner) {}
	virtual void setup() override;
	virtual void teardown()override;
	const std::vector<Collision> & get_collisions();

protected:
	friend class PhysxEngine;
	
	void notify_collision(const Collision & coll);
	void clear_collisions();
	virtual void register_collider() = 0;
	virtual void unregister_collider() = 0;
	
	std::vector<Collision> m_collisions;
	//std::vector<Collision*> m_new_collisions;
private:
};