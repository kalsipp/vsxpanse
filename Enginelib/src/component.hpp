#pragma once
#include "gameobject.hpp"
class GameObject;
class Collision;

class Component {
public:
	Component(GameObject * user):m_owner(user) {}
	virtual void setup () {}
	virtual void collision_step(){}
	virtual void update() {}
	virtual void render() {}
	virtual void teardown() {}
	virtual ~Component() {}
	bool & enabled();
	virtual void on_collision(const Collision & coll){(void)coll;}
	GameObject & owner(){return *(m_owner);}
protected:
	bool m_enabled = true;

	GameObject * const m_owner;
};