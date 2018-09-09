#include <algorithm>
#include "collider.hpp"
#include "physxengine.hpp"


bool Collision::operator==(const Collision & other)const
{
	return other.m_other_collidee == m_other_collidee;
}


void Collider::setup() {
	register_collider();
}

void Collider::notify_collision(const Collision & coll)
{
	m_collisions.push_back(coll);
}

void Collider::clear_collisions()
{
	m_collisions.clear();
}

void Collider::teardown() {
	unregister_collider();
}

const std::vector<Collision> & Collider::get_collisions() {
	return m_collisions;
}

