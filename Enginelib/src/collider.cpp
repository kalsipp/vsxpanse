#include "collider.hpp"

std::vector<Collider*> Collider::m_all_colliders;


void Collider::setup(GameObject* user) {
	m_owner = user;
	register_collider(this);
}

void Collider::update() {
	m_newly_registered_collisions.clear();
}

void Collider::collision_step() {
	for (auto it_coll = m_all_colliders.begin();
	        it_coll != m_all_colliders.end(); ++it_coll) {
		auto sh_coll = *it_coll;
		ASSERT(sh_coll, "Collider is null");
		if (!sh_coll->already_colliding(this)) {
			if (sh_coll->collides_with(this)) {
				sh_coll->notify_collision(this);
				m_newly_registered_collisions.insert((*it_coll));
				ASSERT(false, "Add callback func");
			}
		}
	}
}

void Collider::notify_collision(Collider*  coll) {
	m_newly_registered_collisions.insert(coll);
}

bool Collider::already_colliding(Collider * coll) {
	return m_newly_registered_collisions.find(coll) != m_newly_registered_collisions.end();
}

void Collider::teardown() {
	unregister_collider(m_me);
}

const std::vector<GameObject*> & Collider::get_colliding_objects() {
	return m_colliding_objects;
}

void Collider::register_collider(Collider* item) {
	m_all_colliders.push_back(item);
}

void Collider::unregister_collider(Collider* item) {
	auto current = m_all_colliders.begin();
	while (current != m_all_colliders.end()) {
		ASSERT(*current, "Collider is null in unregister");
		if (*current == item) {
			m_all_colliders.erase(current);
			return;
		}
	}
	ASSERT(false, "Could not unregister collider");
}
