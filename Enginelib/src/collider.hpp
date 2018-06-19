#pragma once
#include <memory>
#include <algorithm>
#include <map>
#include <set>
#include "component.hpp"

class GameObject;

class Collider;
class Collision {
public:
	Collision(Collider*, GameObject*);
	Collider* m_collider;
};

class Collider: public Component {
public:
	Collider();
	~Collider();
	virtual void setup(GameObject*) override;
	virtual void update() override;
	virtual void collision_step()override;
	virtual void teardown()override;
	const std::vector<GameObject*> & get_colliding_objects();
protected:
	void notify_collision(Collider*);
	bool already_colliding(Collider*);
	virtual bool collides_with(const Collider*){return false;}
	std::vector<GameObject*> m_colliding_objects;
	static std::vector<Collider*> m_all_colliders;
	std::set<Collider*> m_newly_registered_collisions;
	Collider* m_me;
private:
	static void register_collider(Collider*);
	static void unregister_collider(Collider*);
};