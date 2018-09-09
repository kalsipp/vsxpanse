#pragma once
#include "component.hpp"

class GameObject;

class Collider;
struct Collision {
	Collider* m_other_collidee;
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